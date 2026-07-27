# src/config/localization.py

import json
import os
from config import logger # သင့်ရဲ့ logger ကို import လုပ်ပါ

class LocalizationManager:
    _translations = {}
    
    @classmethod
    def _get_lang_folder_path(cls):
        """
        ဒီဖိုင်ရှိတဲ့နေရာ (src/config/) ကနေတစ်ဆင့် 
        src/assets/lang/ လမ်းကြောင်းကို အသေ (Absolute Path) ရှာပေးမည့် helper
        """
        current_dir = os.path.dirname(os.path.abspath(__file__)) # src/config
        src_dir = os.path.dirname(current_dir) # src
        return os.path.join(src_dir, "assets", "lang")

    @classmethod
    def load_translations(cls, lang_code: str):
        # Cache ထဲမှာ ရှိပြီးသားဆိုရင် တိုက်ရိုက်ပြန်ပေးပါ
        if lang_code in cls._translations:
            return cls._translations[lang_code]
        
        # လမ်းကြောင်းကို စနစ်တကျ တည်ဆောက်ခြင်း
        lang_folder = cls._get_lang_folder_path()
        file_path = os.path.join(lang_folder, f"{lang_code}.json")
        
        logger.info(f"Attempting to load translation file: {file_path}")
        
        # ဖိုင်တကယ်ရှိမရှိ စစ်ဆေးခြင်း
        if not os.path.exists(file_path):
            logger.error(f"Localization file NOT found at: {file_path}")
            cls._translations[lang_code] = {}
            return {}
        
        try:
            with open(file_path, "r", encoding="utf-8") as f:
                cls._translations[lang_code] = json.load(f)
                logger.info(f"Successfully loaded '{lang_code}' translation.")
                return cls._translations[lang_code]
        except Exception as e:
            logger.error(f"Error parsing JSON translation for {lang_code}: {e}")
            cls._translations[lang_code] = {}
            return {}

    @classmethod
    def get_string(cls, lang_code: str, key: str) -> str:
        translations = cls.load_translations(lang_code)
        # ပြန်လာတဲ့ စာသားထဲမှာ key မရှိရင် key အတိုင်းပဲ ပြန်ပြပါမယ်
        return translations.get(key, key)