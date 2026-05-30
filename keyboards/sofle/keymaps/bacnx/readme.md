# bacnx — Sofle/rev1 keymap

Keymap mô phỏng cảm giác **Ferris Sweep (ZMK)** trên Sofle: Colemak-DH + Home Row Mods, thumb cluster gọn theo kiểu Sweep, có thêm chế độ **GAME** (QWERTY thuần, không HRM).

## Layers

| #   | Layer          | Cách vào                          | Nội dung chính                                              |
|-----|----------------|-----------------------------------|-------------------------------------------------------------|
| 0   | **COLEMAK-DH** | Mặc định                          | Colemak-DH + HRM (A/R/S/T, N/E/I/O)                         |
| 1   | **GAME**       | LaySel + 2 (TO)                   | QWERTY thuần, KHÔNG HRM — cảm giác bàn phím thường để chơi  |
| 2   | **LAYER_SELECT**| Giữ nút trái-trên trên BASE/GAME | + 1 = Colemak, + 2 = GAME, + 3 = LOL                        |
| 3   | **LOWER**      | Giữ thumb trái trong (LT)         | Số + ký hiệu (Sweep parity) + F1–F12                        |
| 4   | **RAISE**      | Giữ thumb phải trong (LT)         | Nav: mũi tên ở N/E/I/O, Home/End, PgUp/Dn, Ctrl-Z/X/C/V     |
| 5   | **ADJUST**     | Giữ LOWER + RAISE đồng thời       | Volume, media, QK_BOOT                                      |
| 6   | **MOUSE**      | Combo Space+Enter (toggle)        | Di chuột (N/E/I/O), scroll (Q/W/F/P), click trái/phải/giữa  |
| 7   | **LOL**        | LaySel + 3 (TO)                   | Liên Minh — chỉ nửa trái hoạt động                          |

## Home Row Mods (Colemak-DH base)

- **Trái:**  A = Super (GUI), R = Alt, S = Ctrl, T = Shift
- **Phải:**  N = Shift, E = Ctrl, I = Alt, O = Super (GUI)
- **Tap** = gõ chữ, **giữ** = phím mod.

Timing (Sweep parity):

| Tham số              | Giá trị | Ý nghĩa                                                               |
|----------------------|---------|-----------------------------------------------------------------------|
| `TAPPING_TERM`       | 280 ms  | Giữ lâu hơn 280 ms → là mod                                           |
| `QUICK_TAP_TERM`     | 175 ms  | Tap-rồi-tap-lại cùng phím trong 175 ms → vẫn là chữ (cho gõ lặp)      |
| `FLOW_TAP_TERM`      | 150 ms  | Nếu phím trước cách < 150 ms → bỏ qua hold (chống misfire khi đang gõ)|
| `PERMISSIVE_HOLD`    | bật     | Phím khác nhấn-và-thả trước khi thả mod-tap → là hold                 |
| `CHORDAL_HOLD`       | bật     | Hold chỉ kích nếu phím tiếp theo ở **nửa kia** (mimic Sweep "balanced")|

## Thumb cluster (Colemak-DH)

```
L: --   --   --   LT(LOW)/Bspc   Space        R: Enter   LT(RAI)/Tab   --   --   --
```

- Thumb **trong** (cạnh trung tâm): tap = Bspc/Tab, giữ = layer Lower/Raise.
- Thumb **trong-trong**: Space (trái), Enter (phải).
- Ba thumb ngoài: KC_NO (không dùng — HRM đã lo phần mod).

## Combo

| Combo                | Hành động       | Ghi chú                                              |
|----------------------|-----------------|------------------------------------------------------|
| `N + E` (HRM)        | Esc             | Trên Colemak-DH (vị trí home row index)              |
| `J + K` (plain)      | Esc             | Trên GAME layer (J/K là phím thường, không HRM)      |
| `Space + Enter`      | Toggle MOUSE    | Bật/tắt layer chuột; bấm lại để thoát                |

`COMBO_TERM = 50 ms`.

## GAME layer

QWERTY thuần (A S D F G / H J K L ;), **không** Home Row Mods, mod chính ở hàng thumb như bàn phím thường:

```
L thumbs: Gui Alt Ctl Space Space      R thumbs: Enter Bspc Ctl Alt Gui
```

Hợp cho FPS/MOBA (WASD, Shift sprint ở pinky-ngoài hàng dưới, Ctrl crouch ở thumb, Space jump). Thoát game mode: giữ nút **LaySel** (trái-trên) + **1** → quay về Colemak.

## Encoder

- **Trái:** Volume (default từ `info.json`)
- **Phải:** Scroll chuột (tốc độ chỉnh qua `ENCODER_SCROLL_STEPS` / `MOUSEKEY_WHEEL_DELTA` trong `config.h`)

## OLED

- **Master (trái):** Tên layer (5 ký tự) + mod đang giữ (S/C/A/G) + Caps + WPM.
- **Slave (phải):** Bongo cat theo WPM (đồng bộ qua `SPLIT_WPM_ENABLE`).
- Cả hai tự tắt sau `OLED_TIMEOUT` = 5 phút không hoạt động (đồng bộ qua `SPLIT_ACTIVITY_ENABLE`).

## Build

```bash
qmk compile -kb sofle/rev1 -km bacnx
```

## Tinh chỉnh nhanh

- HRM bị trễ khi gõ nhanh → giảm `TAPPING_TERM` xuống 250–260 hoặc giảm `FLOW_TAP_TERM` xuống 100.
- Vẫn dính mod khi gõ → tăng `FLOW_TAP_TERM` lên 175–200.
- Không hold được mod cùng-tay (ví dụ Ctrl+Shift+Z toàn từ tay trái) → bỏ `CHORDAL_HOLD` trong `config.h`.
- Tap-tap nhanh bị nuốt thành hold → tăng `QUICK_TAP_TERM` lên 200.
- Scroll encoder phải quá chậm/nhanh → chỉnh `ENCODER_SCROLL_STEPS` (1–4) hoặc `MOUSEKEY_WHEEL_DELTA` (1–4).
