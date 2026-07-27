# src/core/state.py

from models.app_route_model import AppRouteModel
from config.localization import LocalizationManager

# A (Global State Model)
app_state = AppRouteModel()

def loc(key: str) -> str:
    """လက်ရှိ Model ထဲက ဘာသာစကားအတိုင်း စာသားကို တိုက်ရိုက်ဆွဲထုတ်ပေးရန် Helper"""
    return LocalizationManager.get_string(app_state.language, key)