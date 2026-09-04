# run_api_server.py
"""
Shadow EYE - FastAPI Face Detection & Recognition Server Launcher
Runs the FastAPI server on host 0.0.0.0, port 8000 for mobile devices, iOS, Android, and Web PWA.
"""

import sys
import os
import uvicorn

# Ensure src directory is in Python path
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "src"))

if __name__ == "__main__":
    print("===============================================================")
    print("  Shadow EYE - FastAPI Face Detection & Recognition Backend   ")
    print("===============================================================")
    print("  Server binding to: http://0.0.0.0:8000                     ")
    print("  Local access:      http://localhost:8000                   ")
    print("  Swagger API Docs:  http://localhost:8000/docs              ")
    print("===============================================================\n")

    # Run Uvicorn with multi-worker / asynchronous request support for iOS, Android & Web PWA
    workers = int(os.environ.get("UVICORN_WORKERS", "4"))
    print(f"  Multi-device Worker process count: {workers}")
    uvicorn.run("api.face_api:app", host="0.0.0.0", port=8000, workers=workers, reload=False)
