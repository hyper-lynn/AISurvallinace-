import flet as ft
import datetime
import asyncio

@ft.component
def Clock():
    time_str, set_time_str = ft.use_state(datetime.datetime.now().strftime("%I:%M:%S %p"))
    
    def clock_effect():
        running = True
        
        async def update_clock():
            while running:
                current_time = datetime.datetime.now().strftime("%I:%M:%S %p")
                set_time_str(current_time)
                await asyncio.sleep(1.0)
                
        # Run update loop in background async task
        asyncio.create_task(update_clock())
        
        # Cleanup callback on component unmount
        def cleanup():
            nonlocal running
            running = False
            
        return cleanup

    ft.use_effect(clock_effect, [])
    
    return ft.Text(
        value=time_str,
        weight=ft.FontWeight.W_500,
        color=ft.Colors.ON_SURFACE,
        size=14
    )
