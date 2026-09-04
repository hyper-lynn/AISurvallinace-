# src/views/aiChatView.py

import flet as ft
import asyncio
from services.ai_service import generate_ai_response, download_media_file, get_active_model
from services.chat_service import ChatService
from views.components.model_selector import ModelSelector
from config.fonts import AppFonts
from core.auth_context import use_user

from urllib.parse import urlparse, parse_qs

@ft.component
def aiChatView():
    page = ft.context.page
    page_width = page.width if page.width else 800
    user = use_user()
    chat_service = ft.use_memo(lambda: ChatService(), [])
    
    user_id = user.id if user else None

    # Get back_route callback URL from query parameter (e.g. /ai-chat?from=/home or /ai-chat?from=/dashboard)
    back_route = "/home"
    if page and page.route:
        parsed = urlparse(page.route)
        qs = parse_qs(parsed.query)
        if "from" in qs and qs["from"]:
            back_route = qs["from"][0]

    # Always fetch latest messages directly from SQLite3 database
    db_messages = ft.use_memo(lambda: chat_service.get_messages(user_id), [user_id])
    messages, set_messages = ft.use_state(db_messages)
    # ft.context.page.floating_action_button.visible = False
    # Declarative key state for input reset
    input_key, set_input_key = ft.use_state(0)
    input_ref = ft.use_ref()
    listview_ref = ft.use_ref()
    
    # Clear chat history handler
    def handle_clear_history(e):
        chat_service.clear_history(user_id)
        fresh_msgs = [{
            "sender": "AI",
            "text": "မင်္ဂလာပါ! ကျွန်တော်ကတော့ Shadow EYE ရဲ့ Gemini AI & Media Studio ဖြစ်ပါတယ်။ စာသားမေးမြန်းမှုများ၊ ပုံဖန်တီးခြင်း၊ ဗီဒီယို သို့မဟုတ် အကောင့် စီမံခန့်ခွဲမှုများကို ပြုလုပ်နိုင်ပါတယ်။",
            "media_type": None,
            "media_url": None
        }]
        set_messages(fresh_msgs)

    # Core message sending logic
    async def send_message_with_text(user_text: str):
        if not user_text:
            return
            
        # Reset input field declaratively by changing control key
        set_input_key(input_key + 1)
        
        # Save User Message to SQLite3 database
        chat_service.save_message("User", user_text, user_id=user_id)
        
        # 1. Add user message
        new_messages = list(messages)
        new_messages.append({"sender": "User", "text": user_text})
        set_messages(new_messages)
        
        # 2. Add typing/loading indicator
        typing_messages = list(new_messages)
        typing_messages.append({"sender": "AI", "text": f"[{get_active_model()}] AI မှ ဖန်တီးပေးနေပါသည်... ခဏစောင့်ဆိုင်းပေးပါခင်ဗျာ...", "typing": True})
        set_messages(typing_messages)
        
        # 3. Call AI Service (Text / Image / Video / Admin Intents)
        ai_res = await generate_ai_response(user_text, new_messages, current_user=user)
        
        # Save AI Response to SQLite3 database
        chat_service.save_message(
            "AI",
            ai_res["text"],
            media_type=ai_res.get("media_type"),
            media_url=ai_res.get("media_url"),
            user_id=user_id
        )
        
        # 4. Update with final AI response
        final_messages = list(new_messages)
        final_messages.append({
            "sender": "AI",
            "text": ai_res["text"],
            "media_type": ai_res.get("media_type"),
            "media_url": ai_res.get("media_url")
        })
        set_messages(final_messages)
        if page:
            try:
                page.update()
            except Exception:
                pass

    # Submit action handler from button
    async def send_message(e):
        user_text = ""
        if input_ref.current and input_ref.current.value:
            user_text = input_ref.current.value.strip()
        await send_message_with_text(user_text)

    # On Change handler to detect Double Enter (\n\n) submission
    def handle_input_change(e):
        val = e.control.value
        if val and val.endswith("\n\n"):
            clean_text = val.rstrip("\n\r ")
            if clean_text:
                asyncio.create_task(send_message_with_text(clean_text))

    # Auto-rescaling responsive bubble logic
    chat_bubbles = []
    max_bubble_width = max(280, min(750, page_width - 120))
    
    for msg in messages:
        is_user = msg["sender"] == "User"
        is_typing = msg.get("typing", False)
        media_type = msg.get("media_type")
        media_url = msg.get("media_url")
        
        text_len = len(msg["text"])
        est_width = text_len * 10 + 32
        bubble_width = min(max_bubble_width, est_width) if text_len < 35 else max_bubble_width
        
        if media_type:
            bubble_width = min(500, max_bubble_width)

        # Media controls (Images & Videos)
        media_controls = []
        if media_type == "image" and media_url:
            img_src = media_url
            if not media_url.startswith(("http://", "https://", "data:image/")):
                import base64
                import os
                found_path = None
                candidates = [
                    media_url,
                    os.path.normpath(media_url),
                    os.path.abspath(os.path.normpath(media_url)),
                    os.path.join(os.getcwd(), media_url),
                    os.path.join(os.getcwd(), os.path.normpath(media_url)),
                    os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), "assets", "cache", os.path.basename(media_url))
                ]
                for cand in candidates:
                    if cand and os.path.exists(cand):
                        found_path = cand
                        break
                
                if found_path:
                    try:
                        with open(found_path, "rb") as f:
                            b64_str = base64.b64encode(f.read()).decode("utf-8")
                            img_src = f"data:image/jpeg;base64,{b64_str}"
                    except Exception as ex:
                        print(f"Error converting local image to base64: {ex}")

            media_controls.append(
                ft.Image(
                    src=img_src,
                    width=380,
                    height=260,
                    fit=ft.BoxFit.CONTAIN,
                    border_radius=12
                )
            )
            media_controls.append(
                ft.Button(
                    "Save Image",
                    icon=ft.Icons.DOWNLOAD_ROUNDED,
                    style=ft.ButtonStyle(padding=ft.Padding(14, 8, 14, 8)),
                    on_click=lambda e, u=media_url: download_media_file(page, u, "image")
                )
            )
        elif media_type == "video" and media_url:
            media_controls.append(
                ft.Container(
                    width=360,
                    height=220,
                    bgcolor=ft.Colors.BLACK87,
                    border_radius=12,
                    alignment=ft.Alignment(0, 0),
                    content=ft.Column(
                        alignment=ft.MainAxisAlignment.CENTER,
                        horizontal_alignment=ft.CrossAxisAlignment.CENTER,
                        controls=[
                            ft.Icon(ft.Icons.PLAY_CIRCLE_FILL_ROUNDED, color=ft.Colors.WHITE, size=52),
                            ft.Text("AI Video Generated", color=ft.Colors.WHITE, size=14, weight=ft.FontWeight.BOLD)
                        ],
                        spacing=6
                    )
                )
            )
            media_controls.append(
                ft.Button(
                    "Save Video",
                    icon=ft.Icons.DOWNLOAD_ROUNDED,
                    style=ft.ButtonStyle(padding=ft.Padding(14, 8, 14, 8)),
                    on_click=lambda e, u=media_url: download_media_file(page, u, "video")
                )
            )

        if is_typing:
            column_controls = [
                ft.Row(
                    controls=[
                        ft.ProgressRing(width=20, height=20, stroke_width=2.5, color=ft.Colors.BLUE_600),
                        ft.Text(
                            msg["text"],
                            color=ft.Colors.ON_SURFACE,
                            size=13,
                            italic=True,
                            font_family=AppFonts.MYANMAR
                        )
                    ],
                    spacing=10
                )
            ]
        else:
            column_controls = [
                ft.Text(
                    msg["text"],
                    color=ft.Colors.WHITE if is_user else ft.Colors.ON_SURFACE,
                    size=14,
                    italic=False,
                    weight=ft.FontWeight.W_400,
                    font_family=AppFonts.MYANMAR,
                    selectable=True,
                )
            ] + media_controls

        chat_bubbles.append(
            ft.Row(
                controls=[
                    ft.Container(
                        content=ft.Column(
                            controls=column_controls,
                            tight=True,
                            spacing=10
                        ),
                        bgcolor=ft.Colors.BLUE_600 if is_user else ft.Colors.SURFACE_CONTAINER_HIGH,
                        padding=ft.Padding(16, 12, 16, 12),
                        border_radius=ft.BorderRadius(
                            top_left=16,
                            top_right=16,
                            bottom_left=16 if is_user else 2,
                            bottom_right=2 if is_user else 16,
                        ),
                        width=bubble_width,
                    )
                ],
                alignment=ft.MainAxisAlignment.END if is_user else ft.MainAxisAlignment.START,
            )
        )

    # Ultra-Sleek Floating Elevated Header & AI Profile Banner
    elevated_header = ft.Container(
        padding=ft.Padding(16, 12, 16, 12),
        margin=ft.Margin(12, 12, 12, 6),
        bgcolor=ft.Colors.SURFACE,
        border_radius=16,
        border=ft.Border.all(1, ft.Colors.OUTLINE_VARIANT),
        shadow=ft.BoxShadow(
            blur_radius=16,
            color=ft.Colors.with_opacity(0.1, ft.Colors.BLACK),
            offset=ft.Offset(0, 4)
        ),
        content=ft.Column(
            spacing=10,
            tight=True,
            controls=[
                # Top Navigation Row
                ft.Row(
                    alignment=ft.MainAxisAlignment.SPACE_BETWEEN,
                    controls=[
                        ft.Row(
                            controls=[
                                ft.IconButton(
                                    icon=ft.Icons.ARROW_BACK_ROUNDED,
                                    icon_size=22,
                                    tooltip=f"Go Back ({back_route})",
                                    style=ft.ButtonStyle(bgcolor=ft.Colors.SURFACE_CONTAINER_HIGH),
                                    on_click=lambda _: page.navigate(back_route)
                                ),
                                ft.Text(
                                    "AI Studio Workspace",
                                    size=18,
                                    weight=ft.FontWeight.BOLD,
                                    color=ft.Colors.ON_SURFACE
                                )
                            ],
                            spacing=10
                        ),
                        ft.Row(
                            controls=[
                                ModelSelector(compact=True),
                                ft.Container(
                                    padding=ft.Padding(8, 4, 10, 4),
                                    bgcolor=ft.Colors.GREEN_500,
                                    border_radius=12,
                                    content=ft.Row([
                                        ft.Icon(ft.Icons.CIRCLE, size=8, color=ft.Colors.WHITE),
                                        ft.Text("ONLINE", size=10, weight=ft.FontWeight.BOLD, color=ft.Colors.WHITE)
                                    ], spacing=4)
                                ),
                                ft.IconButton(
                                    icon=ft.Icons.DELETE_SWEEP_ROUNDED,
                                    icon_size=22,
                                    tooltip="Clear Chat History",
                                    on_click=handle_clear_history
                                )
                            ],
                            spacing=8
                        )
                    ]
                ),
                ft.Divider(height=1, thickness=1),
                # AI Profile Banner Info
                ft.Row(
                    alignment=ft.MainAxisAlignment.SPACE_BETWEEN,
                    controls=[
                        ft.Row(
                            controls=[
                                ft.Container(
                                    width=42,
                                    height=42,
                                    border_radius=21,
                                    bgcolor=ft.Colors.BLUE_600,
                                    alignment=ft.Alignment(0, 0),
                                    content=ft.Icon(ft.Icons.AUTO_AWESOME_ROUNDED, color=ft.Colors.WHITE, size=22)
                                ),
                                ft.Column(
                                    spacing=2,
                                    controls=[
                                        ft.Row([
                                            ft.Text(
                                                "Shadow EYE",
                                                size=15,
                                                weight=ft.FontWeight.BOLD,
                                                color=ft.Colors.ON_SURFACE
                                            ),
                                            ft.Container(
                                                content=ft.Text("PRO", size=9, weight=ft.FontWeight.BOLD, color=ft.Colors.WHITE),
                                                bgcolor=ft.Colors.PURPLE_600,
                                                padding=ft.Padding(6, 2, 6, 2),
                                                border_radius=4
                                            )
                                        ], spacing=8),
                                        ft.Text(
                                            "Powered by RangoonX,Inc.",
                                            size=11,
                                            color=ft.Colors.ON_SURFACE_VARIANT
                                        )
                                    ]
                                )
                            ],
                            spacing=12
                        )
                    ]
                )
            ]
        )
    )

    # return ft.Container()
    return ft.Container(
        padding=0,
        expand=True,
        content=ft.Column(
            spacing=0,
            expand=True,
            controls=[
                # Floating Elevated Profile & Header Banner
                elevated_header,
                
                # Scrollable Message History List
                ft.Container(
                    expand=True,
                    padding=ft.Padding(16, 8, 16, 8),
                    content=ft.ListView(
                        ref=listview_ref,
                        controls=chat_bubbles,
                        spacing=14,
                        auto_scroll=True,
                    )
                ),
                
                # Bottom Floating Input Controls (Native Rock-Solid Flet Layout)
                ft.Container(
                    padding=ft.Padding(16, 10, 16, 16),
                    bgcolor=ft.Colors.SURFACE,
                    border=ft.Border(top=ft.BorderSide(1, ft.Colors.OUTLINE_VARIANT)),
                    content=ft.Row(
                        controls=[
                            ft.TextField(
                                key=f"page_chat_input_{input_key}",
                                ref=input_ref,
                                hint_text="မေးမြန်းလိုသည်ကိုရေးပါ ...",
                                filled=True,
                                bgcolor=ft.Colors.SURFACE_CONTAINER_HIGH,
                                border_radius=24,
                                border_color=ft.Colors.OUTLINE_VARIANT,
                                focused_border_color=ft.Colors.BLUE_600,
                                prefix_icon=ft.Icons.AUTO_AWESOME_ROUNDED,
                                multiline=True,
                                min_lines=1,
                                max_lines=5,
                                text_style=ft.TextStyle(font_family=AppFonts.MYANMAR, size=14),
                                content_padding=ft.Padding(14, 10, 14, 10),
                                expand=True,
                                on_change=handle_input_change,
                            ),
                            ft.IconButton(
                                icon=ft.Icons.SEND_ROUNDED,
                                icon_color=ft.Colors.WHITE,
                                icon_size=22,
                                tooltip="Send Message",
                                style=ft.ButtonStyle(
                                    bgcolor=ft.Colors.BLUE_600,
                                    shape=ft.CircleBorder(),
                                    padding=ft.Padding(12, 12, 12, 12)
                                ),
                                on_click=send_message,
                            )
                        ],
                        spacing=10,
                        vertical_alignment=ft.CrossAxisAlignment.END
                    )
                )
            ]
        )
    )
