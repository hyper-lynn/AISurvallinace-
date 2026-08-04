# mobile_view_main.py (Root Launcher for Flet APK build)
import sys
import os

SRC_DIR = os.path.join(os.path.dirname(os.path.abspath(__file__)), "src")
if SRC_DIR not in sys.path:
    sys.path.insert(0, SRC_DIR)

from mobile_view_main import main
import flet as ft

if __name__ == "__main__":
    ft.app(target=main, assets_dir="src/assets")
