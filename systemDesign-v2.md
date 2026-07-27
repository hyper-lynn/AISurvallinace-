# Project: AI-Driven Infrastructure & Database Management System
**Version:** 2.0.0 (Updated with Python Integration & Mermaid Flowchart)
**Author:** Lead System Architect

## 1. System Flowchart (Mermaid)

အောက်ပါ Flowchart သည် User မှ စာရိုက်လိုက်သည့်အချိန်မှစ၍ Middleware (Python) မှ တစ်ဆင့် Gemini AI သို့ရောက်ရှိပြီး Database ကို မည်သို့လုံခြုံစွာ ခေါ်ယူသွားသည်ကို ပြသထားပါသည်။

```mermaid
sequenceDiagram
    autonumber
    actor User
    participant UI as Client (UI/CLI)
    participant MW as Middleware (Python/FastAPI)
    participant LLM as Gemini API (AI Studio)
    participant DB as Database (PostgreSQL)

    User->>UI: "Database ထဲက user record ၄ ခု ရှာပေးပါ"
    UI->>MW: API Request ပို့မည်
    MW->>LLM: User Prompt + Allowed Tools (e.g., get_users) ကို ပို့မည်
    LLM-->>MW: JSON Return (Function 'get_users', limit=4)
    Note over MW: Middleware မှ JSON ကို စစ်ဆေးမည် (Validation)
    MW->>DB: Secure SQL (Prepared Statement) ဖြင့် Query လုပ်မည်
    DB-->>MW: Record (၄) ခု ပြန်ပေးမည်
    MW->>LLM: ရရှိလာသော Record များကို Text အဖြစ်ပြောင်းရန် ပြန်ပို့မည် (Optional)
    LLM-->>MW: သပ်ရပ်သော ရှင်းလင်းချက်စာသား ပြန်ရောက်မည်
    MW-->>UI: Final JSON Response (Text + Data)
    UI-->>User: မြင်သာသော ပုံစံဖြင့် ပြသမည်
```

## 3. မှတ်ချက်
- **Security:** AI ကို Database Access Password/Credentials ပေးစရာမလိုပါ။ AI သည် ဘယ် Function ကို ဘာ Parameter ဖြင့် ခေါ်ရမည်ကိုသာ Middleware ထံ ပြန်ပြောပေးခြင်းဖြစ်သည်။ အမှန်တကယ် Database ချိတ်ဆက်ခြင်းကို Middleware (Python) မှ တာဝန်ယူပါသည်။
- **Extensibility:** နောက်ပိုင်း `restart_server()` သို့မဟုတ် `delete_logs()` စသည့် Function များကို လိုအပ်ပါက Python တွင်ရေးပြီး `tools=[]` အတွင်း ထည့်သွင်းပေးရုံသာ ဖြစ်ပါသည်။
