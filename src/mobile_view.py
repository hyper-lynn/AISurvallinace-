# src/mobile_view.py
"""
Shadow EYE - Production Mobile & Web PWA Application Launcher
Entrypoint for Mobile iOS, Android Native APK, and Web PWA applications.
"""

import sys
import os
import socket
import logging
import flet as ft

# # Ensure src directory is in Python path
# SRC_DIR = os.path.dirname(os.path.abspath(__file__))
# if SRC_DIR not in sys.path:
#     sys.path.insert(0, SRC_DIR)

from views.mobile_face_scanner import MobileFaceScannerView

# def get_local_ip() -> str:
#     """Get machine's local network IP address for mobile connections"""
#     try:
#         s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
#         s.connect(("8.8.8.8", 80))
#         ip = s.getsockname()[0]
#         s.close()
#         return ip
#     except Exception:
#         return "127.0.0.1"

async def main(page: ft.Page):
    """Production Mobile & Web PWA Entry Point"""
    page.title = "Shadow EYE - Mobile Face AI Scanner"
    page.theme_mode = ft.ThemeMode.DARK
    page.padding = 0
    page.spacing = 0

    # Render Mobile Face Scanner View Component wrapped in SafeArea
    scanner_view = MobileFaceScannerView(page)
    page.add(ft.SafeArea(content=scanner_view, expand=True))

if __name__ == "__main__":
    # local_ip = get_local_ip()
    # port = 8550

    # print("====================================================================")
    # print("  Shadow EYE - Production Mobile & Web Application Launcher          ")
    # print("====================================================================")
    # print(f"  Local Web Access:       http://localhost:{port}")
    # print(f"  Network / Mobile IP:    http://{local_ip}:{port}")
    # print("====================================================================")
    # print("  📲 HOW TO CONNECT FROM MOBILE DEVICES (ANDROID & IOS):            ")
    # print("  ------------------------------------------------------------------")
    # print(f"  1. Web Mobile PWA (Safari / Chrome): http://{local_ip}:{port}")
    # print(f"  2. Android & iOS Native App:        http://{local_ip}:8000")
    # print("====================================================================\n")

    # Run Flet in WEB_BROWSER mode on 0.0.0.0 for multi-device mobile access
    # ft.run(main, host="0.0.0.0", port=port, view=ft.AppView.mobi, assets_dir="assets")
    ft.run(main, assets_dir="assets")

    
