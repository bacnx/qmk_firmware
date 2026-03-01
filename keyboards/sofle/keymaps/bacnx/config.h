// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

// ---------- Split handedness: trái/phải theo chân D4, không phụ thuộc bên cắm USB ----------
#define SPLIT_HAND_PIN D4
#define SPLIT_HAND_PIN_LOW_IS_LEFT

// ---------- Split: đồng bộ WPM sang nửa slave (để Bongo cat phản ứng theo gõ) ----------
#define SPLIT_WPM_ENABLE
// Đồng bộ trạng thái bật/tắt OLED và activity giữa 2 nửa → timeout tắt OLED giống nhau
#define SPLIT_OLED_ENABLE
#define SPLIT_ACTIVITY_ENABLE
#define OLED_TIMEOUT 5 * 60000 // ms: tắt OLED sau 5m không hoạt động (dùng chung cả 2 nửa)

// ---------- Tri-layer (giữ LOWER + RAISE → ADJUST) ----------
#define TRI_LAYER_LOWER_LAYER 3  // _LOWER
#define TRI_LAYER_UPPER_LAYER 4  // _RAISE
#define TRI_LAYER_ADJUST_LAYER 5 // _ADJUST

// ---------- Home Row Mods — tap/hold thoải mái hơn ----------
#define TAPPING_TERM 200 // ms: tap nhanh = chữ, giữ lâu = mod
#define PERMISSIVE_HOLD  // mod-tap: nếu phím khác nhấn trước khi thả → coi là hold (mod)

// ---------- Combo (J+K → Esc) — thời gian nhấn 2 phím để kích combo ----------
#define COMBO_TERM 50 // ms: cả J và K phải down trong 50ms (có thể tăng 80–100 nếu khó kích)

// ---------- Encoder phải: scroll chuột — điều chỉnh tốc độ ----------
// Mỗi bước encoder = ENCODER_SCROLL_STEPS lần gửi scroll; mỗi lần = MOUSEKEY_WHEEL_DELTA đơn vị.
// Tăng ENCODER_SCROLL_STEPS (2, 3, 4…) hoặc MOUSEKEY_WHEEL_DELTA (2, 3…) = scroll nhanh hơn.
#define ENCODER_SCROLL_STEPS 2 // số “bước” scroll mỗi lần xoay 1 nấc encoder (1 = chậm, 3–4 = nhanh)
#define MOUSEKEY_WHEEL_DELTA 1 // đơn vị scroll mỗi bước (1–4, max 127); tăng = scroll dày hơn mỗi nấc
#define MOUSEKEY_WHEEL_DELAY 0 // 0 = phản hồi ngay, không trễ
