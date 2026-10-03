# bacnx — Sofle/rev1 keymap

Keymap mô phỏng cảm giác **Ferris Sweep (ZMK, [bacnx/zmk-config](https://github.com/bacnx/zmk-config))** trên Sofle: Colemak-DH, thumb cluster kiểu Sweep, **không home row mods** (mod nằm ở cụm ngón cái), cộng thêm các mode game: **GAME** (QWERTY thường), **LOL**, **SF6**.

## Layers

| #   | Layer          | Cách vào                       | Nội dung chính                                                    |
|-----|----------------|--------------------------------|-------------------------------------------------------------------|
| 0   | **COLEMAK-DH** | Mặc định / SYS + 1             | Colemak-DH, mod ở thumb ngoài                                     |
| 1   | **GAME**       | SYS + 2                        | QWERTY thuần như bàn phím thường — không combo, không hold-tap    |
| 2   | **LOL**        | SYS + 3                        | Liên Minh — chỉ nửa trái hoạt động                                |
| 3   | **SF6**        | SYS + 4                        | Street Fighter 6 — kiểu hitbox, phím mặc định Classic             |
| 4   | **LOWER**      | Giữ thumb trái trong (LT)      | Số + ký hiệu + F1–F12                                             |
| 5   | **RAISE**      | Giữ thumb phải trong (LT)      | Nav: ← ↓ ↑ → ở N/E/I/O, Home/End, PgUp/Dn + mod thường tay trái   |
| 6   | **ADJUST**     | Giữ LOWER + RAISE              | Volume, media                                                     |
| 7   | **MOUSE**      | Combo Space+Enter / SYS + 5    | Chuột giống layer Mouse trong zmk-config                          |
| 8   | **SYS**        | Giữ phím trái-trên (mọi mode)  | Đổi mode, bật chuột, bootloader                                   |

## Đổi mode & bootloader (layer SYS)

Phím **trái-trên** ở **mọi** mode (Colemak, GAME, LOL, SF6) là phím giữ để vào SYS:

```
SYS: | (giữ) | Colemak | GAME | LOL | SF6 | Mouse |      | -- | -- | -- | -- | -- | BOOT |
     (mọi phím khác trong SYS đều tắt)
```

- **BOOT** (góc phải-trên): phải **giữ 1 giây** mới vào bootloader; OLED hiện `BOOT!` trong lúc giữ. Cần cả 2 tay (út trái giữ SYS, út phải giữ BOOT) nên khó bấm nhầm. Nửa vào bootloader là **nửa đang cắm USB**.
- Flash 2 nửa: cắm USB nửa trái → SYS + BOOT → chép `.uf2`; rồi cắm USB nửa phải và làm lại. Cùng một firmware cho cả 2 nửa (tay trái/phải nhận theo chân D4).
- Cách khác nếu firmware hỏng:
  - **Bootmagic:** giữ phím góc ngoài-trên của nửa đang cắm USB (trái: phím SYS, phải: phím góc phải-trên) rồi cắm cáp. Cách này xoá EEPROM.
  - **Nút reset:** bấm nhanh 2 lần nút reset trên PCB (RP2040 double-tap reset).
- Rút cáp cắm lại luôn về Colemak-DH.

## Colemak-DH (layer 0)

```
| SYS  |  1  |  2  |  3  |  4  |  5  |              |  6  |  7  |  8  |  9  |  0  |  `   |
| Esc  |  Q  |  W  |  F  |  P  |  B  |              |  J  |  L  |  U  |  Y  |  ;  | Bspc |
| Tab  |  A  |  R  |  S  |  T  |  G  |              |  M  |  N  |  E  |  I  |  O  |  '   |
| Shift|  Z  |  X  |  C  |  D  |  V  | Mute |  | Play |  K  |  H  |  ,  |  .  |  /  | Shift|
       | Alt | Gui |Ctrl |LOW/⌫|Space|              |Enter|RAI/⇥|Ctrl | Gui | Alt |
```

- Thumb **trong**: tap = Bspc / Tab, giữ = LOWER / RAISE (layer-tap). Tap rồi giữ lại nhanh (< 175 ms) = lặp Bspc/Tab.
- 3 thumb ngoài = mod thường: Ctrl gần ngón cái nhất, rồi Gui, Alt ngoài cùng.
- Nút nhấn encoder: trái = Mute, phải = Play/Pause.

Timing (giống `&lt` trong zmk-config):

| Tham số           | Giá trị | Ý nghĩa                                               |
|-------------------|---------|-------------------------------------------------------|
| `TAPPING_TERM`    | 200 ms  | Giữ thumb lâu hơn 200 ms → layer                      |
| `QUICK_TAP_TERM`  | 175 ms  | Tap rồi giữ lại cùng phím trong 175 ms → lặp phím     |
| `PERMISSIVE_HOLD` | bật     | Phím khác nhấn-và-thả trong lúc giữ thumb → layer     |

## RAISE (Nav)

```
| Esc  | Ins |  -- |PrtSc|  -- |  -- |              |  -- |PgUp | Del |  -- |  -- |  --  |
| Caps | Gui | Alt |Ctrl |Shift|  -- |              |Home |  ←  |  ↓  |  ↑  |  →  |  --  |
|  --  |  -- |Ctl-Z|Ctl-X|Ctl-C|Ctl-V|              | End |PgDn |  -- |  -- |  -- |  --  |
```

Hàng home trái là mod thường (không tap-hold): giữ RAISE + Shift/Ctrl + mũi tên để chọn chữ / nhảy theo từ.

## Combo

| Combo           | Hành động    | Ghi chú                                                                   |
|-----------------|--------------|---------------------------------------------------------------------------|
| `Space + Enter` | Toggle MOUSE | Chỉ chạy ở Colemak-DH và MOUSE; bỏ qua nếu vừa gõ phím khác < 150 ms      |

`COMBO_TERM = 60 ms`. Ở GAME / LOL / SF6 không có combo nào, nên phím không bị giữ lại chờ combo (không trễ).

## GAME

QWERTY thuần như bàn phím thường, không combo / hold-tap. Mod ở thumb: `-- Alt Ctrl Space Space | Enter Bspc Ctrl Alt --` (bỏ Super để không lỡ chạm Super/Start menu khi chơi). Shift ở út hàng dưới.

## SF6 (Street Fighter 6, Classic)

```
| SYS  |  1  |  2  |  3  |  4  |  5  |              |  6  |  7  |  8  |  9  |  0  |  --  |
| Esc  |  -- |  -- | W ↑ |  -- |  -- |              |  Y  |U LP |I MP |O HP |  P  |  --  |
|  --  |  -- | A ← | S ↓ | D → |  -- |              |  H  |J LK |K MK |L HK |  ;  |  --  |
|  --  |  -- |  -- |  -- |  -- |  -- |  --  |  |  -- |  N  |  M  |  ,  |  .  |  /  |  --  |
       |  -- |  -- |  -- |  -- | W ↑ |              |Enter|Bspc |  -- |  -- |  -- |
```

- Gửi đúng phím **mặc định Classic** của SF6 (WASD + U I O / J K L), nên không cần chỉnh trong game.
- Tay trái đặt **áp út / giữa / trỏ** lên 3 phím home: **← ↓ →**. Ngón út nghỉ, ngón trỏ (khoẻ) bấm →.
- **Lên** có 2 chỗ: **ngón cái** (kiểu hitbox, khuyên dùng) hoặc phía trên ngón giữa (kiểu WASD).
- **Hướng chéo = bấm 2 hướng cùng lúc**, mỗi hướng một ngón:
  - ↙ = giữa + áp út (↓ + ←), ↘ = giữa + trỏ (↓ + →)
  - ↖ = ngón cái + áp út (↑ + ←), ↗ = ngón cái + trỏ (↑ + →)
  - Quarter-circle (↓ ↘ →): giữ ↓ bằng ngón giữa, thêm → bằng ngón trỏ, rồi nhả ↓.
  - Trái + Phải cùng lúc: SF6 tự coi là đứng yên (neutral).
- `P`, `;`, `Y`, `H`… để trống — gán trong game cho Drive Parry / Drive Impact / Throw nếu muốn.
- Không combo, không tap-hold, không mod → không trễ và không lỡ thoát game.

## MOUSE (giống zmk-config)

```
|  --  | Gui | Alt |Ctrl |Shift| MB4 |              |  -- |  -- |  -- |  -- |  -- |  --  |
|  --  |Slow |XFast|YFast|LClk |RClk |              |  -- | M ← | M ↓ | M ↑ | M → |  --  |
|  --  |  -- |XSlow|YSlow|MClk | MB5 |              |  -- | W ← | W ↓ | W ↑ | W → |  --  |
       |  -- |  -- |  -- | off | off |              | off | off |  -- |  -- |  -- |
```

- Bật/tắt: Space + Enter. Thoát: chạm 1 trong 4 thumb trong (`off`).
- N/E/I/O = di chuyển; H , . / = cuộn (cùng ngón, xuống 1 hàng).
- Phím tốc độ **giữ để dùng và nhân dồn theo từng trục**: A = chậm cả 2 trục (÷6, cuộn ÷3), R/S = nhanh ngang/dọc (×2), X/C = chậm ngang/dọc (÷4). Vd. S + X = dọc nhanh, ngang chậm.
- QMK mousekey không có tốc độ theo trục, nên chuột chạy bằng engine riêng (`mouse_engine.c`) qua pointing device, với thông số và đơn vị giống zmk-config:
  - Di chuyển tăng tốc tuyến tính tới max trong 500 ms: ngang 2400/s, dọc 1800/s.
  - Cuộn **mượt** (hi-res), tốc độ đều 3.75 nấc/s — đúng như ZMK khi bật smooth scrolling.

## Encoder

- **Trái:** Volume (mặc định từ `sofle.c`).
- **Phải:** Cuộn (qua engine chuột, cuộn hi-res); `ENCODER_SCROLL_STEPS` nấc mỗi bước.

## OLED

- **Master:** Tên layer/mode (5 ký tự, `BOOT!` khi đang giữ BOOT) + mod đang giữ (S/C/A/G) + Caps + WPM.
- **Slave:** Bongo cat theo WPM (đồng bộ qua `SPLIT_WPM_ENABLE`).
- Cả hai tự tắt sau `OLED_TIMEOUT` = 5 phút không hoạt động.

## Build

```bash
qmk compile -kb sofle/rev1 -km bacnx
```

## Tinh chỉnh nhanh (`config.h`)

- Tap Bspc/Tab hay bị thành layer → tăng `TAPPING_TERM` (220–250). Vào layer bị chậm → giảm (180).
- Space + Enter khó kích → tăng `COMBO_TERM` (80); hay kích nhầm khi gõ → tăng `COMBO_PRIOR_IDLE_MS`.
- Chuột nhanh/chậm → `MOUSE_MOVE_VAL`, tỉ lệ ngang/dọc `MOUSE_MOVE_X_*` / `MOUSE_MOVE_Y_*`, tăng tốc `MOUSE_MOVE_TIME_TO_MAX`.
- Cuộn nhanh/chậm → `MOUSE_SCROLL_VAL` (đơn vị 1/16 nấc mỗi giây, như ZMK); encoder → `ENCODER_SCROLL_STEPS`.
- Giữ BOOT lâu/ngắn hơn → `BOOT_HOLD_MS`.
