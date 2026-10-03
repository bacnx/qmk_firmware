// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

// ---------- Split handedness: trái/phải theo chân D4, không phụ thuộc bên cắm USB ----------
#define SPLIT_HAND_PIN D4
#define SPLIT_HAND_PIN_LOW_IS_LEFT

// Enable watchdog to prevent split keyboard from losing USB detection in BIOS
#define SPLIT_WATCHDOG_ENABLE

// ---------- Split: đồng bộ WPM sang nửa slave (để Bongo cat phản ứng theo gõ) ----------
#define SPLIT_WPM_ENABLE
// Đồng bộ trạng thái bật/tắt OLED và activity giữa 2 nửa → timeout tắt OLED giống nhau
#define SPLIT_OLED_ENABLE
#define SPLIT_ACTIVITY_ENABLE
#define OLED_TIMEOUT 5 * 60000 // ms: tắt OLED sau 5m không hoạt động (dùng chung cả 2 nửa)

// ---------- Bootloader ----------
// Bootmagic: giữ phím góc ngoài-trên của nửa đang cắm USB rồi cắm vào → bootloader (và xoá EEPROM).
// Nửa trái: [0,0] (mặc định). Nửa phải: [5,0].
#define BOOTMAGIC_ROW_RIGHT 5
#define BOOTMAGIC_COLUMN_RIGHT 0
// Phím BOOT trong layer SYS phải giữ ngần này (ms) mới vào bootloader.
#define BOOT_HOLD_MS 1000

// ---------- NKRO: bật mặc định (game cần nhiều phím cùng lúc) ----------
#define NKRO_DEFAULT_ON true

// ---------- Layer-tap ở thumb trong (Bspc/LOWER, Tab/RAISE) — giống &lt trong zmk-config ----------
#define TAPPING_TERM   200 // ms: giữ lâu hơn → layer (ZMK tapping-term-ms)
#define QUICK_TAP_TERM 175 // tap rồi giữ lại cùng phím trong 175ms → lặp Bspc/Tab (ZMK quick-tap-ms)
#define PERMISSIVE_HOLD    // phím khác nhấn-và-thả trong lúc giữ → layer (ZMK balanced)

// ---------- Combo (Space + Enter → bật/tắt MOUSE) ----------
#define COMBO_TERM 60           // ms: 2 phím phải xuống trong 60ms (ZMK timeout-ms)
#define COMBO_SHOULD_TRIGGER    // chỉ chạy combo ở Colemak/MOUSE (xem combo_should_trigger)
#define COMBO_PRIOR_IDLE_MS 150 // ở Colemak: vừa gõ phím < 150ms thì không kích combo (ZMK require-prior-idle-ms)

// ---------- Chuột (mouse_engine.c) — cùng đơn vị với zmk-config/Sweep.keymap ----------
// Cuộn mượt (như CONFIG_ZMK_POINTING_SMOOTH_SCROLLING). Cần host hỗ trợ HID Resolution Multiplier (Linux/Windows);
// host không hỗ trợ (macOS, KVM…) sẽ cuộn nhanh gấp 120 lần → comment dòng dưới để cuộn từng nấc.
#define POINTING_DEVICE_HIRES_SCROLL_ENABLE
#define MOUSE_MOVE_VAL 1200                 // ZMK_POINTING_DEFAULT_MOVE_VAL
#define MOUSE_MOVE_X_NUM 2                  // MMV_X_NORMAL 2 1 → ngang 2400/s
#define MOUSE_MOVE_X_DEN 1
#define MOUSE_MOVE_Y_NUM 3 // MMV_Y_NORMAL 3 2 → dọc 1800/s
#define MOUSE_MOVE_Y_DEN 2
#define MOUSE_MOVE_TIME_TO_MAX 500 // ms để đạt tốc độ max (&mmv time-to-max-speed-ms)
#define MOUSE_SCROLL_VAL 60        // ZMK_POINTING_DEFAULT_SCRL_VAL: 60 = 3.75 nấc/giây, tốc độ đều

// ---------- Encoder phải: cuộn ----------
#define ENCODER_SCROLL_STEPS 2 // số nấc cuộn mỗi lần xoay 1 nấc encoder (1 = chậm, 3–4 = nhanh)
