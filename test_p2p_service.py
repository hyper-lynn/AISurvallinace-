import os
import sys
import time
import logging

# Ensure src module is importable
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

from src.services.dahua_p2p_service import DahuaP2PService

logging.basicConfig(level=logging.INFO, format="[%(asctime)s] %(levelname)s - %(message)s")

def test_service():
    print("=== Testing DahuaP2PService ===")
    service = DahuaP2PService()

    print(f"Device SN from .env: {service.device_sn}")
    print(f"Device User from .env: {service.device_user}")
    print(f"Device Pass length: {len(service.device_pass)}")

    print("\n1. Initializing SDK...")
    success = service.initialize()
    print(f"Initialization status: {success}")
    assert success, "SDK initialization failed!"

    print("\n2. Testing P2P Stream start invocation...")
    # Attempting P2P stream request
    res = service.start_p2p_stream()
    print(f"Start P2P stream call returned: {res}")

    print("Waiting 2 seconds for callback responses...")
    time.sleep(2)

    print("\n3. Stopping stream...")
    stop_res = service.stop_p2p_stream()
    print(f"Stop stream returned: {stop_res}")

    print("\n=== Test Completed Successfully ===")

if __name__ == "__main__":
    test_service()
