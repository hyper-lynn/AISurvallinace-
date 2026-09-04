import os
import urllib.request
from pathlib import Path
import ssl

def download_file(url, dest):
    print(f"Downloading {url} to {dest}...")
    try:
        # Create unverified context for potential SSL issues
        ctx = ssl.create_default_context()
        ctx.check_hostname = False
        ctx.verify_mode = ssl.CERT_NONE
        
        with urllib.request.urlopen(url, context=ctx) as response:
            with open(dest, 'wb') as out_file:
                out_file.write(response.read())
        print(f"Download complete: {dest.name}")
    except Exception as e:
        print(f"Failed to download {url}: {e}")

def main():
    base_dir = Path(__file__).parent.resolve()
    models_dir = base_dir / "assets" / "models"
    models_dir.mkdir(parents=True, exist_ok=True)
    
    models = [
        {
            "name": "yolov8n-pose.pt",
            "url": "https://github.com/ultralytics/assets/releases/download/v8.2.0/yolov8n-pose.pt"
        },
        {
            "name": "yolov8s-pose.pt",
            "url": "https://github.com/ultralytics/assets/releases/download/v8.2.0/yolov8s-pose.pt"
        },
        {
            "name": "face_detection_yunet_2023mar.onnx",
            "url": "https://github.com/opencv/opencv_zoo/raw/main/models/face_detection_yunet/face_detection_yunet_2023mar.onnx"
        }
    ]
    
    for model in models:
        dest_path = models_dir / model["name"]
        if not dest_path.exists():
            download_file(model["url"], dest_path)
        else:
            print(f"Model {model['name']} already exists at {dest_path}. Skipping.")

if __name__ == "__main__":
    print("Starting model download process...")
    main()
    print("Done.")
