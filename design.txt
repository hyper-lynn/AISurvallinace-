# 🤖 TELEGRAM BOT PORTAL & AI PROTOCOLS - DESIGN & FEATURE SPECIFICATION

> **System**: Shadow Eye (S-Eye) Intelligent Surveillance & AI Security Platform  
> **Module**: Telegram Bot Portal, AI Detection Layer & Gemini AI Assistant Studio  
> **Document Purpose**: Feature breakdown and layout architecture specification for UI/UX design (Stitch / Figma / Flet).

---

## 📑 TABLE OF CONTENTS
1. [Overview & Core Architecture](#1-overview--core-architecture)
2. [Telegram Bot Portal Feature Matrix](#2-telegram-bot-portal-feature-matrix)
3. [AI Vision & Detection Engine Features](#3-ai-vision--detection-engine-features)
4. [Automated Alert Dispatching System](#4-automated-alert-dispatching-system)
5. [Telegram Gemini AI Chat Assistant (Polling Listener)](#5-telegram-gemini-ai-chat-assistant-polling-listener)
6. [AI Security Policy & Guardrail Shield](#6-ai-security-policy--guardrail-shield)
7. [Operatives & Target Destinations Registry](#7-operatives--target-destinations-registry)
8. [UI/UX Layout Architecture & Design System Tokens](#8-uiux-layout-architecture--design-system-tokens)

---

## 1. OVERVIEW & CORE ARCHITECTURE

The **Telegram Bot Portal** serves as the primary external communication and remote-command gateway for the S-Eye platform. It integrates:
* **Telegram Bot API**: Instant photo snapshot dispatch and multi-recipient broadcasting.
* **YOLOv8 Pose AI Engine**: Real-time Human & Fall Pose Detection.
* **Gemini AI Pro Engine**: Conversational security assistant via Telegram chat.
* **SQLite3 Persistence Layer**: Stores bot tokens, targets, security policies, and camera profiles.

```
                    +-----------------------------------+
                    |   S-Eye Live Surveillance App     |
                    +-----------------+-----------------+
                                      |
         +----------------------------+----------------------------+
         |                                                         |
+--------v--------+                              +-----------------v---------------+
| YOLOv8 Pose AI  |                              | Telegram Bot Assistant Listener |
| (Human & Fall)  |                              | (Gemini AI Pro Integration)     |
+--------+--------+                              +-----------------+---------------+
         |                                                         |
         +----------------------------+----------------------------+
                                      |
                      +---------------v---------------+
                      | Telegram API Dispatcher Engine|
                      +---------------+---------------+
                                      |
          +---------------------------+---------------------------+
          |                           |                           |
+---------v---------+       +---------v---------+       +---------v---------+
| Operative Private |       | Tactical Security |       | Broadcast HQ      |
| Direct Telegram   |       | Group Chat (-100) |       | Public Channel    |
+-------------------+       +-------------------+       +-------------------+
```

---

## 2. TELEGRAM BOT PORTAL FEATURE MATRIX

| Feature ID | Feature Name | Description | Status / Tech Stack |
| :--- | :--- | :--- | :--- |
| **BOT-01** | **API Credentials Setup** | Bot Token & Global Chat ID entry with show/hide password toggle. | Configured / SQLite3 + `.env` |
| **BOT-02** | **Bot Connection Tester** | One-click instant connection test dispatch (`send_test_message`). | Active / `requests.post` |
| **BOT-03** | **Multi-Target Routing** | Route alerts to Camera-Specific Chat ID, Global Chat ID, or DB Operative Groups. | Active / Multi-destination |
| **BOT-04** | **Automated Photo Alerts** | Real-time JPEG snapshot dispatch with metadata caption on threat detection. | Active / Base64 to JPEG Bytes |
| **BOT-05** | **Alert Cooldown Manager**| 30-second rate limiting to prevent spamming Telegram chats. | Active / Time-based cooldown |
| **BOT-06** | **Gemini AI Chat Polling**| Background worker thread listening for incoming operator messages on Telegram. | Active / Threading Poller |
| **BOT-07** | **Remote System Commands**| Execute `/status`, `/cameras`, `/snapshot <id>`, `/ai_on`, `/alarm_on` via Telegram. | Active / Text Command Parser |
| **BOT-08** | **AI Security Guardrails**| Anti-Prompt Injection, Credential Theft Prevention & Privilege Access Control. | Active / Filter Layer |

---

## 3. AI VISION & DETECTION ENGINE FEATURES

* **Models Supported**:
  * `YOLOv8n-pose.pt` (Nano Pose Model - 6MB, 3x faster, primary choice for real-time CPU streaming).
  * `YOLOv8s-pose.pt` (Small Pose Model - High precision).
  * `OpenCV MOG2` (Ultra-fast motion background subtractor).
  * `Gemini 3.6 Flash` (Multimodal AI Scene Analysis & Verification).
* **Frame-Skipping & Box Caching Architecture**:
  * Runs YOLO inference once every 3 frames (`frame_count % 3 == 0`) with `imgsz=320`.
  * Intermediate frames draw cached bounding boxes for silky smooth 30 FPS video feed.
* **Strict Fall Detection Algorithm**:
  * Calculates Spine Vector Angle relative to ground ($\text{Spine Angle} = \arctan2(dy, dx)$).
  * True Fall condition: $(\text{Spine Angle} < 30^\circ \text{ OR } dy < 15\text{px}) \text{ AND } (\text{Width} > \text{Height} \times 1.25)$.
  * Eliminates false positives during sitting, standing, or walking.

---

## 4. AUTOMATED ALERT DISPATCHING SYSTEM

### Snapshot Alert Payload Format
When a **Human** or **Fall** is detected (with Alarm Mode Active):
1. Captures live frame buffer -> encodes to JPEG bytes.
2. Formats Telegram HTML Caption:
   ```html
   🚨 <b>S-Eye AI Security Alert</b>

   📹 <b>Camera Channel:</b> Front Gate CCTV (RTSP)
   🎯 <b>Detection Event:</b> HUMAN DETECTED / FALL DETECTED
   🧠 <b>AI Scan Engine:</b> YOLOv8n-pose
   📊 <b>Confidence Score:</b> 92.0%
   📢 <b>Target Destination:</b> <code>-1001234567890</code>
   ⏰ <b>Timestamp:</b> 2026-08-03 13:20:00

   <i>S-Eye Intelligent Surveillance System</i>
   ```
3. Dispatches via `sendPhoto` API to:
   - Primary: Camera Custom Chat ID
   - Secondary: Global Fallback Chat ID
   - Tertiary: Active Registered Operative Groups/Channels

---

## 5. TELEGRAM GEMINI AI CHAT ASSISTANT (POLLING LISTENER)

Allows authorized operators to chat directly with the bot on Telegram:
* **Interactive Command Menu**:
  * `/start` or `/help` -> Display interactive welcome guide & available commands.
  * `/status` -> System health, CPU/RAM usage, camera count, active alerts.
  * `/cameras` -> List all registered CCTV channels and RTSP sources.
  * `/snapshot <cam_id>` -> Instantly capture live photo snapshot from specific camera & send to chat.
  * `/ai_on` / `/ai_off` -> Remote toggle AI detection.
  * `/alarm_on` / `/alarm_off` -> Remote toggle Alarm alert dispatch mode.
* **Conversational AI Mode**:
  * Any text message (not starting with `/`) is processed by **Gemini AI Pro** with security context instructions.

---

## 6. AI SECURITY POLICY & GUARDRAIL SHIELD

Built-in security policy filter before sending prompt payloads to Gemini AI:
1. **Prompt Injection Filter**: Scans for and blocks jailbreak vectors (DAN, ignore instructions, system prompt override).
2. **Credential Theft Prevention**: Prevents leakage of `TELEGRAM_BOT_TOKEN`, `GEMINI_API_KEY`, database passwords, or system `.env` secrets.
3. **Privileged Access Control**: Restricts administrative database mutations to verified admin sessions.

---

## 7. OPERATIVES & TARGET DESTINATIONS REGISTRY

### Destination Types
* `user`: Individual Security Operatives (Direct Message).
* `group`: Tactical Fast-Response Group Chats (Numeric Chat ID starting with `-100`).
* `channel`: HQ Broadcast Public/Private Channels (`@seye_hq_alerts`).

### Profile Attributes
* `target_name`: Display Name (e.g. Maj. Arnold Miller, Tactical Response Unit).
* `target_type`: `user` | `group` | `channel`.
* `chat_id`: Numeric ID or `@username`.
* `role`: `DIRECTOR`, `FIELD LEAD`, `TACTICAL UNIT`, `BROADCAST`.
* `phone`: Emergency contact phone number.
* `note`: Operational notes and zone assignment.

---

## 8. UI/UX LAYOUT ARCHITECTURE & DESIGN SYSTEM TOKENS

### Layout Structure for Bot Protocols Studio Tab (Stitch Spec)

```
+-----------------------------------------------------------------------------+
| 🤖 BOT PROTOCOLS & AI INTEGRATION STUDIO                    [ACTIVE PROTOCOLS] |
| Configure Telegram Bot API, YOLOv8 Pose Engine & Gemini AI Chat Assistant  |
+-----------------------------------------------------------------------------+
| 🔑 BOT ACCESS CREDENTIALS                                                   |
| [ Bot Access Token (Password Field with Reveal Icon)                      ] |
| [ Global Chat / Channel ID (e.g. -1001234567890)                          ] |
|                                                                             |
| 🧠 AI VISION & DETECTION ENGINE                                             |
| [ Dropdown: YOLOv8 Nano (Ultra-fast Real-time Human & Fall Detection)     v ] |
|                                                                             |
| 🎛️ AUTOMATED ALERT TRIGGERS & AI ASSISTANT                                  |
| (•) Motion Detection Instant Alert Photo                [Cyan Switch  ON]   |
| (•) Human & Fall Detection Alert Photo                  [Amber Switch ON]   |
| (•) Telegram Gemini AI Pro Chat Assistant Listener      [Purple Switch ON]  |
|                                                                             |
| [ ⚡ TEST BOT CONNECTION ]                         [ 💾 SAVE BOT PROTOCOLS ]  |
+-----------------------------------------------------------------------------+
| 🛡️ AI SECURITY POLICY TERMS & GUARDRAILS                 [GUARDRAILS ACTIVE]|
| (✓) Prompt Injection Filter  (✓) Credential Shield  (✓) Admin Role Access   |
+-----------------------------------------------------------------------------+
| 👥 TELEGRAM ALERT RECIPIENTS & PROFILES                                    |
| [ 🔍 Search Recipient Name, Chat ID, Role...                              ] |
|                                                                             |
| +-------------------------------------------------------------------------+ |
| | (Avatar) Maj. Arnold Miller  [DIRECTOR]                                | |
| | Chat ID: @arnold_miller_dir  • Director of Security Operations          | |
| | Actions: [👤 Profile] [⚡ Send Test] [🗑️ Delete]                        | |
| +-------------------------------------------------------------------------+ |
| | (Avatar) Tactical Response Unit  [TACTICAL UNIT]                       | |
| | Chat ID: -100889210492  • Perimeter Breach Fast Response Team           | |
| | Actions: [👤 Profile] [⚡ Send Test] [🗑️ Delete]                        | |
| +-------------------------------------------------------------------------+ |
+-----------------------------------------------------------------------------+
```

### Design Color Tokens (Dark Mode / Glassmorphic)
* **Background Surface**: `#1E1F22` (`SURFACE_CONTAINER_HIGH`)
* **Card Container Background**: `#2B2D31` (`SURFACE_CONTAINER`)
* **Primary Accent (Cyan)**: `#00E5FF` (`CYAN_400`)
* **Warning Accent (Amber)**: `#FFC107` (`AMBER_400`)
* **AI/Assistant Accent (Purple)**: `#AB47BC` (`PURPLE_400`)
* **Success Indicator**: `#4CAF50` (`GREEN_400`)
* **Error/Alert Indicator**: `#F44336` (`RED_400`)
* **Typography**: Primary - `Inter`, Myanmar - `Pyidaungsu`

---
*Generated for S-Eye Platform UI/UX Layout Architecture Specification.*
