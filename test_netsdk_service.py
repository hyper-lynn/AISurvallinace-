import os
import sys
import time
import logging

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

from src.services.dahua_netsdk_service import DahuaNetSDKService

logging.basicConfig(level=logging.INFO, format="[%(asctime)s] %(levelname)s - %(message)s")

def test_netsdk():
    print("=== Testing Dahua General NetSDK Service (dhnetsdk.dll) ===")
    service = DahuaNetSDKService.get_instance()

    print(f"Target Device IP: {service.ip}:{service.port}")
    print(f"Target User: {service.user}")

    print("\n1. Logging in via Direct NetSDK TCP...")
    success = service.connect()
    print(f"Login success: {success}")
    assert success, "Dahua NetSDK login failed!"

    sn = service.get_serial_number()
    channels = service.get_total_channels()

    print(f"\n2. Verified Device Info:")
    print(f"   - Serial Number: {sn}")
    print(f"   - Total Channels: {channels}")

    print("\n3. Testing Channel 0 RealPlay Stream Handle Creation...")
    play_handle = service.start_channel_stream(channel=0, hwnd_ptr=0)
    print(f"RealPlay PlayHandle: {play_handle}")
    assert play_handle > 0, "Failed to start RealPlay stream!"

    print("Streaming active for 2 seconds...")
    time.sleep(2)

    print("\n4. Testing PTZ Control (Move Up)...")
    ptz_res = service.ptz_move_up(channel=0, speed=4, stop=False)
    print(f"PTZ Move Up: {ptz_res}")
    time.sleep(0.5)
    service.ptz_move_up(channel=0, speed=4, stop=True)

    print("\n5. Cleaning up and disconnecting...")
    service.disconnect()
    print("\n=== Dahua General NetSDK Test Completed Successfully! ===")

if __name__ == "__main__":
    test_netsdk()
