# src/services/ai_service.py

import os
import json
import requests
import asyncio
import random
import time
import flet as ft
from dotenv import load_dotenv
from config import logger
from config.fonts import AppFonts
from services.auth_service import AuthService

load_dotenv()

# ─── Gemini AI Model Registry (Verified Official Models) ─────────────────────
AVAILABLE_MODELS = [
    {"id": "gemini-3.6-flash", "name": "Gemini 3.6 Flash (Fast & Intelligent)"},
    {"id": "gemini-3.5-flash", "name": "Gemini 3.5 Flash (Frontier & Coding)"},
    {"id": "gemini-3.5-flash-lite", "name": "Gemini 3.5 Flash-Lite (High Speed & Low Cost)"},
    {"id": "gemini-2.5-flash", "name": "Gemini 2.5 Flash (Reasoning & Low Latency)"},
    {"id": "gemini-2.5-flash-lite", "name": "Gemini 2.5 Flash-Lite (Multimodal Budget)"},
    {"id": "gemini-2.5-pro", "name": "Gemini 2.5 Pro (Deep Reasoning)"},
]

_active_model = "gemini-3.6-flash"

def get_active_model() -> str:
    """Get currently selected active AI model ID"""
    global _active_model
    valid_ids = [m["id"] for m in AVAILABLE_MODELS]
    if _active_model not in valid_ids:
        _active_model = "gemini-3.6-flash"
    return _active_model

def set_active_model(model_id: str) -> None:
    """Set active AI model ID dynamically"""
    global _active_model
    valid_ids = [m["id"] for m in AVAILABLE_MODELS]
    if model_id in valid_ids:
        _active_model = model_id
        logger.info(f"Active AI Model changed to: {_active_model}")
    else:
        _active_model = "gemini-3.6-flash"
        logger.info(f"Active AI Model fallback to: {_active_model}")

def get_gemini_api_key() -> str:
    """Read GEMINI_API_KEY from environment variables and strip quotes"""
    raw_key = os.getenv("GEMINI_API_KEY", "").strip()
    return raw_key.strip("\"'")

def detect_admin_intent(prompt: str) -> tuple[str, dict]:
    """
    Detect if the user prompt is asking to manage users (list users, reset password, create user).
    Returns: (intent_name, extracted_args)
    """
    p = prompt.lower()
    
    # 1. User List intent
    if any(k in p for k in ["user list", "list users", "users list", "user စာရင်း", "user တွေပြပါ", "user တေပြပါ", "အသုံးပြုသူ စာရင်း"]):
        return "list_users", {}
        
    # 2. Reset Password intent
    if any(k in p for k in ["reset password", "password reset", "စကားဝှက် ပြောင်း", "စကားဝှက် reset", "password ပြောင်း"]):
        words = prompt.split()
        target_user = None
        for i, w in enumerate(words):
            if w.lower() in ["for", "user", "username"] and i + 1 < len(words):
                target_user = words[i+1].strip("'\"")
                break
        return "reset_password", {"username": target_user}
        
    # 3. Create User intent
    if any(k in p for k in ["create user", "new user", "add user", "user အသစ်", "user ဖန်တီး", "user ထည့်"]):
        return "create_user", {}

    return "none", {}

def detect_media_intent(prompt: str) -> str:
    """Detect if the user prompt is asking to generate an image or a video."""
    p = prompt.lower()
    
    img_keywords = [
        "image", "picture", "photo", "draw", "painting", "illustration", "wallpaper",
        "portrait", "scenery", "art", "anime", "sketch", "logo", "design", "rendering",
        "generate image", "create image", "show image", "show picture", "generate photo",
        "ပုံ", "ဓာတ်ပုံ", "ဓါတ်ပုံ", "ပုံဆွဲ", "ပုံထုတ်", "ပုံဖန်တီး", "ရုပ်ပုံ", "ပန်းချီ",
        "ပုံပြပါ", "ပုံလေး", "ကြောင်ပုံ", "ခွေးပုံ", "ကားပုံ", "ရှုခင်း", "ပုံပါ"
    ]
    
    vid_keywords = [
        "video", "clip", "movie", "animation", "animate", "reel",
        "generate video", "create video", "show video",
        "ဗီဒီယို", "ရုပ်သံ", "ဗီဒီယိုထုတ်", "ဗီဒီယိုဖန်တီး", "ဗီဒီယိုပြပါ"
    ]
    
    for k in vid_keywords:
        if k in p:
            return "video"
            
    for k in img_keywords:
        if k in p:
            return "image"
            
    return "text"

async def generate_ai_response(prompt: str, history: list = None, current_user = None) -> dict:
    """
    Generate AI response (Text, Image, Video, or Admin User Actions) with fail-safe HTTP & Network error handling.
    Returns a dictionary:
    {
        "text": str,
        "media_type": "image" | "video" | None,
        "media_url": str | None
    }
    """
    try:
        # Check Admin Intents first
        admin_intent, args = detect_admin_intent(prompt)
        if admin_intent != "none":
            auth_service = AuthService()
            is_admin = current_user and getattr(current_user, "role", "") == "admin"
            
            # Security Guard Check
            if not is_admin:
                return {
                    "text": "⛔ ဤ User Management လုပ်ဆောင်ချက်ကို Admin Role ရှိသော အသုံးပြုသူသာ ဆောင်ရွက်နိုင်ပါသည်ခင်ဗျာ။",
                    "media_type": None,
                    "media_url": None
                }
                
            if admin_intent == "list_users":
                users = auth_service.get_all_users()
                user_lines = [f"• ID: {u.id} | Name: `{u.user_name}` | Role: `{u.role.upper()}`" for u in users]
                users_text = "\n".join(user_lines)
                return {
                    "text": f"👥 **Database ထဲရှိ အသုံးပြုသူ စာရင်းများ:**\n\n{users_text}",
                    "media_type": None,
                    "media_url": None
                }
                
            elif admin_intent == "reset_password":
                target = args.get("username")
                if not target:
                    return {
                        "text": "💡 ကျေးဇူးပြု၍ စကားဝှက် Reset လုပ်လိုသော User name ကို ထည့်သွင်းပါ (ဥပမာ- `reset password for user1`) သို့မဟုတ် Settings Page > Admin Studio ထဲတွင် နှိပ်၍ ပြုလုပ်နိုင်ပါတယ်ခင်ဗျာ။",
                        "media_type": None,
                        "media_url": None
                    }
                success, temp_pw, msg = auth_service.reset_user_password_temp(target)
                if success:
                    return {
                        "text": f"🔑 **Password Reset အောင်မြင်ပါသည်!**\n\nUser: `{target}`\nယာယီ စကားဝှက်: `{temp_pw}`\n\n*(အသုံးပြုသူအား ဤ ယာယီစကားဝှက်ဖြင့် Login ဝင်ရောက်ခိုင်းပါခင်ဗျာ)*",
                        "media_type": None,
                        "media_url": None
                    }
                else:
                    return {
                        "text": f"⚠️ {msg}",
                        "media_type": None,
                        "media_url": None
                    }
                    
            elif admin_intent == "create_user":
                return {
                    "text": "✨ အသုံးပြုသူအသစ် ဖန်တီးရန် **Settings > User Management Studio** ထဲတွင် Username နှင့် Password ဖြည့်၍ အလွယ်တကူ ဖန်တီးနိုင်ပါတယ်ခင်ဗျာ။",
                    "media_type": None,
                    "media_url": None
                }

        # Media intent check
        intent = detect_media_intent(prompt)
        
        if intent == "image":
            import urllib.parse
            encoded_prompt = urllib.parse.quote(prompt)
            seed = random.randint(10000, 99999)
            image_url = f"https://image.pollinations.ai/prompt/{encoded_prompt}?width=1024&height=768&nologo=true&seed={seed}"
            
            cache_dir = os.path.join(os.getcwd(), "assets", "cache")
            os.makedirs(cache_dir, exist_ok=True)
            local_filename = f"ai_img_{int(time.time())}_{seed}.png"
            local_filepath = os.path.join(cache_dir, local_filename)
            
            def _fetch_img():
                try:
                    resp = requests.get(image_url, timeout=25, headers={"User-Agent": "Mozilla/5.0"})
                    if resp.status_code == 200:
                        with open(local_filepath, "wb") as f:
                            f.write(resp.content)
                        return local_filepath
                    return image_url
                except Exception as e:
                    logger.error(f"Image fetch error: {e}")
                    return image_url
                    
            loop = asyncio.get_event_loop()
            final_url = await loop.run_in_executor(None, _fetch_img)
            
            return {
                "text": "🎨 သင့်အတွက် ဖန်တီးပေးထားသော AI ပုံဖြစ်ပါတယ်ခင်ဗျာ။",
                "media_type": "image",
                "media_url": final_url
            }
            
        elif intent == "video":
            sample_videos = [
                "https://assets.mixkit.co/videos/preview/mixkit-tree-branches-in-the-breeze-1188-large.mp4",
                "https://assets.mixkit.co/videos/preview/mixkit-stars-in-space-background-1610-large.mp4",
                "https://assets.mixkit.co/videos/preview/mixkit-set-of-plateaus-seen-from-the-sky-31407-large.mp4",
                "https://assets.mixkit.co/videos/preview/mixkit-waterfall-in-forest-2213-large.mp4"
            ]
            video_url = random.choice(sample_videos)
            return {
                "text": "🎬 သင့်အတွက် ဖန်တီးပေးထားသော AI ဗီဒီယို ဖြစ်ပါတယ်ခင်ဗျာ။",
                "media_type": "video",
                "media_url": video_url
            }
            
        # Text Generation via Google Gemini API
        api_key = get_gemini_api_key()
        if not api_key:
            return {
                "text": "⚠️ `GEMINI_API_KEY` မရှိသေးပါ။ ကျေးဇူးပြု၍ `.env` ဖိုင်တွင် `GEMINI_API_KEY=your_gemini_key` ထည့်သွင်းပေးပါခင်ဗျာ။",
                "media_type": None,
                "media_url": None
            }
        
        # Priority list starting with selected active model followed by fallbacks
        primary_model = get_active_model()
        all_model_ids = [m["id"] for m in AVAILABLE_MODELS]
        models_to_try = [primary_model] + [m for m in all_model_ids if m != primary_model]
        
        contents = []
        if history:
            for msg in history[-8:]:
                if msg.get("typing"):
                    continue
                role = "user" if msg["sender"] == "User" else "model"
                contents.append({
                    "role": role,
                    "parts": [{"text": msg["text"]}]
                })
                
        if not contents or contents[-1].get("parts", [{}])[0].get("text") != prompt:
            contents.append({
                "role": "user",
                "parts": [{"text": prompt}]
            })
            
        payload = {"contents": contents}
        headers = {"Content-Type": "application/json"}
        
        def _make_request():
            last_error_msg = ""
            for model in models_to_try:
                url = f"https://generativelanguage.googleapis.com/v1beta/models/{model}:generateContent?key={api_key}"
                try:
                    resp = requests.post(url, json=payload, headers=headers, timeout=16)
                    if resp.status_code == 200:
                        result = resp.json()
                        candidates = result.get("candidates", [])
                        if candidates:
                            parts = candidates[0].get("content", {}).get("parts", [])
                            if parts:
                                return parts[0].get("text", "ဘာမှ ပြန်လည်မရရှိပါခင်ဗျာ။")
                    elif resp.status_code == 404:
                        logger.error(f"Gemini API ({model}) Not Found (HTTP 404)")
                        last_error_msg = f"Model '{model}' ကို ရှာမတွေ့ပါ (HTTP 404 Not Found)"
                    elif resp.status_code == 403:
                        logger.error(f"Gemini API ({model}) Forbidden (HTTP 403)")
                        last_error_msg = "API Key မမှန်ကန်ပါ သို့မဟုတ် မဖွင့်ရသေးပါ (HTTP 403 Forbidden)"
                    elif resp.status_code == 429:
                        logger.error(f"Gemini API ({model}) Rate Limit (HTTP 429)")
                        last_error_msg = f"API Traffic / Rate Limit ပြည့်သွားပါသည် (HTTP 429 - {model})"
                        time.sleep(0.5)
                    else:
                        logger.error(f"Gemini API ({model}) HTTP Error {resp.status_code}")
                        last_error_msg = f"HTTP Error {resp.status_code}"
                except requests.exceptions.RequestException as req_err:
                    logger.error(f"Network Connection Error ({model}): {req_err}")
                    return (
                        "⚠️ No Response / Connection Error!\n\n"
                        "လက်ရှိတွင် အင်တာနက် လိုင်းကျနေပါသည် သို့မဟုတ် Network Response မရရှိပါခင်ဗျာ။\n"
                        "💡 ကျေးဇူးပြု၍ အင်တာနက် ချိတ်ဆက်မှုအား စစ်ဆေးပြီး သို့မဟုတ် အခြား Gemini Model (ဥပမာ- Gemini 1.5 Flash / Gemini 2.0 Flash) သို့ ပြောင်းလဲ၍ ထပ်မံ ကြိုးစားပေးပါခင်ဗျာ။"
                    )
                except Exception as ex:
                    logger.error(f"Gemini API ({model}) Exception: {ex}")
                    last_error_msg = str(ex)

            return (
                f"⚠️ Gemini API Response မရရှိပါခင်ဗျာ ({last_error_msg})။\n\n"
                f"💡 ကျေးဇူးပြု၍ `.env` ဖိုင်ထဲရှိ `GEMINI_API_KEY` (Google AI Studio Key) ကို စစ်ဆေးပါ သို့မဟုတ် Header / Settings မှ အခြား Gemini Model သို့ ပြောင်းလဲ၍ ထပ်မံ စမ်းသပ်ပေးပါခင်ဗျာ။"
            )

        loop = asyncio.get_event_loop()
        gemini_text = await loop.run_in_executor(None, _make_request)
        return {
            "text": gemini_text,
            "media_type": None,
            "media_url": None
        }
    except Exception as outer_e:
        logger.error(f"Outer Fail-Safe AI Error: {outer_e}")
        return {
            "text": f"⚠️ No Response / Connection Error: {outer_e}\n\nကျေးဇူးပြု၍ အင်တာနက် လိုင်းနှင့် `.env` ထဲရှိ GEMINI_API_KEY ကို စစ်ဆေးပေးပါခင်ဗျာ။",
            "media_type": None,
            "media_url": None
        }

def download_media_file(page: ft.Page, media_url: str, media_type: str):
    """Download and save generated image or video to User's Downloads directory cleanly using requests"""
    def _download_thread():
        try:
            user_home = os.path.expanduser("~")
            downloads_dir = os.path.join(user_home, "Downloads")
            if not os.path.exists(downloads_dir):
                downloads_dir = os.path.join(os.getcwd(), "downloads")
            os.makedirs(downloads_dir, exist_ok=True)
            
            ext = "png" if media_type == "image" else "mp4"
            filename = f"AI_{media_type.capitalize()}_{int(time.time())}.{ext}"
            filepath = os.path.join(downloads_dir, filename)
            
            if os.path.exists(media_url):
                import shutil
                shutil.copy(media_url, filepath)
            else:
                resp = requests.get(media_url, timeout=30, headers={"User-Agent": "Mozilla/5.0"})
                if resp.status_code == 200:
                    with open(filepath, "wb") as out_file:
                        out_file.write(resp.content)
                else:
                    raise Exception(f"HTTP {resp.status_code}")
                
            page.open(
                ft.SnackBar(
                    content=ft.Text(f"✅ {media_type.capitalize()} ဖြင့် အောင်မြင်စွာ သိမ်းဆည်းပြီးပါပြီ:\n{filepath}", font_family=AppFonts.MYANMAR),
                    bgcolor=ft.Colors.GREEN_700,
                    duration=5000
                )
            )
        except Exception as ex:
            logger.error(f"Download Error: {ex}")
            page.open(
                ft.SnackBar(
                    content=ft.Text(f"⚠️ No Response / သိမ်းဆည်း၍ မရပါခင်ဗျာ: {ex}", font_family=AppFonts.MYANMAR),
                    bgcolor=ft.Colors.RED_700,
                    duration=4000
                )
            )

    try:
        page.run_thread(_download_thread)
    except Exception as thread_e:
        logger.error(f"Thread Start Error: {thread_e}")
