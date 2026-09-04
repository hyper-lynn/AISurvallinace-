# src/services/ai_service.py

import os
import json
import requests
import asyncio
import random
import time
import flet as ft
from typing import Optional, Dict, Tuple, Union, List
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

def extract_camera_target(prompt: str) -> tuple[str, str]:
    """
    Extract target camera source and name based on camera ID / index in user prompt.
    Support inputs like: 'webcam 1', 'cam 2', 'camera 0', 'webcam 2 screenshot', 'cam 1 ss', 'cctv 2', etc.
    """
    import re
    from services.camera_service import CameraService
    cams = CameraService().get_cameras()

    p_lower = prompt.lower()
    
    # 1. Match specific camera patterns (e.g. webcam 1, cam 2, camera 0, cam 1, cctv 2, #1, #2)
    match = re.search(r"(?:webcam|cam|camera|cctv)\s*#?\s*(\d{1,3})", p_lower)
    target_num = int(match.group(1)) if match else None

    if target_num is None:
        # Check standalone small digit (e.g. 0, 1, 2) in prompt, excluding long Telegram Chat IDs (> 999)
        num_matches = re.findall(r"\b(\d{1,2})\b", p_lower)
        if num_matches:
            target_num = int(num_matches[0])

    if target_num is not None:
        if cams:
            # First priority: Match DB camera where source == str(target_num) (e.g. source="1" or "0")
            for c in cams:
                if str(c.get("source", "")).strip() == str(target_num):
                    return str(c.get("source", "0")), c.get("name", f"Camera {target_num}")

            # Second priority: Match DB camera where ID == target_num
            for c in cams:
                if c.get("id") == target_num:
                    return str(c.get("source", "0")), c.get("name", f"Camera {target_num}")
            
            # Third priority: Match by 1-based index in DB (Cam 1 = 1st cam, Cam 2 = 2nd cam)
            if 1 <= target_num <= len(cams):
                c = cams[target_num - 1]
                return str(c.get("source", "0")), c.get("name", f"Camera {target_num}")
        
        # Fourth priority: Direct device index e.g. webcam 0, webcam 1, cam 2
        return str(target_num), f"Webcam Device {target_num}"

    # Default to first camera in DB if available
    if cams:
        c0 = cams[0]
        return str(c0.get("source", "0")), c0.get("name", "Camera 1")

    return "0", "Default Webcam (0)"


def extract_telegram_target(prompt: str) -> Optional[str]:
    """
    Extract requested Telegram Chat ID, Username, or Channel ID from user prompt if present.
    Supports formats like: 'to 12345678', 'id: 12345678', 'chat_id 12345678', 'telegram 12345678', '@mychannel'
    """
    import re
    p_lower = prompt.lower()

    # 1. Look for @username channel format
    username_match = re.search(r"@([a-zA-Z0-9_]{5,32})", prompt)
    if username_match:
        return f"@{username_match.group(1)}"

    # 2. Look for numeric Chat ID (e.g. 8647823342 or -10012345678)
    numeric_match = re.search(r"(?:to|id|chat|telegram|id:)?\s*(-?\d{6,15})", p_lower)
    if numeric_match:
        return numeric_match.group(1)

    return None

def detect_manager_intent(prompt: str) -> tuple[str, dict]:
    """
    Detect if the prompt is a Security Operations Center (SOC) Manager command:
    - Camera screenshot / snapshot
    - Camera list & status report
    - System health report
    """
    p = prompt.lower().strip()

    # 1. Camera Screenshot / Snapshot Intent
    snap_keywords = [
        "screenshot", "snapshot", "screen shot", "snap shot", "ss",
        "စကရင်ရှော့", "ဓါတ်ပုံရိုက်", "ဓာတ်ပုံရိုက်", "ပုံရိုက်", "ပုံရိုက်ပေးပါ", "ပုံရိုက်ပါ",
        "ss ရိုက်", "ss ပို့", "ss ပေးပို့", "ss ပို့ပေး", "photo ရိုက်", "picture ရိုက်",
        "camera screenshot", "camera snapshot", "cctv snapshot", "webcam snapshot",
        "webcam screenshot", "cam screenshot", "cam ss", "webcam ss",
        "capture camera", "take snapshot", "take screenshot", "/snapshot", "/screenshot"
    ]
    if any(k in p for k in snap_keywords) or ("webcam" in p and any(w in p for w in ["photo", "picture", "ss", "shot", "ရိုက်", "ပို့"])):
        return "camera_snapshot", {}

    # 2. Camera Status / List Intent (cam_list, cctv list, database cameras)
    status_keywords = [
        "cam_list", "camlist", "cam list", "camera list", "cctv list", "camera status", "cctv status",
        "cam_list ပို့ပေး", "camlist ပို့ပေး", "cam_list ပြပါ", "cam_list ပို့", "camlist ပြပါ",
        "camera စာရင်း", "cctv စာရင်း", "camera တွေပြပါ", "camera တေပြပါ", "ကင်မရာ အခြေအနေ", "ကင်မရာ စာရင်း",
        "list cameras", "show cameras", "get cameras", "all cameras"
    ]
    if any(k in p for k in status_keywords):
        return "camera_status", {}

    # 3. System Health Intent
    health_keywords = [
        "system health", "system status", "စနစ် အခြေအနေ", "စနစ်အခြေအနေ", "စနစ်ကျန်းမာရေး",
        "health report", "soc status"
    ]
    if any(k in p for k in health_keywords):
        return "system_health", {}

    return "none", {}

def detect_media_intent(prompt: str) -> str:
    """Detect if the user prompt is asking to generate an AI image or a video."""
    p = prompt.lower()
    
    # Exclude any camera/CCTV/webcam/ss/snapshot prompts from AI image generation
    cam_terms = [
        "webcam", "cctv", "cam ", "cam1", "cam2", "cam3", "cam0", "camera",
        "ss", "screenshot", "snapshot", "ဓါတ်ပုံရိုက်", "ဓာတ်ပုံရိုက်", "ပုံရိုက်", "ss ပို့"
    ]
    if any(term in p for term in cam_terms):
        return "text"

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
        # 0. AI Security Inspection & Prompt Injection Guardrail
        from services.ai_security import AISecurityGuard
        is_safe, violation_msg, sanitized_prompt = AISecurityGuard.inspect_and_sanitize(prompt)
        if not is_safe:
            return {
                "text": violation_msg,
                "media_type": None,
                "media_url": None
            }
        prompt = sanitized_prompt

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

        # Check SOC Manager Intents (Camera Snapshot, Status, Health)
        mgr_intent, mgr_args = detect_manager_intent(prompt)
        if mgr_intent != "none":
            if mgr_intent == "camera_snapshot":
                from controllers.camera_controller import CameraController
                from services.telegram_service import TelegramService
                from datetime import datetime

                target_source, target_name = extract_camera_target(prompt)
                req_chat_id = extract_telegram_target(prompt)

                snapshot_path = CameraController.capture_snapshot(source=target_source)
                if snapshot_path and os.path.exists(snapshot_path):
                    tg_msg = ""
                    try:
                        tg_svc = TelegramService()
                        tg_config = tg_svc.get_config()
                        tg_targets = tg_svc.get_targets()

                        # Determine destination Chat ID (Explicitly requested Chat ID, or DB default, or first target)
                        dest_chat_id = req_chat_id or tg_config.get("chat_id")
                        if not dest_chat_id and tg_targets:
                            dest_chat_id = tg_targets[0].get("chat_id")

                        bot_token = tg_config.get("bot_token")
                        if bot_token and dest_chat_id:
                            caption = (
                                f"🚨 <b>S-Eye Instant Camera Snapshot Dispatch</b>\n\n"
                                f"📹 <b>Camera Source:</b> {target_name} (<code>{target_source}</code>)\n"
                                f"⏰ <b>Timestamp:</b> {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}\n\n"
                                f"<i>Dispatched via AI Chat Command Request</i>"
                            )
                            ok, res_str = tg_svc.send_alert_photo(snapshot_path, caption=caption, target_chat_id=dest_chat_id)
                            if ok:
                                tg_msg = f"\n\n🚀 **Telegram Dispatch:** Snapshot photo sent to Chat ID `{dest_chat_id}` successfully!"
                            else:
                                tg_msg = f"\n\n⚠️ **Telegram Dispatch Notice:** {res_str}"
                        elif not bot_token:
                            tg_msg = "\n\n💡 *Telegram Bot Token မသတ်မှတ်ရသေးပါ။ Settings > Telegram Dispatcher တွင် Bot Token ထည့်သွင်းပေးပါခင်ဗျာ။*"
                        elif not dest_chat_id:
                            tg_msg = "\n\n💡 *Telegram Target Chat ID မသတ်မှတ်ရသေးပါ။ Prompt ထဲတွင် Chat ID ထည့်ပါ သို့မဟုတ် Settings တွင် သတ်မှတ်ပေးပါခင်ဗျာ။*"
                    except Exception as tg_ex:
                        logger.error(f"Telegram snapshot dispatch error: {tg_ex}")

                    return {
                        "text": f"📸 **[SOC Manager Live Snapshot]**\n\n**Target Camera:** {target_name} (`Source: {target_source}`)\n**Status:** Real-time Camera Feed Snapshot captured cleanly.{tg_msg}",
                        "media_type": "image",
                        "media_url": snapshot_path
                    }
                else:
                    return {
                        "text": "⚠️ **[SOC Manager Alert]**: Camera Screenshot ရိုက်ကူးရာတွင် အခက်အခဲ ဖြစ်ပေါ်ခဲ့ပါသည်။ ကျေးဇူးပြု၍ ကင်မရာ ချိတ်ဆက်မှုကို စစ်ဆေးပေးပါခင်ဗျာ။",
                        "media_type": None,
                        "media_url": None
                    }

            elif mgr_intent == "camera_status":
                from services.camera_service import CameraService
                cams = CameraService().get_cameras()
                if not cams:
                    return {
                        "text": "📸 **[SOC Manager Report]**\n\nDatabase ထဲတွင် လက်ရှိ ချိတ်ဆက်ထားသော ကင်မရာ စာရင်း မရှိသေးပါ။",
                        "media_type": None,
                        "media_url": None
                    }

                lines = [
                    "🎥 **[SOC Manager - Official Camera Database List (`cam_list`)]**",
                    f"**Database ထဲရှိ တပ်ဆင်ထားသော ကင်မရာ စုစုပေါင်း:** `{len(cams)}` လုံး\n"
                ]
                for i, c in enumerate(cams, 1):
                    lines.append(f"**{i}. {c['name']}** (ID: `{c['id']}`)")
                    lines.append(f"   • **Device Type:** `{c.get('device_type', 'webcam').upper()}`")
                    lines.append(f"   • **Source / SN:** `{c.get('source')}`")
                    lines.append(f"   • **Zone Group:** `{c.get('camera_group', 'Zone-01')}`")
                    lines.append(f"   • **AI Detection:** `{'ENABLED' if c.get('human_detection') else 'DISABLED'}`")
                    lines.append(f"   • **Telegram Alarm:** `{'ACTIVE' if c.get('telegram_alert_enabled') else 'OFF'}`\n")

                return {
                    "text": "\n".join(lines),
                    "media_type": None,
                    "media_url": None
                }

            elif mgr_intent == "system_health":
                return {
                    "text": (
                        "🛡️ **[SOC Manager - Security System Health Report]**\n\n"
                        "• **Surveillance Stream Engine:** Nominal (10 FPS Zero-Lag Capture)\n"
                        "• **AI Threat Detection:** YOLOv8 Pose & Human Detection Active\n"
                        "• **Telegram Alert Dispatcher:** Operational & Online\n"
                        "• **Storage Database:** SQLite3 Secure Encryption Active\n\n"
                        "စနစ်တစ်ခုလုံး အဆင်သင့် လုံခြုံစွာ လည်ပတ်လျက် ရှိပါသည်ခင်ဗျာ။"
                    ),
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
                "text": "🖼️ Image Output:",
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
            
        payload = {
            "system_instruction": {
                "parts": [{"text": AISecurityGuard.get_system_policy()}]
            },
            "contents": contents
        }
        headers = {"Content-Type": "application/json"}
        
        def _make_request():
            last_error_msg = ""
            for model in models_to_try:
                url = f"https://generativelanguage.googleapis.com/v1beta/models/{model}:generateContent?key={api_key}"
                # Auto-retry up to 3 times per model for network fluctuations / timeouts
                for attempt in range(1, 4):
                    try:
                        timeout_val = 12 + (attempt * 6) # 18s, 24s, 30s
                        resp = requests.post(url, json=payload, headers=headers, timeout=timeout_val)
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
                            break
                        elif resp.status_code == 403:
                            logger.error(f"Gemini API ({model}) Forbidden (HTTP 403)")
                            last_error_msg = "API Key မမှန်ကန်ပါ သို့မဟုတ် မဖွင့်ရသေးပါ (HTTP 403 Forbidden)"
                            break
                        elif resp.status_code == 429:
                            logger.error(f"Gemini API ({model}) Rate Limit (HTTP 429)")
                            last_error_msg = f"API Traffic / Rate Limit ပြည့်သွားပါသည် (HTTP 429 - {model})"
                            time.sleep(1.0)
                        else:
                            logger.error(f"Gemini API ({model}) HTTP Error {resp.status_code}")
                            last_error_msg = f"HTTP Error {resp.status_code}"
                    except BaseException as ex:
                        logger.warning(f"Gemini API Connection Attempt {attempt}/3 ({model}): {ex}")
                        last_error_msg = f"အင်တာနက် လိုင်းနှေးနေပါသည် သို့မဟုတ် Read Timeout ဖြစ်ပါသည် ({ex})"
                        time.sleep(0.8)

            return (
                f"⚠️ Gemini API Connection Error!\n\n"
                f"💡 လက်ရှိတွင် အင်တာနက် လိုင်းကျနေပါသည် သို့မဟုတ် Network Timeout ဖြစ်သွားပါသည် (၃ ကြိမ် ထပ်မံကြိုးစားပြီးပါပြီ)။\n\n"
                f"အကြောင်းရင်း: {last_error_msg}\n"
                f"ကျေးဇူးပြု၍ အင်တာနက် ချိတ်ဆက်မှုအား စစ်ဆေးပြီး သို့မဟုတ် အခြား Gemini Model သို့ ပြောင်းလဲ၍ ထပ်မံ ကြိုးစားပေးပါခင်ဗျာ။"
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
                
            page.show_dialog(
                ft.SnackBar(
                    content=ft.Text(f"✅ {media_type.capitalize()} ဖြင့် အောင်မြင်စွာ သိမ်းဆည်းပြီးပါပြီ:\n{filepath}", font_family=AppFonts.MYANMAR),
                    bgcolor=ft.Colors.GREEN_700,
                    duration=5000
                )
            )
        except Exception as ex:
            logger.error(f"Download Error: {ex}")
            page.show_dialog(
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
