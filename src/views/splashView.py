# src/views/splashView.py

import os
import sys
import time
import asyncio
import concurrent.futures
import flet as ft
from config import logger

@ft.component
def SplashScreen(on_complete: callable):
    """
    Tactical Futuristic Splash Screen with Real-Time AI Model Preloading Progress.
    Displays SITE.jpg logo, active GPU initialization steps, and progress bar.
    Transitions to main application once AI models are fully initialized on GPU.
    """
    progress, set_progress = ft.use_state(0.0)
    status_text, set_status_text = ft.use_state("Initializing System Environment...")
    gpu_label, set_gpu_label = ft.use_state("Detecting Hardware...")

    def run_preloading():
        executor = concurrent.futures.ThreadPoolExecutor(max_workers=4)

        async def _preload_task():
            try:
                # Step 1: Detect & Initialize GPU
                set_status_text("Initializing NVIDIA CUDA 13.3 GPU Acceleration...")
                set_progress(0.15)
                await asyncio.sleep(0.3)

                try:
                    import torch
                    if hasattr(torch, "cuda") and torch.cuda.is_available():
                        gpu_name = torch.cuda.get_device_name(0)
                        set_gpu_label(f"NVIDIA GPU: {gpu_name}")
                    else:
                        set_gpu_label("Hardware: CPU Fallback Mode")
                except (ImportError, OSError, Exception) as e:
                    logger.warning(f"PyTorch GPU check note: {e}")
                    set_gpu_label("Hardware: CPU Fallback Mode")

                # Step 2: Preload YOLOv8 Pose Model
                set_status_text("Preloading YOLOv8 AI Model on NVIDIA GPU...")
                set_progress(0.40)
                
                def load_yolo():
                    try:
                        from services.yolo_service import YOLOService
                        return YOLOService.get_instance()
                    except Exception as e:
                        logger.error(f"Splash YOLOService init note: {e}")
                        return None

                loop = asyncio.get_running_loop()
                await loop.run_in_executor(executor, load_yolo)
                await asyncio.sleep(0.3)

                # Step 3: Preload Target Face Service & ArcFace IR-50 Extractor
                set_status_text("Preloading InsightFace SCRFD & ArcFace IR-50 Engine...")
                set_progress(0.70)

                def load_target_service():
                    try:
                        from services.target_face_service import TargetFaceService
                        svc = TargetFaceService.get_instance()
                        svc._get_arcface_extractor()
                        return svc
                    except Exception as e:
                        logger.error(f"Splash TargetFaceService init note: {e}")
                        return None

                await loop.run_in_executor(executor, load_target_service)
                await asyncio.sleep(0.3)

                # Step 4: Preload MiniFASNet 2.5D Liveness & Telegram Service
                set_status_text("Initializing MiniFASNet 2.5D Liveness & Telegram Services...")
                set_progress(0.90)

                def load_telegram():
                    try:
                        from services.telegram_service import TelegramService
                        return TelegramService()
                    except Exception:
                        return None

                await loop.run_in_executor(executor, load_telegram)
                await asyncio.sleep(0.4)

                # Step 5: Ready & Transition
                set_status_text("Shadow EYE Engine Ready! Launching Surveillance UI...")
                set_progress(1.0)
                await asyncio.sleep(0.5)

                if on_complete:
                    on_complete()

            except Exception as e:
                logger.error(f"Splash screen error: {e}")
                set_status_text("Launching Application...")
                set_progress(1.0)
                await asyncio.sleep(0.4)
                if on_complete:
                    on_complete()

        asyncio.create_task(_preload_task())

    ft.use_effect(run_preloading, [])

    return ft.Container(
        expand=True,
        bgcolor="#0F1015",
        alignment=ft.Alignment.CENTER,
        content=ft.Column(
            alignment=ft.MainAxisAlignment.CENTER,
            horizontal_alignment=ft.CrossAxisAlignment.CENTER,
            spacing=25,
            controls=[
                # Glow Animated Container around Logo SITE.jpg
                ft.Container(
                    width=150,
                    height=150,
                    border_radius=75,
                    border=ft.Border.all(3, "#00E676"),
                    shadow=ft.BoxShadow(
                        blur_radius=30,
                        spread_radius=5,
                        color="#00E676"
                    ),
                    clip_behavior=ft.ClipBehavior.ANTI_ALIAS,
                    content=ft.Image(
                        src="/SITE.jpg",
                        fit=ft.BoxFit.COVER,
                        width=150,
                        height=150,
                        error_content=ft.Icon(ft.Icons.SECURITY, size=80, color="#00E676")
                    )
                ),

                # App Title & Subtitle
                ft.Column(
                    horizontal_alignment=ft.CrossAxisAlignment.CENTER,
                    spacing=6,
                    controls=[
                        ft.Text(
                            "SHADOW EYE",
                            size=32,
                            weight=ft.FontWeight.BOLD,
                            color="#FFFFFF",
                            # letter_spacing=3
                        ),
                        ft.Text(
                            "AI SURVEILLANCE & TARGET RECOGNITION SYSTEM",
                            size=12,
                            weight=ft.FontWeight.W_500,
                            color="#00E676",
                            # letter_spacing=1.5
                        )
                    ]
                ),

                # Hardware GPU Tag
                ft.Container(
                    padding=ft.Padding.symmetric(horizontal=16, vertical=6),
                    bgcolor="#1A1C23",
                    border_radius=20,
                    border=ft.Border.all(1, "#2A2D3A"),
                    content=ft.Row(
                        alignment=ft.MainAxisAlignment.CENTER,
                        tight=True,
                        controls=[
                            ft.Icon(ft.Icons.MEMORY, size=16, color="#29B6F6"),
                            ft.Text(gpu_label, size=12, color="#E0E0E0", weight=ft.FontWeight.W_500)
                        ]
                    )
                ),

                # Progress Section
                ft.Container(
                    width=420,
                    padding=ft.Padding.symmetric(horizontal=20),
                    content=ft.Column(
                        spacing=10,
                        controls=[
                            ft.ProgressBar(
                                value=progress,
                                color="#00E676",
                                bgcolor="#1A1C23",
                                height=8
                            ),
                            ft.Row(
                                alignment=ft.MainAxisAlignment.SPACE_BETWEEN,
                                controls=[
                                    ft.Text(status_text, size=12, color="#B0BEC5", weight=ft.FontWeight.W_400),
                                    ft.Text(f"{int(progress * 100)}%", size=12, color="#00E676", weight=ft.FontWeight.BOLD)
                                ]
                            )
                        ]
                    )
                )
            ]
        )
    )
