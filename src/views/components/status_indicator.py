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
    Fail-safe blocking connectivity check - runs in thread executor.
    Uses HTTP port 80 over standard DNS IPs to avoid ISP TCP 53 port blocks and debugger timeouts.
    """
    targets = [
        ("1.1.1.1", 80),
        ("8.8.8.8", 80),
        ("google.com", 80)
    ]
    for host, port in targets:
        try:
            with socket.create_connection((host, port), timeout=1.5):
                return True
        except (socket.timeout, socket.error, TimeoutError, OSError, Exception):
            continue
            
    return False
