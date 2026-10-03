// SPDX-License-Identifier: GPL-2.0-or-later
// Sofle/rev1 keymap "bacnx" — coding/Hyprland/tmux/Neovim + các mode game
// Base: Colemak-DH, KHÔNG home row mods (mod nằm ở cụm ngón cái), kiểu Ferris Sweep.

#include QMK_KEYBOARD_H
#include "mouse_engine.h"
#ifdef OLED_ENABLE
#    include "bongocat.h"
#endif

// ============ Layers ============
// Mode (đổi bằng SYS + 1/2/3/4): COLEMAK_DH, GAME, LOL, SF6.
// Layer tạm (nằm trên mode): LOWER, RAISE, ADJUST, MOUSE, SYS.
enum layers {
    _COLEMAK_DH, // Colemak-DH, mặc định khi cắm
    _GAME,       // QWERTY thuần cho game chung chung — không combo, không hold-tap
    _LOL,        // Liên Minh Huyền Thoại — chỉ mảnh trái, mảnh phải tắt
    _SF6,        // Street Fighter 6 — kiểu hitbox, phím mặc định Classic
    _LOWER,      // Số + ký hiệu (giữ thumb trái trong)
    _RAISE,      // Nav + mod thường (giữ thumb phải trong)
    _ADJUST,     // LOWER + RAISE: volume, media
    _MOUSE,      // Chuột kiểu zmk-config (combo Space+Enter)
    _SYS         // Giữ phím trái-trên: đổi mode, bật chuột, bootloader
};

enum custom_keycodes {
    SYS_BOOT = SAFE_RANGE, // giữ BOOT_HOLD_MS mới vào bootloader
    SF6_UP,                // "Lên" (W) cho SF6, đặt ở 2 chỗ, không nhả nhầm khi giữ cả hai
    MS_TOGL,               // bật/tắt MOUSE ngay khi nhấn (combo Space+Enter, SYS+5)
    MS_EXIT,               // tắt MOUSE ngay khi nhấn (thumb trong ở MOUSE); nhấn 2 thumb vẫn chỉ tắt
    // Chuột — thứ tự phải khớp me_input_t trong mouse_engine.h
    MV_LEFT,
    MV_RGHT,
    MV_UP,
    MV_DOWN,
    WH_LEFT,
    WH_RGHT,
    WH_UP,
    WH_DOWN,
    SP_SLOW, // A: chậm cả 2 trục
    SP_XFST, // R: nhanh trục ngang
    SP_YFST, // S: nhanh trục dọc
    SP_XSLW, // X: chậm trục ngang
    SP_YSLW, // C: chậm trục dọc
};
_Static_assert(SP_YSLW - MV_LEFT == ME_INPUT_COUNT - 1, "mouse keycodes must match me_input_t");

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
    /*
     * COLEMAK-DH (layer 0)
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * | SYS  |  1   |  2   |  3   |  4   |  5   |                    |  6   |  7   |  8   |  9   |  0   |  `   |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | Esc  |  Q   |  W   |  F   |  P   |  B   |                    |  J   |  L   |  U   |  Y   |  ;   | Bspc |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | Tab  |  A   |  R   |  S   |  T   |  G   |-------.    ,-------|  M   |  N   |  E   |  I   |  O   |  '   |
     * |------+------+------+------+------+------| Mute  |    | Play  |------+------+------+------+------+------|
     * | Shift|  Z   |  X   |  C   |  D   |  V   |-------|    |-------|  K   |  H   |  ,   |  .   |  /   | Shift|
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *            | Alt  | Gui  | Ctrl |LOW/⌫ | /Space  /       \Enter \  |RAI/⇥ | Ctrl | Gui  | Alt  |
     *            `----------------------------------'           '------''---------------------------'
     * Thumb trong: tap = Bspc/Tab, giữ = LOWER/RAISE (layer-tap, không phải mod-tap).
     * Space + Enter (cùng lúc) = bật/tắt MOUSE.
     */
    [_COLEMAK_DH] = LAYOUT(
        MO(_SYS), KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,
        KC_ESC,   KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                       KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
        KC_TAB,   KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                       KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
        KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_MUTE,  KC_MPLY, KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                  KC_LALT, KC_LGUI, KC_LCTL, LT(_LOWER, KC_BSPC), KC_SPC,     KC_ENT,  LT(_RAISE, KC_TAB), KC_RCTL, KC_RGUI, KC_RALT
    ),

    /*
     * GAME (layer 1) — QWERTY thuần như bàn phím thường: không combo, không hold-tap.
     * Không có Super (tránh lỡ chạm Super/Start menu khi đang chơi).
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * | SYS  |  1   |  2   |  3   |  4   |  5   |                    |  6   |  7   |  8   |  9   |  0   |  `   |
     * | Esc  |  Q   |  W   |  E   |  R   |  T   |                    |  Y   |  U   |  I   |  O   |  P   | Bspc |
     * | Tab  |  A   |  S   |  D   |  F   |  G   |-------.    ,-------|  H   |  J   |  K   |  L   |  ;   |  '   |
     * | Shift|  Z   |  X   |  C   |  V   |  B   | Mute  |    | Play  |  N   |  M   |  ,   |  .   |  /   | Shift|
     *            |  --  | Alt  | Ctrl |Space | Space |          | Enter | Bspc | Ctrl | Alt  |  --  |
     */
    [_GAME] = LAYOUT(
        MO(_SYS), KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,
        KC_ESC,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_TAB,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                       KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_MUTE,  KC_MPLY, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                  XXXXXXX, KC_LALT, KC_LCTL, KC_SPC,  KC_SPC,                     KC_ENT,  KC_BSPC, KC_RCTL, KC_RALT, XXXXXXX
    ),

    /*
     * LOL (layer 2) — LMHT. Hàng 1: SYS -- Ctrl+6 Alt+Tab Play/Pause Next.
     * Hàng 2: B 1–5. Hàng 3: Tab A QWER. Hàng 4: Ctrl Z X C D F. Thumb: G P T V Space. Phải tắt.
     */
    [_LOL] = LAYOUT(
        MO(_SYS), XXXXXXX, LCTL(KC_6), LALT(KC_TAB), KC_MPLY, KC_MNXT,           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_B,     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_TAB,   KC_A,    KC_Q,    KC_W,    KC_E,    KC_R,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_LCTL,  KC_Z,    KC_X,    KC_C,    KC_D,    KC_F,    XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                  KC_G,    KC_P,    KC_T,    KC_V,    KC_SPC,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),

    /*
     * SF6 (layer 3) — Street Fighter 6, kiểu hitbox, gửi đúng phím mặc định Classic của game:
     *   Hướng: W↑ A← S↓ D→     Đấm: U I O = LP MP HP     Đá: J K L = LK MK HK
     * Tay trái đặt áp út/giữa/trỏ lên 3 phím home (vị trí S D F): ← ↓ →. Ngón út nghỉ.
     * "Lên" có 2 chỗ: ngón cái (kiểu hitbox) và phía trên ngón giữa (kiểu WASD).
     * Hướng chéo = bấm 2 hướng cùng lúc. Trái+Phải cùng lúc: game tự coi là đứng yên.
     * Y H P N M: phím chữ dư để gán phím tắt (Drive Parry / Drive Impact / Throw) trong game —
     * Y/H có thể đã được gán sẵn, xem Controls. Chỉ để phím chữ vì SF6 được báo không nhận ; , ' [ ].
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * | SYS  |  1   |  2   |  3   |  4   |  5   |                    |  6   |  7   |  8   |  9   |  0   |  --  |
     * | Esc  |  --  |  --  | W ↑  |  --  |  --  |                    |  Y   | U LP | I MP | O HP |  P   |  --  |
     * |  --  |  --  | A ←  | S ↓  | D →  |  --  |-------.    ,-------|  H   | J LK | K MK | L HK |  --  |  --  |
     * |  --  |  --  |  --  |  --  |  --  |  --  |  --   |    |  --   |  N   |  M   |  --  |  --  |  --  |  --  |
     *            |  --  |  --  |  --  |  --  |  W ↑  |          | Enter | Bspc |  --  |  --  |  --  |
     */
    [_SF6] = LAYOUT(
        MO(_SYS), KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    XXXXXXX,
        KC_ESC,   XXXXXXX, XXXXXXX, SF6_UP,  XXXXXXX, XXXXXXX,                    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    XXXXXXX,
        XXXXXXX,  XXXXXXX, KC_A,    KC_S,    KC_D,    XXXXXXX,                    KC_H,    KC_J,    KC_K,    KC_L,    XXXXXXX, XXXXXXX,
        XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, KC_N,    KC_M,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, SF6_UP,                     KC_ENT,  KC_BSPC, XXXXXXX, XXXXXXX, XXXXXXX
    ),

    /*
     * LOWER — Sweep Num/Sym. F1–F12 ở hàng số bonus của Sofle.
     * Hàng top alpha: ! @ # $ % ^ & * ( )
     * Hàng home    : 1 2 3 4 5 6 7 8 9 0
     * Hàng bot alpha: ` - = [ ] \ ' ; _ |
     */
    [_LOWER] = LAYOUT(
        _______,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                      KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        _______,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                    KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_F12,
        _______,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
        _______,  KC_GRV,  KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, _______,  _______, KC_BSLS, KC_QUOT, KC_SCLN, KC_UNDS, KC_PIPE, _______,
                  _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______
    ),

    /*
     * RAISE — Sweep Nav. Mũi tên ← ↓ ↑ → trên N E I O.
     * Hàng home trái = Gui/Alt/Ctrl/Shift thường (không tap-hold): giữ RAISE + Shift/Ctrl + mũi tên
     * để chọn chữ / nhảy theo từ.
     * (6 cột mỗi bên, từ cột ngoài cùng bên trái)
     * Hàng top : Esc  Ins  -     PrtSc -     -    / -    PgUp Del  -  -  -
     * Hàng home: Caps Gui  Alt   Ctrl  Shift -    / Home ←    ↓    ↑  →  -
     * Hàng bot : -    -    Ctl-Z Ctl-X Ctl-C Ctl-V / End  PgDn -    -  -  -
     */
    [_RAISE] = LAYOUT(
        _______,  _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______,
        KC_ESC,   KC_INS,  _______, KC_PSCR, _______, _______,                    _______, KC_PGUP, KC_DEL,  _______, _______, _______,
        KC_CAPS,  KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______,                    KC_HOME, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______,
        _______,  _______, C(KC_Z), C(KC_X), C(KC_C), C(KC_V), _______,  _______, KC_END,  KC_PGDN, _______, _______, _______, _______,
                  _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______
    ),

    /*
     * ADJUST — Tri-layer (giữ LOWER + RAISE): volume, media.
     */
    [_ADJUST] = LAYOUT(
        _______,  _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______,
        _______,  _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______,
        _______,  _______, _______, _______, _______, _______,                    _______, KC_VOLD, KC_MUTE, KC_VOLU, _______, _______,
        _______,  _______, _______, _______, _______, _______, _______,  _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______,
                  _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______
    ),

    /*
     * MOUSE — giống layer Mouse trong zmk-config (Sweep).
     * Bật/tắt: Space + Enter cùng lúc. Thoát: chạm 1 trong 4 thumb trong.
     * Phải home  — N/E/I/O = di chuyển ← ↓ ↑ →
     * Phải dưới  — H/,/./⁄ = cuộn ← ↓ ↑ → (cùng ngón, xuống 1 hàng)
     * Trái trên  — Q/W/F/P = Gui/Alt/Ctrl/Shift (ctrl-click, shift-click…)   B = MB4 (back)
     * Trái home  — A = chậm (2 trục)   R = nhanh ngang   S = nhanh dọc   T = click trái   G = click phải
     * Trái dưới  —                     X = chậm ngang    C = chậm dọc    D = click giữa   V = MB5 (forward)
     * Phím tốc độ giữ để dùng và nhân dồn (vd. S + X = dọc nhanh, ngang chậm). Thông số ở config.h.
     */
    [_MOUSE] = LAYOUT(
        _______,  _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______,
        _______,  KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, MS_BTN4,                    _______, _______, _______, _______, _______, _______,
        _______,  SP_SLOW, SP_XFST, SP_YFST, MS_BTN1, MS_BTN2,                    _______, MV_LEFT, MV_DOWN, MV_UP,   MV_RGHT, _______,
        _______,  _______, SP_XSLW, SP_YSLW, MS_BTN3, MS_BTN5, _______,  _______, _______, WH_LEFT, WH_DOWN, WH_UP,   WH_RGHT, _______,
                  _______, _______, _______, MS_EXIT, MS_EXIT,                    MS_EXIT, MS_EXIT, _______, _______, _______
    ),

    /*
     * SYS — giữ phím trái-trên (có ở mọi mode).
     * 1 = Colemak-DH   2 = GAME   3 = LOL   4 = SF6   5 = bật/tắt MOUSE
     * BOOT (góc phải-trên): GIỮ 1 giây mới vào bootloader (OLED hiện BOOT!). Phím khác: tắt.
     */
    [_SYS] = LAYOUT(
        _______,  TO(_COLEMAK_DH), TO(_GAME), TO(_LOL), TO(_SF6), MS_TOGL,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, SYS_BOOT,
        XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),
    // clang-format on
};

// ============ Combo ============
// Chỉ còn Space + Enter → bật/tắt MOUSE, và chỉ chạy ở COLEMAK_DH / MOUSE
// (ở GAME/LOL/SF6 phím không bị giữ lại chờ combo → không trễ).
const uint16_t PROGMEM mouse_combo[] = {KC_SPC, KC_ENT, COMBO_END};

combo_t key_combos[] = {
    COMBO(mouse_combo, MS_TOGL),
};

// Trong MOUSE, 2 thumb là MS_EXIT → so combo theo phím của layer Colemak để Space+Enter vẫn tắt được.
uint8_t combo_ref_from_layer(uint8_t layer) {
    return layer == _MOUSE ? _COLEMAK_DH : layer;
}

// Giống require-prior-idle-ms của ZMK: vừa gõ phím khác < COMBO_PRIOR_IDLE_MS thì không kích combo.
// Chỉ tính phím gõ thật (chữ/số/ký hiệu/media), không tính mod, phím layer, phím chuột — như ZMK.
static uint32_t last_other_press;

static bool is_mouse_combo_key(keyrecord_t *record) {
    keypos_t k = record->event.key;
    return k.col == 4 && (k.row == 4 || k.row == 9); // thumb Space [4,4] và Enter [9,4]
}

bool pre_process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed || is_mouse_combo_key(record)) {
        return true;
    }
    uint16_t kc = keycode;
    if (IS_QK_LAYER_TAP(kc)) {
        kc = QK_LAYER_TAP_GET_TAP_KEYCODE(kc);
    } else if (IS_QK_MODS(kc)) {
        kc = QK_MODS_GET_BASIC_KEYCODE(kc);
    }
    if (IS_BASIC_KEYCODE(kc) || IS_CONSUMER_KEYCODE(kc) || IS_SYSTEM_KEYCODE(kc)) {
        last_other_press = timer_read32();
    }
    return true;
}

bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    switch (get_highest_layer(layer_state | default_layer_state)) {
        case _COLEMAK_DH:
            return timer_elapsed32(last_other_press) >= COMBO_PRIOR_IDLE_MS;
        case _MOUSE:
            return true; // không gõ chữ ở MOUSE; luôn cho thoát bằng combo (tránh thumb thứ 2 rơi xuống Enter/Space)
        default:
            return false;
    }
}

// ============ Phím tùy chỉnh ============
static bool     boot_held;
static uint32_t boot_timer;
static uint8_t  sf6_up_count;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SYS_BOOT:
            boot_held = record->event.pressed;
            if (boot_held) {
                boot_timer = timer_read32();
            }
            return false;

        case SF6_UP:
            if (record->event.pressed) {
                if (sf6_up_count++ == 0) {
                    register_code(KC_W);
                }
            } else if (sf6_up_count > 0 && --sf6_up_count == 0) {
                unregister_code(KC_W);
            }
            return false;

        case MS_TOGL:
            if (record->event.pressed) {
                layer_invert(_MOUSE);
            }
            return false;

        case MS_EXIT:
            if (record->event.pressed) {
                layer_off(_MOUSE);
            }
            return false;

        case MV_LEFT ... SP_YSLW:
            me_input((me_input_t)(keycode - MV_LEFT), record->event.pressed, timer_read32());
            return false;
    }
    return true;
}

void housekeeping_task_user(void) {
    if (boot_held && timer_elapsed32(boot_timer) >= BOOT_HOLD_MS) {
        boot_held = false;
        reset_keyboard();
    }
}

void keyboard_post_init_user(void) {
#ifdef NKRO_ENABLE
    // NKRO_DEFAULT_ON chỉ áp dụng khi EEPROM được khởi tạo lại → bật luôn mỗi lần khởi động.
    keymap_config.nkro = true;
#endif
}

// Tri-layer thủ công: LT() không tự kích tri-layer như TL_LOWR/TL_UPPR.
// Giữ LOWER + RAISE cùng lúc → bật ADJUST.
layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

// ============ Chuột: engine riêng qua pointing device (driver custom, không có cảm biến) ============
bool pointing_device_driver_init(void) {
    return true; // không có phần cứng; trả true để pointing_device_task chạy
}

void pointing_device_init_user(void) {
#ifdef POINTING_DEVICE_HIRES_SCROLL_ENABLE
    me_init(pointing_device_get_hires_scroll_resolution());
#else
    me_init(1);
#endif
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    me_delta_t d;
    if (me_tick(timer_read32(), &d)) {
        mouse_report.x += d.x;
        mouse_report.y += d.y;
        mouse_report.h += d.h;
        mouse_report.v += d.v;
    }
    return mouse_report;
}

// ---------- OLED ----------
// Sofle đã bật OLED trong info.json. Code mặc định ở sofle.c bị thay bằng oled_task_user (return false).
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

    // Dòng 1: Layer (tối đa 5 ký tự; đủ 5 thì không \n trong chuỗi). Đang giữ BOOT → BOOT!
    if (boot_held) {
        oled_write_ln_P(PSTR("BOOT!"), true);
    } else {
        switch (get_highest_layer(layer_state | default_layer_state)) {
            case _COLEMAK_DH:
                oled_write_ln_P(PSTR("COLMK"), false);
                break;
            case _GAME:
                oled_write_ln_P(PSTR("GAME "), false);
                break;
            case _LOL:
                oled_write_ln_P(PSTR("LOL\n"), false);
                break;
            case _SF6:
                oled_write_ln_P(PSTR("SF6\n"), false);
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
            case _SYS:
                oled_write_ln_P(PSTR("SYS\n"), false);
                break;
            default:
                oled_write_ln_P(PSTR("?\n"), false);
        }
    }

    // Dòng 2: Mod đang giữ (S/C/A/G)
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

// ---------- Encoder: trái = volume (mặc định sofle.c), phải = cuộn (qua engine chuột, cuộn hi-res; tắt ở LOL) ----------
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 1) {
        if (get_highest_layer(layer_state | default_layer_state) != _LOL) { // LOL: mảnh phải tắt
            me_wheel_notches(0, clockwise ? -ENCODER_SCROLL_STEPS : ENCODER_SCROLL_STEPS);
        }
        return false; // đã xử lý, không chạy hành vi mặc định (PgUp/PgDn)
    }
    return true; // encoder trái: để default (volume)
}
