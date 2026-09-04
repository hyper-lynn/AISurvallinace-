import flet as ft
import asyncio
import socket
from core.helper import use_loc

@ft.component
def StatusIndicator():
    """
    Real-time system status indicator.
    Pings a lightweight check to determine online/offline status.
    Props: 
        - check_interval (int): seconds between checks (default 5)
    """
    loc = use_loc()
    is_online, set_is_online = ft.use_state(True)

    def status_effect():
        running = True

        async def check_status():
            while running:
                try:
                    # Minimal async network check
                    loop = asyncio.get_event_loop()
                    online = await loop.run_in_executor(None, _check_connectivity)
                    set_is_online(online)
                except Exception:
                    set_is_online(False)
                await asyncio.sleep(5.0)

        asyncio.create_task(check_status())

        def cleanup():
            nonlocal running
            running = False

        return cleanup

    ft.use_effect(status_effect, [])

    status_label = loc("system_online") if is_online else loc("system_offline")
    dot_color = ft.Colors.GREEN_500 if is_online else ft.Colors.RED_500

    return ft.Row(
        spacing=6,
        vertical_alignment=ft.CrossAxisAlignment.CENTER,
        controls=[
            ft.Container(
                width=9,
                height=9,
                border_radius=5,
                bgcolor=dot_color,
                animate=ft.Animation(duration=400, curve=ft.AnimationCurve.EASE_IN_OUT),
            ),
            ft.Text(
                value=status_label,
                weight=ft.FontWeight.W_500,
                color=ft.Colors.ON_SURFACE,
                size=14,
            )
        ]
    )


def _check_connectivity() -> bool:
    """
    Fail-safe non-raising connectivity check - runs in thread executor.
    Uses direct numeric IP addresses (no DNS lookup) and connect_ex to prevent gaierror.
    """
    # Direct numeric IPv4 addresses avoid DNS getaddrinfo gaierror completely!
    raw_ip_targets = [
        ("1.1.1.1", 80),
        ("8.8.8.8", 80),
        ("1.0.0.1", 80),
        ("8.8.4.4", 80)
    ]
    for ip_addr, port in raw_ip_targets:
        s = None
        try:
            s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            s.settimeout(0.5)
            res = s.connect_ex((ip_addr, port))
            if res == 0:
                s.close()
                return True
        except (socket.gaierror, TimeoutError, socket.timeout, socket.error, OSError, Exception):
            pass
        finally:
            if s:
                try:
                    s.close()
                except Exception:
                    pass
            
    return False


