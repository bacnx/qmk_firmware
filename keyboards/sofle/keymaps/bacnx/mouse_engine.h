// SPDX-License-Identifier: GPL-2.0-or-later
// Engine chuột kiểu ZMK (mmv/msc + input-processor scaler) cho layer MOUSE.
//
// Mousekey của QMK chỉ có tốc độ chung cho cả 2 trục, nên phần di chuyển/cuộn
// được tự tính ở đây rồi đẩy ra qua pointing device (driver "custom"):
// - Di chuyển: tốc độ tăng tuyến tính từ 0 tới max trong MOUSE_MOVE_TIME_TO_MAX ms.
// - Cuộn: tốc độ đều (giống ZMK khi bật smooth scrolling), cuộn hi-res.
// - Phím tốc độ giữ-để-dùng, nhân dồn theo từng trục (vd. YFAST + XSLOW).
//
// File này không phụ thuộc QMK (chỉ cần thời gian ms truyền vào) để test được trên máy host.

#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    ME_MOVE_LEFT,
    ME_MOVE_RIGHT,
    ME_MOVE_UP,
    ME_MOVE_DOWN,
    ME_WHEEL_LEFT,
    ME_WHEEL_RIGHT,
    ME_WHEEL_UP,
    ME_WHEEL_DOWN,
    ME_SPEED_SLOW,  // chậm cả 2 trục
    ME_SPEED_XFAST, // nhanh trục ngang
    ME_SPEED_YFAST, // nhanh trục dọc
    ME_SPEED_XSLOW, // chậm trục ngang
    ME_SPEED_YSLOW, // chậm trục dọc
    ME_INPUT_COUNT
} me_input_t;

typedef struct {
    int16_t x; // + = sang phải
    int16_t y; // + = xuống dưới
    int16_t h; // + = cuộn sang phải (đơn vị hi-res)
    int16_t v; // + = cuộn lên (đơn vị hi-res)
} me_delta_t;

// wheel_resolution: số đơn vị hi-res cho 1 nấc cuộn (pointing_device_get_hires_scroll_resolution(), 1 nếu không hi-res).
void me_init(uint16_t wheel_resolution);

// Gọi khi phím nhấn/thả. now_ms: timer_read32().
void me_input(me_input_t input, bool pressed, uint32_t now_ms);

// Cuộn một lượng cố định (encoder), tính bằng nấc. + = lên / phải.
void me_wheel_notches(int16_t h_notches, int16_t v_notches);

// Gọi mỗi vòng lặp. Trả về true nếu out có chuyển động (out luôn được ghi).
bool me_tick(uint32_t now_ms, me_delta_t *out);

// Thả hết phím di chuyển/cuộn/tốc độ (vd. khi đổi mode).
void me_reset(void);
