COMBO_ENABLE           = yes
MOUSEKEY_ENABLE        = no     # chuột dùng engine riêng (mouse_engine.c), không dùng mousekey của QMK
POINTING_DEVICE_ENABLE = yes    # để gửi chuyển động/cuộn của engine
POINTING_DEVICE_DRIVER = custom # không có cảm biến thật
WPM_ENABLE             = yes    # bật để hiện WPM trên OLED + Bongo cat slave
SRC                   += bongocat.c mouse_engine.c
