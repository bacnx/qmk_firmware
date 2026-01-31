# bacnx — Sofle/rev1 keymap

Keymap tối giản cho **coding / Hyprland / tmux / Neovim**, dùng **Home Row Mods** ở base layer.

## Layers

| Layer   | Cách vào              | Nội dung chính                          |
|---------|------------------------|-----------------------------------------|
| **BASE**  | Mặc định               | QWERTY + HRM (A/S/D/F, J/K/L/;)         |
| **LOWER** | Thumb trái (LOWER)      | Số, ký hiệu, F1–F12 (coding)            |
| **RAISE** | Thumb phải (RAISE)      | Nav (mũi tên, PgUp/Dn, Home/End), Copy/Paste |
| **ADJUST**| Giữ LOWER + RAISE      | Volume, media, QK_BOOT                  |

## Home Row Mods (BASE)

- **Trái:** A = Super(GUI), S = Alt, D = Ctrl, F = Shift
- **Phải:** J = Shift, K = Ctrl, L = Alt, ; = Super(GUI)
- **Tap** = gõ chữ, **giữ** = phím mod (Hyprland Super, tmux Ctrl+b, Neovim C-A-S…).

## Thumb

- Trái: LOWER, Space
- Phải: Enter, RAISE

## Build

```bash
qmk compile -kb sofle/rev1 -km bacnx
```
