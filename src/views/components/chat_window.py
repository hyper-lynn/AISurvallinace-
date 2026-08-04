# src/views/components/chat_window.py

import flet as ft
import asyncio
from services.ai_service import generate_ai_response, download_media_file, get_active_model
from services.chat_service import ChatService
from views.components.model_selector import ModelSelector
from config.fonts import AppFonts
from core.auth_context import use_user

@ft.component
def AIChatOverlay():
    page = ft.context.page
    user = use_user()
    chat_service = ft.use_memo(lambda: ChatService(), [])
    
    # Responsive window dimensions based on page size
    page_width = page.width if page.width else 800
    page_height = page.height if page.height else 600
    
    # Responsive chat width & height
    chat_width = min(380, page_width - 20)
    chat_height = min(500, page_height - 80)
    
    # Window visibility state
    visible, set_visible = ft.use_state(False)
    
    # Declarative Position state (React-style component hook)
    default_left = max(20.0, page_width - chat_width - 40)
    default_top = max(20.0, page_height - chat_height - 100)
    
    left, set_left = ft.use_state(default_left)
    top, set_top = ft.use_state(default_top)
    
    # Keep left and top within screen bounds if resized
    if left + chat_width > page_width:
        left = max(10.0, page_width - chat_width - 20)
    if top + chat_height > page_height:
        top = max(10.0, page_height - chat_height - 20)
        
    # Always fetch latest messages directly from SQLite3 database
    user_id = user.id if user else None
    db_messages = ft.use_memo(lambda: chat_service.get_messages(user_id), [user_id])
    messages, set_messages = ft.use_state(db_messages)
    
    # Key state for resetting input field declaratively on submit
    input_key, set_input_key = ft.use_state(0)
    input_ref = ft.use_ref()
    listview_ref = ft.use_ref()

    # Hide floating AI chat overlay when inside AI Workspace page (/ai-chat)
    curr_route = page.route if (page and page.route) else ""
    if curr_route.startswith("/ai-chat"):
        return ft.Container()
    
    # Declarative Drag event handler
    def on_drag(e: ft.DragUpdateEvent):
        new_left = max(0.0, min(left + e.local_delta.x, page_width - chat_width))
        new_top = max(0.0, min(top + e.local_delta.y, page_height - chat_height))
        set_left(new_left)
        set_top(new_top)

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
    max_bubble_width = max(260, min(340, chat_width - 40))
    
    for msg in messages:
        is_user = msg["sender"] == "User"
        is_typing = msg.get("typing", False)
        media_type = msg.get("media_type")
        media_url = msg.get("media_url")
        
        text_len = len(msg["text"])
        est_width = text_len * 9 + 28
        bubble_width = min(max_bubble_width, est_width) if text_len < 28 else max_bubble_width

        # Media controls (Images & Videos)
        media_controls = []
        if media_type == "image" and media_url:
            media_controls.append(
                ft.Image(
                    src=media_url,
                    width=280,
                    height=200,
                    fit=ft.BoxFit.COVER,
                    border_radius=10
                )
            )
            media_controls.append(
                ft.Button(
                    "Save Image",
                    icon=ft.Icons.DOWNLOAD_ROUNDED,
                    style=ft.ButtonStyle(padding=ft.Padding(10, 6, 10, 6)),
                    on_click=lambda e, u=media_url: download_media_file(page, u, "image")
                )
            )
        elif media_type == "video" and media_url:
            media_controls.append(
                ft.Container(
                    width=280,
                    height=160,
                    bgcolor=ft.Colors.BLACK87,
                    border_radius=10,
                    alignment=ft.Alignment(0, 0),
                    content=ft.Column(
                        alignment=ft.MainAxisAlignment.CENTER,
                        horizontal_alignment=ft.CrossAxisAlignment.CENTER,
                        controls=[
                            ft.Icon(ft.Icons.PLAY_CIRCLE_FILL_ROUNDED, color=ft.Colors.WHITE, size=44),
                            ft.Text("AI Video Generated", color=ft.Colors.WHITE, size=12, weight=ft.FontWeight.BOLD)
                        ],
                        spacing=4
                    )
                )
            )
            media_controls.append(
                ft.Button(
                    "Save Video",
                    icon=ft.Icons.DOWNLOAD_ROUNDED,
                    style=ft.ButtonStyle(padding=ft.Padding(10, 6, 10, 6)),
                    on_click=lambda e, u=media_url: download_media_file(page, u, "video")
                )
            )

        if is_typing:
            column_controls = [
                ft.Row(
                    controls=[
                        ft.ProgressRing(width=16, height=16, stroke_width=2, color=ft.Colors.BLUE_600),
                        ft.Text(
                            msg["text"],
                            color=ft.Colors.ON_SURFACE,
                            size=12,
                            italic=True,
                            font_family=AppFonts.MYANMAR
                        )
                    ],
                    spacing=8
                )
            ]
        else:
            column_controls = [
                ft.Text(
                    msg["text"],
                    color=ft.Colors.WHITE if is_user else ft.Colors.ON_SURFACE,
                    size=13,
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
                            spacing=8
                        ),
                        bgcolor=ft.Colors.BLUE_600 if is_user else ft.Colors.SURFACE_CONTAINER_HIGH,
                        padding=ft.Padding(12, 10, 12, 10),
                        border_radius=ft.BorderRadius(
                            top_left=14,
                            top_right=14,
                            bottom_left=14 if is_user else 2,
                            bottom_right=2 if is_user else 14,
                        ),
                        width=bubble_width,
                    )
                ],
                alignment=ft.MainAxisAlignment.END if is_user else ft.MainAxisAlignment.START,
            )
        )

    # AI Profile banner
    ai_profile_banner = ft.Container(
        padding=ft.Padding(12, 6, 12, 6),
        bgcolor=ft.Colors.SURFACE_CONTAINER_LOW,
        border=ft.Border(bottom=ft.BorderSide(1, ft.Colors.OUTLINE_VARIANT)),
        content=ft.Row(
            alignment=ft.MainAxisAlignment.SPACE_BETWEEN,
            controls=[
                ft.Row(
                    controls=[
                        ft.CircleAvatar(
                            content=ft.Icon(ft.Icons.AUTO_AWESOME_ROUNDED, color=ft.Colors.WHITE, size=14),
                            radius=12,
                            bgcolor=ft.Colors.BLUE_600
                        ),
                        ft.Column(
                            spacing=0,
                            controls=[
                                ft.Text(
                                    "Shadow EYE AI Assistant",
                                    size=11,
                                    weight=ft.FontWeight.BOLD,
                                    color=ft.Colors.ON_SURFACE
                                ),
                                # ft.Text(
                                #     "Enter 2x / Click Send to Submit",
                                #     size=9,
                                #     color=ft.Colors.ON_SURFACE_VARIANT
                                # )
                            ]
                        )
                    ],
                    spacing=8
                ),
                ft.IconButton(
                    icon=ft.Icons.DELETE_SWEEP_ROUNDED,
                    icon_size=18,
                    tooltip="Clear Chat History",
                    on_click=handle_clear_history
                )
            ]
        )
    )

    # Open full page callback handler
    def open_full_page(e):
        page.navigate("/ai-chat")

    # Draggable Chat Box UI
    chat_box = ft.Container(
        left=left,
        top=top,
        width=chat_width,
        height=chat_height,
        bgcolor=ft.Colors.SURFACE,
        border=ft.Border.all(1, ft.Colors.OUTLINE_VARIANT),
        border_radius=16,
        shadow=ft.BoxShadow(
            blur_radius=20,
            color=ft.Colors.with_opacity(0.15, ft.Colors.BLACK),
            offset=ft.Offset(0, 8),
        ),
        clip_behavior=ft.ClipBehavior.ANTI_ALIAS,
        visible=visible,
        content=ft.Column(
            spacing=0,
            controls=[
                # Drag Header
                ft.GestureDetector(
                    on_pan_update=on_drag,
                    content=ft.Container(
                        bgcolor=ft.Colors.BLUE_600,
                        padding=ft.Padding(10, 8, 10, 8),
                        content=ft.Row(
                            controls=[
                                ft.Row(
                                    controls=[
                                        ft.Icon(ft.Icons.AUTO_AWESOME_ROUNDED, color=ft.Colors.WHITE, size=16),
                                        ft.Text("AI Assistant", color=ft.Colors.WHITE, weight=ft.FontWeight.BOLD, size=13),
                                    ],
                                    spacing=6
                                ),
                                ft.Row(
                                    controls=[
                                        ModelSelector(compact=True),
                                        ft.IconButton(
                                            icon=ft.Icons.OPEN_IN_NEW_ROUNDED,
                                            icon_color=ft.Colors.WHITE,
                                            icon_size=16,
                                            tooltip="Open Full Page",
                                            padding=0,
                                            on_click= open_full_page
                                        ),
                                        ft.IconButton(
                                            icon=ft.Icons.CLOSE_ROUNDED,
                                            icon_color=ft.Colors.WHITE,
                                            icon_size=16,
                                            padding=0,
                                            on_click=lambda _: set_visible(False)
                                        )
                                    ],
                                    spacing=2
                                )
                            ],
                            alignment=ft.MainAxisAlignment.SPACE_BETWEEN
                        ),
                    )
                ),
                # AI Profile Banner
                ai_profile_banner,
                # Chat History Scrollable List
                ft.Container(
                    expand=True,
                    padding=10,
                    content=ft.ListView(
                        ref=listview_ref,
                        controls=chat_bubbles,
                        spacing=10,
                        auto_scroll=True,
                    )
                ),
                # Divider
                ft.Divider(height=1, thickness=1),
                # Chat Input Area (Native Rock-Solid Flet Layout)
                ft.Container(
                    padding=8,
                    bgcolor=ft.Colors.SURFACE_CONTAINER_LOW,
                    content=ft.Row(
                        controls=[
                            ft.TextField(
                                key=f"chat_input_{input_key}",
                                ref=input_ref,
                                hint_text="မေးမြန်းလိုသည်များ ရေးပါ...",
                                filled=True,
                                bgcolor=ft.Colors.SURFACE_CONTAINER_HIGH,
                                border_radius=20,
                                border_color=ft.Colors.OUTLINE_VARIANT,
                                focused_border_color=ft.Colors.BLUE_600,
                                prefix_icon=ft.Icons.AUTO_AWESOME_ROUNDED,
                                multiline=True,
                                min_lines=1,
                                max_lines=3,
                                text_style=ft.TextStyle(font_family=AppFonts.MYANMAR, size=13),
                                content_padding=ft.Padding(10, 6, 10, 6),
                                expand=True,
                                on_change=handle_input_change,
                            ),
                            ft.IconButton(
                                icon=ft.Icons.SEND_ROUNDED,
                                icon_color=ft.Colors.BLUE_600,
                                icon_size=20,
                                on_click=send_message,
                            )
                        ],
                        spacing=4,
                        vertical_alignment=ft.CrossAxisAlignment.END
                    )
                )
            ]
        )
    )

    # Circular toggle floating button
    toggle_btn = ft.Container(
        bottom=20,
        right=20,
        content=ft.FloatingActionButton(
            icon=ft.Icons.CHAT_ROUNDED,
            on_click=lambda _: set_visible(not visible),
            bgcolor=ft.Colors.BLUE_600,
            content=ft.Icon(ft.Icons.AUTO_AWESOME_ROUNDED, color=ft.Colors.WHITE),
        )
    )

    if not visible:
        return toggle_btn

    return ft.Stack(
        controls=[
            chat_box,
            toggle_btn
        ]
    )
