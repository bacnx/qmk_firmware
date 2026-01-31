// SPDX-License-Identifier: GPL-2.0-or-later
// Sofle/rev1 keymap "bacnx" — minimal, coding/Hyprland/tmux/Neovim
// Base layer: Home Row Mods (tap = chữ, giữ = mod)

#include QMK_KEYBOARD_H

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
        _______, KC_EQL,  KC_MINS, KC_PLUS, KC_LCBR, KC_RCBR, _______, _______, KC_LBRC, KC_RBRC, KC_SCLN, KC_COLN, KC_BSLS, _______,
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
