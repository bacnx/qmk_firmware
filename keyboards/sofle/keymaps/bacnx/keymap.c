// SPDX-License-Identifier: GPL-2.0-or-later
// Sofle/rev1 keymap "bacnx" — minimal, coding/Hyprland/tmux/Neovim
// Base layer: Home Row Mods (tap = chữ, giữ = mod)

#include QMK_KEYBOARD_H
#ifdef OLED_ENABLE
#    include "bongocat.h"
#endif

// ============ Layers ============
enum layers {
    _COLEMAK_DH,  // 0: Colemak-DH + Home Row Mods (mặc định)
    _QWERTY,      // 1: QWERTY + Home Row Mods
    _LAYER_SELECT,// 2: Giữ nút layer (trái trên) + 1 = Colemak DH, + 2 = QWERTY
    _LOWER,       // 3: Số + ký hiệu (coding)
    _RAISE,       // 4: Nav + tmux/neovim
    _ADJUST,      // 5: Tri-layer (LOWER+RAISE) — volume, reset
    _MOUSE        // 6: Điều khiển chuột (toggle Space+Enter)
};

// ============ Base layers: Colemak-DH / QWERTY + Home Row Mods ============
// Trái:  A=Gui  R/S=Alt  S/D=Ctrl  T/F=Shift  — Colemak: A R S T D / Qwerty: A S D F G
// Phải:  H N E I O / J K L ; — N/J=Shift  E/K=Ctrl  I/L=Alt  O/;=Gui
// Nút trái trên: giữ = layer select, 1 = Colemak DH, 2 = QWERTY.

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
    /*
     * COLEMAK-DH (layer 0, mặc định)
     * ,-----------------------------------------.     ,-----------------------------------------.
     * |LaySel|  1   |  2   |  3   |  4   |  5   |     |  6   |  7   |  8   |  9   |  0   |  `   |
     * |------+------+------+------+------+------|     |------+------+------+------+------+------|
     * | Esc  |  Q   |  W   |  F   |  P   |  G   |     |  J   |  L   |  U   |  Y   |  ;   | Bspc |
     * |------+------+------+------+------+------|     |------+------+------+------+------+------|
     * | Tab  |A/Gui |R/Alt |S/Ctl |T/Sft |  D   |     |  H   |N/Sft |E/Ctl |I/Alt |O/Gui |  '   |
     * |------+------+------+------+------+------|     |------+------+------+------+------+------|
     * | Shift|  Z   |  X   |  C   |  V   |  B   |     |  K   |  M   |  ,   |  .   |  /   | Shift|
     * |------+------+------+------+------+------|     |------+------+------+------+------+------|
     *       | Gui  | Alt  | Ctl  |LOWER |Space |     | Enter| RAISE| Ctl  | Alt  | Gui  |
     *       `-----------------------------------'     `-----------------------------------'
     */
    [_COLEMAK_DH] = LAYOUT(
        LT(_LAYER_SELECT, KC_GRV), KC_1,    KC_2,    KC_3,    KC_4,    KC_5,         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,
        KC_ESC,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,         KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
        KC_TAB,  LGUI_T(KC_A), LALT_T(KC_R), LCTL_T(KC_S), LSFT_T(KC_T), KC_D,   KC_H,    RSFT_T(KC_N), RCTL_T(KC_E), RALT_T(KC_I), RGUI_T(KC_O), KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_NO,  KC_NO,  KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                 KC_LGUI, KC_LALT, KC_LCTL, TL_LOWR, KC_SPC,        KC_ENT,  TL_UPPR, KC_RCTL, KC_RALT, KC_RGUI
    ),

    /*
     * QWERTY (layer 1)
     * ,-----------------------------------------.     ,-----------------------------------------.
     * |LaySel|  1   |  2   |  3   |  4   |  5   |     |  6   |  7   |  8   |  9   |  0   |  `   |
     * |------+------+------+------+------+------|     |------+------+------+------+------+------|
     * | Esc  |  Q   |  W   |  E   |  R   |  T   |     |  Y   |  U   |  I   |  O   |  P   | Bspc |
     * |------+------+------+------+------+------|     |------+------+------+------+------+------|
     * | Tab  |A/Gui |S/Alt |D/Ctl |F/Sft |  G   |     |  H   |J/Sft |K/Ctl |L/Alt |;/Gui |  '   |
     * |------+------+------+------+------+------|     |------+------+------+------+------+------|
     * | Shift|  Z   |  X   |  C   |  V   |  B   |     |  N   |  M   |  ,   |  .   |  /   | Shift|
     * |------+------+------+------+------+------|     |------+------+------+------+------+------|
     *       | Gui  | Alt  | Ctl  |LOWER |Space |     | Enter| RAISE| Ctl  | Alt  | Gui  |
     *       `-----------------------------------'     `-----------------------------------'
     */
    [_QWERTY] = LAYOUT(
        LT(_LAYER_SELECT, KC_GRV), KC_1,    KC_2,    KC_3,    KC_4,    KC_5,         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_TAB,  LGUI_T(KC_A), LALT_T(KC_S), LCTL_T(KC_D), LSFT_T(KC_F), KC_G,   KC_H,    RSFT_T(KC_J), RCTL_T(KC_K), RALT_T(KC_L), RGUI_T(KC_SCLN), KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_NO,  KC_NO,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                 KC_LGUI, KC_LALT, KC_LCTL, TL_LOWR, KC_SPC,        KC_ENT,  TL_UPPR, KC_RCTL, KC_RALT, KC_RGUI
    ),

    /*
     * LAYER_SELECT — giữ nút trái trên + 1 = Colemak DH, + 2 = QWERTY (chỉ 2 layer cơ bản)
     */
    [_LAYER_SELECT] = LAYOUT(
        _______, TO(_COLEMAK_DH), TO(_QWERTY), _______, _______, _______,   _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                 _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______
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
     * RAISE — Mũi tên, Home/End, PgUp/Dn
     */
    [_RAISE] = LAYOUT(
        _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______,
        _______, KC_ESC,  _______, _______, _______, _______,       KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_BSPC, _______,
        _______, KC_TAB,  _______, _______, _______, _______,       KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_QUOT, _______,
        _______, _______, KC_CAPS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
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

    /*
     * MOUSE — toggle bằng Space+Enter. h/j/k/l = di chuyển, U/N = scroll dọc, Y/M = scroll ngang.
     * F = click trái (MS_BTN1), G = click phải (MS_BTN2). S/D = ACL2/ACL1 (move/scroll dày).
     * Giữ Space+Enter ở thumb để toggle tắt.
     */
    [_MOUSE] = LAYOUT(
        _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,       MS_WHLL, MS_WHLU, _______, _______, _______, _______,
        _______, _______, MS_ACL2, MS_ACL1, MS_BTN1, MS_BTN2,       MS_LEFT, MS_DOWN, MS_UP,   MS_RGHT, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, MS_WHLD, MS_WHLR, _______, _______, _______, _______,
                 _______, _______, _______, _______, KC_SPC,        KC_ENT,  _______, _______, _______, _______
    ),
    // clang-format on
};

// J+K (QWERTY) hoặc N+E (Colemak DH) — cùng vị trí phím → Esc
const uint16_t PROGMEM jk_combo[]          = {RSFT_T(KC_J), RCTL_T(KC_K), COMBO_END};
const uint16_t PROGMEM ne_combo[]          = {RSFT_T(KC_N), RCTL_T(KC_E), COMBO_END};
const uint16_t PROGMEM space_enter_combo[] = {KC_SPC, KC_ENT, COMBO_END};

combo_t key_combos[] = {
    COMBO(jk_combo, KC_ESC),
    COMBO(ne_combo, KC_ESC),
    COMBO(space_enter_combo, TG(_MOUSE)),
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
#    if defined(SPLIT_ACTIVITY_ENABLE) && (OLED_TIMEOUT > 0)
        // Đồng bộ timeout với nửa master: reset oled_timeout khi còn activity (từ cả 2 nửa)
        if (last_input_activity_elapsed() < OLED_TIMEOUT) {
            oled_on();
        }
#    endif
        render_bongocat_slave();
        return false; // slave: Bongo cat, không dùng logo mặc định
    }
    // Master: layer + mod đang giữ + lock keys (+ WPM nếu bật)
    oled_set_cursor(0, 0);
    oled_write_P(PSTR("\n"), false);

    // Dòng 1: Layer (tối đa 5 ký tự, viết hoa hết; đủ 5 thì không \n trong chuỗi)
    switch (get_highest_layer(layer_state)) {
        case _COLEMAK_DH:
            oled_write_ln_P(PSTR("COLMK"), false);
            break;
        case _QWERTY:
            oled_write_ln_P(PSTR("QWRTY"), false);
            break;
        case _LAYER_SELECT:
            oled_write_ln_P(PSTR("SELEC"), false);
            break;
        case _LOWER:
            oled_write_ln_P(PSTR("LOWER"), false);
            break;
        case _RAISE:
            oled_write_ln_P(PSTR("RAISE"), false);
            break;
        case _ADJUST:
            oled_write_ln_P(PSTR("ADJST"), false);
            break;
        case _MOUSE:
            oled_write_ln_P(PSTR("MOUSE"), false);
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

    // Dòng 3: chỉ caps/CAPS
    led_t led = host_keyboard_led_state();
    oled_write_ln_P(led.caps_lock ? PSTR("CAPS") : PSTR("Caps"), false);
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
