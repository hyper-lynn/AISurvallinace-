# src/mobile_view_main.py
"""
Flet Launcher for Mobile & Web PWA Application (Inside src/)
Used when running:
  - flet run mobile_view_main.py
  - flet run --web mobile_view_main.py
  - flet run --ios mobile_view_main.py
  - flet run --android mobile_view_main.py
"""

import sys
import os
import flet as ft

# Add parent directory and src to sys.path
SRC_DIR = os.path.dirname(os.path.abspath(__file__))
if SRC_DIR not in sys.path:
    sys.path.insert(0, SRC_DIR)

from views.mobile_face_scanner import main

if __name__ == "__main__":
    ft.run(main)
