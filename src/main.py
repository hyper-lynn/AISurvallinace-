#src/main.py

import os
import sys
import glob
import ctypes
import site

# Configure OpenCV FFmpeg RTSP stream options globally before cv2 is loaded
# Forces TCP transport to prevent UDP packet loss and H.264 macroblock decoding errors
os.environ["OPENCV_FFMPEG_CAPTURE_OPTIONS"] = "rtsp_transport;tcp|stimeout;5000000|probesize;32|analyzeduration;0|fflags;nobuffer|flags;low_delay|max_delay;0"
os.environ["OPENCV_LOG_LEVEL"] = "OFF"

# Preload CUDA 13 / 12 & cuDNN DLLs for ONNX Runtime & PyTorch GPU
try:
    possible_dll_dirs = [
        r"C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v13.3\bin\x64",
        r"C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v13.3\bin",
        r"C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v12.4\bin",
        r"C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v12.1\bin",
    ]
    for sp in site.getsitepackages():
        nvidia_base = os.path.join(sp, "nvidia")
        if os.path.exists(nvidia_base):
            for pkg in os.listdir(nvidia_base):
                for sub in ["bin", "lib"]:
                    candidate = os.path.join(nvidia_base, pkg, sub)
                    if os.path.exists(candidate):
                        possible_dll_dirs.append(candidate)
        t_lib = os.path.join(sp, "torch", "lib")
        if os.path.exists(t_lib):
            possible_dll_dirs.append(t_lib)

    user_home = os.path.expanduser("~")
    global_py_pattern = os.path.join(user_home, "AppData", "Local", "Programs", "Python", "Python*", "Lib", "site-packages", "torch", "lib")
    for g_path in glob.glob(global_py_pattern):
        if os.path.exists(g_path) and g_path not in possible_dll_dirs:
            possible_dll_dirs.append(g_path)

    for ddir in possible_dll_dirs:
        if os.path.exists(ddir):
            os.environ["PATH"] = ddir + os.pathsep + os.environ.get("PATH", "")
            if hasattr(os, "add_dll_directory"):
                try:
                    os.add_dll_directory(ddir)
                except Exception:
                    pass

    critical_cuda_dlls = ["cublas64_12.dll", "cudnn64_9.dll", "cudnn64_8.dll", "zlibwapi.dll", "cudart64_12.dll", "cufft64_11.dll", "curand64_10.dll", "cusparse64_12.dll"]
    for ddir in possible_dll_dirs:
        if os.path.exists(ddir):
            for target_dll in critical_cuda_dlls:
                full_dll_path = os.path.join(ddir, target_dll)
                if os.path.exists(full_dll_path):
                    try:
                        ctypes.CDLL(full_dll_path)
                    except Exception:
                        pass
except Exception:
    pass

import flet as ft 

from config import logger
from config.fonts import AppFonts
from config.colors import get_app_theme
from core.routerApp import routingApp
from views.splashView import SplashScreen

async def main(page:ft.Page):
    
    try:
        logger.info("Shadow Eye is trying to start!")
        page.fonts = AppFonts.FONTS_MAPPING
        page.title = "Shadow EYE"
        page.window.icon = r"images/logo.ico"
        page.padding = 0
        
        await page.window.center()
        page.window.full_screen = True
        
        # Apply custom themes before rendering
        try:
            page.theme = get_app_theme(ft.ThemeMode.LIGHT)
            page.dark_theme = get_app_theme(ft.ThemeMode.DARK)
            logger.info("Custom themes applied successfully")
        except Exception as e:
            logger.error(f"Failed to apply custom themes: {e}")

        def launch_main_app():
            try:
                page.render(routingApp)
                logger.info("Shadow EYE Main UI rendered successfully after AI model preloading.")
            except Exception as render_e:
                logger.error(f"Failed to render main application UI: {render_e}")

        # Render Futuristic Splash Screen with Logo SITE.jpg & AI Preloader
        page.render(lambda: SplashScreen(on_complete=launch_main_app))
        
    except Exception as e:
        logger.debug(f"Shadow EYE failed to start: {e}")
    

if __name__ == "__main__":
    ft.run(main,assets_dir="assets" , view=ft.AppView.FLET_APP)

    
# import flet as ft

# def main(page: ft.Page):
#     # Font file ကို ချိတ်ဆက်ခြင်း (assets folder ထဲမှာ font ရှိရပါမယ်)
#     page.fonts = {
#         "Pyidaungsu": "/fonts/Pyidaungsu.ttf" 
#     }
    
#     # App တစ်ခုလုံးအတွက် Default Font ကို Pyidaungsu အဖြစ် သတ်မှတ်ခြင်း
#     page.theme = ft.Theme(font_family="Pyidaungsu")

#     tf = ft.TextField(label="ဒီမှာ ရိုက်ကြည့်ပါ", text_size=20)
#     page.add(tf)

# ft.app(target=main, assets_dir="assets")