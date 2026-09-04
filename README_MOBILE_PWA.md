# 📱 Shadow EYE - Mobile & Web PWA Face Scanner Guide

This guide explains how to run the **FastAPI Face Detection Backend Server** and launch the **Flet Mobile & Web PWA App** with **React-Style Hooks (`@ft.component`, `ft.use_state`, `ft.use_effect`)**.

---

## 🚀 1. Start FastAPI Backend Server

Open a terminal and start the FastAPI server:

```bash
python run_api_server.py
```

- **Local Endpoint**: `http://localhost:8000`
- **Network Endpoint** (for iOS / Android devices on Wi-Fi): `http://<YOUR_LOCAL_IP>:8000` (e.g. `http://192.168.1.100:8000`)
- **Interactive Swagger API Docs**: `http://localhost:8000/docs`

### Key API Endpoints:
- `POST /api/v1/detect-face` : Detect faces, perform 2.5D liveness check, match against registered SQLite targets.
- `POST /api/v1/compare-faces` : Compare 2 face photos & calculate similarity score.
- `POST /api/v1/register-face` : Add new target face profile into SQLite DB.
- `GET /api/v1/target-faces` : Fetch registered target faces list.
- `GET /api/v1/health` : Health check and model status indicator.

---

## 🌐 2. Run Flet Web Application (PWA Mode)

To run as a **Responsive Web App (PWA)** in your browser:

```bash
flet run --web mobile_view_main.py
```

This launches the PWA app at `http://localhost:8502` or next available port. iOS and Android devices connected to the same network can access the PWA via browser.

---

## 📱 3. Build & Run Native Mobile App (iOS / Android)

### Run on iOS Device / Simulator:
```bash
flet run --ios mobile_view_main.py
```

### Run on Android Device / Emulator:
```bash
flet run --android mobile_view_main.py
```

### Build Standalone Android APK:
```bash
flet build apk mobile_view_main.py
```

---

## ✨ Features Included:
1. **React-Style State Hooks**: Architecture powered by `@ft.component`, `ft.use_state`, and `ft.use_effect`.
2. **Camera Face Detection**: Native mobile & web camera scanning with Base64 JSON payload streaming to FastAPI.
3. **Face Bounding Box & Reticle**: Visual bounding box overlay with match score, liveness score, and VIP role tags.
4. **2-Photo Face Comparison**: Side-by-side photo selector tool with progress bar similarity metric.
5. **Target Faces Database**: Manage VIP profiles directly stored in SQLite database (`data/target_faces.db`).
6. **Mobile & Web Responsive Design**: Sleek dark glassmorphism design with bottom navigation bar for mobile view and adaptive layout.
