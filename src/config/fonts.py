# src/config/fonts.py

class AppFonts:
    # Primary font naming
    BOLD = "Inter-Bold"
    REGULAR = "Inter-Regular"
    
    # Myanmar Unicode Font naming
    MYANMAR = "Padauk-Regular"
    MYANMAR_BOLD = "Padauk-Bold"
    
    # Global Font Family for Theme (Padauk supports both English & Myanmar Unicode shaping)
    DEFAULT_FAMILY = "Padauk-Regular"
    
    # Local Font Mapping for instant asset loading (No remote network delay)
    FONTS_MAPPING = {
        "Padauk-Regular": "/fonts/Padauk-Regular.ttf",
        "Padauk-Bold": "/fonts/Padauk-Regular.ttf",
    }
