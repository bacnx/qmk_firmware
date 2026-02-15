// SPDX-License-Identifier: GPL-2.0-or-later
// Sofle/rev1 keymap "bacnx" — minimal, coding/Hyprland/tmux/Neovim
// Base layer: Home Row Mods (tap = chữ, giữ = mod)

#include QMK_KEYBOARD_H
#ifdef OLED_ENABLE
#    include "bongocat.h"
#endif

// ============ Layers ============
enum layers {
    _BASE,  // 0: QWERTY + Home Row Mods
    _LOWER, // 1: Số + ký hiệu (coding)
    _RAISE, // 2: Nav + tmux/neovim
    _ADJUST // 3: Tri-layer (LOWER+RAISE) — volume, reset
};

// ============ Base: QWERTY + Home Row Mods ============
// Trái:  A=Super(GUI)  S=Alt  D=Ctrl  F=Shift  — Hyprland/tmux/neovim
// Phải: J=Shift  K=Ctrl  L=Alt  ;=Super(GUI)
// Tap = gõ chữ, Hold = giữ mod.

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
    /*
     * BASE (Home Row Mods)
     * ,-----------------------------------------.     ,-----------------------------------------.
     * |  `   |  1   |  2   |  3   |  4   |  5   |     |  6   |  7   |  8   |  9   |  0   |  `   |
     * |------+------+------+------+------+------|     |------+------+------+------+------+------|
     * | Esc  |  Q   |  W   |  E   |  R   |  T   |     |  Y   |  U   |  I   |  O   |  P   | Bspc |
     * |------+------+------+------+------+------|     |------+------+------+------+------+------|
     * | Tab  | A/Gui| S/Alt| D/Ctl| F/Sft|  G   |     |  H   | J/Sft| K/Ctl| L/Alt| ;/Gui|  '   |
     * |------+------+------+------+------+------|     |------+------+------+------+------+------|
     * | Shift|  Z   |  X   |  C   |  V   |  B   |     |  N   |  M   |  ,   |  .   |  /   | Shift|
     * |------+------+------+------+------+------|     |------+------+------+------+------+------|
     *       | Gui  | Alt  | Ctl  |LOWER |Space |     | Enter| RAISE| Ctl  | Alt  | Gui  |
     *       `-----------------------------------'     `-----------------------------------'
     */
    [_BASE] = LAYOUT(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_TAB,  LGUI_T(KC_A), LALT_T(KC_S), LCTL_T(KC_D), LSFT_T(KC_F), KC_G,   KC_H,    RSFT_T(KC_J), RCTL_T(KC_K), RALT_T(KC_L), RGUI_T(KC_SCLN), KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_NO,  KC_NO,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                 KC_LGUI, KC_LALT, KC_LCTL, TL_LOWR, KC_SPC,        KC_ENT,  TL_UPPR, KC_RCTL, KC_RALT, KC_RGUI
    ),

    /*
     * LOWER — số, ký hiệu, F-keys (coding)
     */
    [_LOWER] = LAYOUT(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,         KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,          KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_F12,
        _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,       KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE,
        _______, KC_EQL,  KC_MINS, KC_PLUS, KC_LCBR, KC_RCBR, _______, _______, KC_LBRC, KC_RBRC, KC_GRV,  KC_COLN, KC_BSLS, _______,
                 _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______
    ),

    /*
     * RAISE — nav, tmux/neovim
     * Mũi tên, Home/End, PgUp/Dn, Copy/Paste, word nav
     */
    [_RAISE] = LAYOUT(
        _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______,
        _______, KC_INS,  KC_PSCR, KC_APP,  _______, _______,       KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_DEL,  KC_BSPC,
        _______, _______, _______, _______, _______, _______,       KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
        _______, C(KC_Z), C(KC_X), C(KC_C), C(KC_V), _______, _______, _______, _______, _______, _______, _______, _______, _______,
                 _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______
    ),

    /*
     * ADJUST — Tri-layer (giữ LOWER + RAISE): volume, bootloader
     */
    [_ADJUST] = LAYOUT(
        _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______,
        QK_BOOT, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,       _______, KC_VOLD, KC_MUTE, KC_VOLU, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______,
                 _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______
    ),
    // clang-format on
};

const uint16_t PROGMEM jk_combo[] = {RSFT_T(KC_J), RCTL_T(KC_K), COMBO_END};

combo_t key_combos[] = {
    COMBO(jk_combo, KC_ESC),
};

// ---------- OLED (nếu bật OLED_ENABLE) ----------
// Sofle đã bật OLED trong info.json. Code mặc định ở sofle.c:
// - Nửa master: layer + caps (Qwrt/Clmk/Mod, Base/Lower/Raise/Adjust).
// - Nửa slave: logo QMK.
// Để tùy chỉnh: implement oled_task_user(), return false = không chạy code mặc định.
#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180; // nửa phải (slave) xoay 180° cho dễ nhìn
    }
    return rotation; // nửa trái dùng rotation từ oled_init_kb (270°)
}

bool oled_task_user(void) {
    if (!is_keyboard_master()) {
        render_bongocat_slave();
        return false; // slave: Bongo cat, không dùng logo mặc định
    }
    // Master: layer + mod đang giữ + lock keys (+ WPM nếu bật)
    oled_set_cursor(0, 0);
    oled_write_P(PSTR("\n"), false);

    // Dòng 1: Layer (BASE ngắn hơn nên thêm 1 xuống dòng cho đồng bộ với LOWER/RAISE/ADJUST)
    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_ln_P(PSTR("BASE\n"), false);
            break;
        case _LOWER:
            oled_write_ln_P(PSTR("LOWER"), false);
            break;
        case _RAISE:
            oled_write_ln_P(PSTR("RAISE"), false);
            break;
        case _ADJUST:
            oled_write_ln_P(PSTR("ADJ\n"), false);
            break;
        default:
            oled_write_ln_P(PSTR("?"), false);
    }

    // Dòng 2: Mod đang giữ (S/C/A/G) — hữu ích cho Home Row Mods
    uint8_t mods = get_mods();
    oled_write_P(PSTR("Mod \n"), false);
    oled_write_P((mods & MOD_MASK_SHIFT) ? PSTR("S") : PSTR("-"), false);
    oled_write_P((mods & MOD_MASK_CTRL) ? PSTR("C") : PSTR("-"), false);
    oled_write_P((mods & MOD_MASK_ALT) ? PSTR("A") : PSTR("-"), false);
    oled_write_ln_P((mods & MOD_MASK_GUI) ? PSTR("G") : PSTR("-"), false);
    oled_write_P(PSTR("\n"), false);

    // Dòng 3: Lock keys (C/N/S), chữ đảo khi bật
    led_t led = host_keyboard_led_state();
    oled_write_P(PSTR("Lock\n"), false);
    oled_write_P(PSTR("C "), led.caps_lock);
    oled_write_P(PSTR("N "), led.num_lock);
    oled_write_ln_P(PSTR("S"), led.scroll_lock);
    oled_write_P(PSTR("\n"), false);

#    ifdef WPM_ENABLE
    // Dòng 4: WPM (cần thêm WPM_ENABLE = yes trong rules.mk)
    oled_write_P(PSTR("WPM\n"), false);
    oled_write(get_u8_str(get_current_wpm(), '0'), false);
    oled_write_ln_P(PSTR("  "), false);
#    endif

    return false;
}
#endif

// ---------- Encoder: trái = volume (default), phải = scroll chuột ----------
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 1) {
        // Encoder phải: scroll chuột (tốc độ chỉnh bằng ENCODER_SCROLL_STEPS và MOUSEKEY_WHEEL_DELTA trong config.h)
#ifdef MOUSEKEY_ENABLE
        for (uint8_t i = 0; i < ENCODER_SCROLL_STEPS; i++) {
            if (clockwise) {
                tap_code(MS_WHLD); // scroll xuống
            } else {
                tap_code(MS_WHLU); // scroll lên
            }
        }
        return false; // đã xử lý, không chạy hành vi mặc định (PgUp/PgDn)
#else
        (void)clockwise;
        return true;
#endif
    }
    return true; // encoder trái: để default (volume)
}
