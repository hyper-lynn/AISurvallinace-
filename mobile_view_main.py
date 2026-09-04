# mobile_view_main.py
"""
Shadow EYE - Mobile Launcher Delegate
Redirects to src/mobile_view.py entrypoint.
"""

import sys
import os

SRC_DIR = os.path.join(os.path.dirname(os.path.abspath(__file__)), "src")
if SRC_DIR not in sys.path:
    sys.path.insert(0, SRC_DIR)

from mobile import main, get_local_ip
import flet as ft

if __name__ == "__main__":
    local_ip = get_local_ip()
    port = 8550

    print("====================================================================")
    print("  Shadow EYE - Production Mobile & Web Application Launcher          ")
    print("====================================================================")
    print(f"  Local Web Access:       http://localhost:{port}")
    print(f"  Network / Mobile IP:    http://{local_ip}:{port}")
    print("====================================================================\n")

    ft.run(main, host="0.0.0.0", port=port, view=ft.AppView.WEB_BROWSER, assets_dir="assets")
