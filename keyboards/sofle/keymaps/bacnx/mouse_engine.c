// SPDX-License-Identifier: GPL-2.0-or-later
// Engine chuột kiểu ZMK — xem mouse_engine.h. Mọi thông số chỉnh được trong config.h.

#include "mouse_engine.h"

// ---------- Thông số mặc định (đặt lại trong config.h nếu muốn) ----------
// Cùng đơn vị với zmk-config (Sweep.keymap) để so sánh trực tiếp.
#ifndef MOUSE_MOVE_VAL
#    define MOUSE_MOVE_VAL 1200 // ZMK_POINTING_DEFAULT_MOVE_VAL: đơn vị/giây khi đạt max
#endif
#ifndef MOUSE_MOVE_X_NUM // MMV_X_NORMAL 2 1 → ngang 2400/s
#    define MOUSE_MOVE_X_NUM 2
#    define MOUSE_MOVE_X_DEN 1
#endif
#ifndef MOUSE_MOVE_Y_NUM // MMV_Y_NORMAL 3 2 → dọc 1800/s
#    define MOUSE_MOVE_Y_NUM 3
#    define MOUSE_MOVE_Y_DEN 2
#endif
#ifndef MOUSE_MOVE_TIME_TO_MAX
#    define MOUSE_MOVE_TIME_TO_MAX 500 // ms, &mmv time-to-max-speed-ms (tăng tốc tuyến tính)
#endif
#ifndef MOUSE_SCROLL_VAL
#    define MOUSE_SCROLL_VAL 60 // ZMK_POINTING_DEFAULT_SCRL_VAL: 1/16 nấc mỗi giây (60 = 3.75 nấc/s)
#endif
#ifndef MOUSE_SCROLL_TIME_TO_MAX
#    define MOUSE_SCROLL_TIME_TO_MAX 0 // 0 = tốc độ đều (ZMK smooth scrolling bỏ qua tăng tốc)
#endif
#ifndef MOUSE_TICK_MS
#    define MOUSE_TICK_MS 8 // gửi report mỗi 8 ms (ZMK: 16 ms)
#endif
#ifndef MOUSE_REPORT_LIMIT
#    define MOUSE_REPORT_LIMIT 127 // giới hạn mỗi trục trong 1 report (int8)
#endif

// Phím tốc độ (giữ), nhân dồn — giống SPEED_* / SCRL_SLOW trong zmk-config.
#ifndef MOUSE_SPEED_SLOW_NUM // A: chậm cả 2 trục khi di chuyển
#    define MOUSE_SPEED_SLOW_NUM 1
#    define MOUSE_SPEED_SLOW_DEN 6
#endif
#ifndef MOUSE_SCROLL_SLOW_NUM // A: chậm khi cuộn
#    define MOUSE_SCROLL_SLOW_NUM 1
#    define MOUSE_SCROLL_SLOW_DEN 3
#endif
#ifndef MOUSE_SPEED_FAST_NUM // R / S: nhanh trục X / Y
#    define MOUSE_SPEED_FAST_NUM 2
#    define MOUSE_SPEED_FAST_DEN 1
#endif
#ifndef MOUSE_SPEED_SLOWER_NUM // X / C: chậm trục X / Y
#    define MOUSE_SPEED_SLOWER_NUM 1
#    define MOUSE_SPEED_SLOWER_DEN 4
#endif

#define ZMK_WHEEL_RESOLUTION 16 // ZMK smooth scrolling: 1 nấc = 16 đơn vị
#define MAX_TICK_MS 50          // vòng lặp bị chậm thì không nhảy chuột quá xa

enum { AX_X, AX_Y, AX_H, AX_V, AX_COUNT };

typedef struct {
    int8_t   dir;   // -1, 0, +1 (2 phím ngược chiều cùng giữ = 0, như ZMK cộng tốc độ)
    uint32_t start; // lúc bắt đầu chạy (để tính tăng tốc)
    int32_t  rem;   // phần lẻ còn lại, đơn vị 1/1000
} axis_t;

typedef struct {
    int32_t num;
    int32_t den;
} ratio_t;

static uint16_t held;
static axis_t   axes[AX_COUNT];
static int32_t  pend_h, pend_v; // đơn vị hi-res chờ gửi (encoder + phần vượt giới hạn report)
static uint16_t wheel_res = 1;
static uint32_t last_tick;

#define HELD(input) ((held & (uint16_t)(1u << (input))) != 0)

void me_init(uint16_t wheel_resolution) {
    wheel_res = wheel_resolution ? wheel_resolution : 1;
    me_reset();
}

void me_reset(void) {
    held = 0;
    for (uint8_t i = 0; i < AX_COUNT; i++) {
        axes[i] = (axis_t){0};
    }
    pend_h = 0;
    pend_v = 0;
}

static void set_dir(axis_t *a, int8_t dir, uint32_t now) {
    if (dir == a->dir) {
        return;
    }
    if (a->dir == 0) {
        a->start = now; // bắt đầu tăng tốc lại từ 0
    }
    a->dir = dir;
    a->rem = 0;
}

static int8_t dir_of(me_input_t neg, me_input_t pos) {
    return (int8_t)((HELD(pos) ? 1 : 0) - (HELD(neg) ? 1 : 0));
}

void me_input(me_input_t input, bool pressed, uint32_t now_ms) {
    if (input >= ME_INPUT_COUNT) {
        return;
    }
    if (pressed) {
        held |= (uint16_t)(1u << input);
    } else {
        held &= (uint16_t)~(1u << input);
    }
    set_dir(&axes[AX_X], dir_of(ME_MOVE_LEFT, ME_MOVE_RIGHT), now_ms);
    set_dir(&axes[AX_Y], dir_of(ME_MOVE_UP, ME_MOVE_DOWN), now_ms);
    set_dir(&axes[AX_H], dir_of(ME_WHEEL_LEFT, ME_WHEEL_RIGHT), now_ms);
    set_dir(&axes[AX_V], dir_of(ME_WHEEL_DOWN, ME_WHEEL_UP), now_ms);
}

void me_wheel_notches(int16_t h_notches, int16_t v_notches) {
    pend_h += (int32_t)h_notches * wheel_res;
    pend_v += (int32_t)v_notches * wheel_res;
}

static void mul(ratio_t *r, int32_t num, int32_t den) {
    r->num *= num;
    r->den *= den;
}

// Tốc độ max của trục (đơn vị/giây) đã nhân phím tốc độ đang giữ.
static ratio_t axis_speed(uint8_t ax) {
    bool    wheel = (ax == AX_H || ax == AX_V);
    bool    horiz = (ax == AX_X || ax == AX_H);
    ratio_t r;
    switch (ax) {
        case AX_X:
            r = (ratio_t){MOUSE_MOVE_VAL * MOUSE_MOVE_X_NUM, MOUSE_MOVE_X_DEN};
            break;
        case AX_Y:
            r = (ratio_t){MOUSE_MOVE_VAL * MOUSE_MOVE_Y_NUM, MOUSE_MOVE_Y_DEN};
            break;
        default:
            r = (ratio_t){(int32_t)MOUSE_SCROLL_VAL * wheel_res, ZMK_WHEEL_RESOLUTION};
            break;
    }
    if (HELD(ME_SPEED_SLOW)) {
        if (wheel) {
            mul(&r, MOUSE_SCROLL_SLOW_NUM, MOUSE_SCROLL_SLOW_DEN);
        } else {
            mul(&r, MOUSE_SPEED_SLOW_NUM, MOUSE_SPEED_SLOW_DEN);
        }
    }
    if (HELD(horiz ? ME_SPEED_XFAST : ME_SPEED_YFAST)) {
        mul(&r, MOUSE_SPEED_FAST_NUM, MOUSE_SPEED_FAST_DEN);
    }
    if (HELD(horiz ? ME_SPEED_XSLOW : ME_SPEED_YSLOW)) {
        mul(&r, MOUSE_SPEED_SLOWER_NUM, MOUSE_SPEED_SLOWER_DEN);
    }
    return r;
}

// Lượng di chuyển của 1 trục trong dt ms (đã cộng phần lẻ lần trước).
static int32_t step_axis(uint8_t ax, uint32_t now, uint32_t dt) {
    axis_t *a = &axes[ax];
    if (a->dir == 0) {
        return 0;
    }
    uint32_t ttm     = (ax == AX_X || ax == AX_Y) ? MOUSE_MOVE_TIME_TO_MAX : MOUSE_SCROLL_TIME_TO_MAX;
    uint32_t elapsed = now - a->start;
    int64_t  ramp_n  = 1;
    int64_t  ramp_d  = 1;
    if (ttm > 0 && elapsed < ttm) {
        ramp_n = elapsed; // tăng tuyến tính: tốc độ = max * elapsed / ttm
        ramp_d = ttm;
    }
    ratio_t s     = axis_speed(ax);
    int64_t milli = ((int64_t)s.num * ramp_n * dt) / ((int64_t)s.den * ramp_d); // (đơn vị/giây) * ms = 1/1000 đơn vị
    int64_t acc   = a->rem + a->dir * milli;
    int32_t out   = (int32_t)(acc / 1000);
    a->rem        = (int32_t)(acc - (int64_t)out * 1000);
    return out;
}

static int16_t clamp_report(int32_t v) {
    if (v > MOUSE_REPORT_LIMIT) return MOUSE_REPORT_LIMIT;
    if (v < -MOUSE_REPORT_LIMIT) return -MOUSE_REPORT_LIMIT;
    return (int16_t)v;
}

bool me_tick(uint32_t now_ms, me_delta_t *out) {
    *out = (me_delta_t){0};

    bool active = (pend_h != 0 || pend_v != 0);
    for (uint8_t i = 0; i < AX_COUNT; i++) {
        active |= (axes[i].dir != 0);
    }
    if (!active) {
        last_tick = now_ms;
        return false;
    }

    uint32_t dt = now_ms - last_tick;
    if (dt < MOUSE_TICK_MS) {
        return false;
    }
    if (dt > MAX_TICK_MS) {
        dt = MAX_TICK_MS;
    }
    last_tick = now_ms;

    // Di chuyển: phần vượt giới hạn report giữ lại trong rem cho lần sau.
    for (uint8_t ax = AX_X; ax <= AX_Y; ax++) {
        int32_t v = step_axis(ax, now_ms, dt);
        int16_t c = clamp_report(v);
        axes[ax].rem += (v - c) * 1000;
        if (ax == AX_X) {
            out->x = c;
        } else {
            out->y = c;
        }
    }

    // Cuộn: gộp với lượng chờ (encoder); phần vượt giới hạn để lại lần sau.
    pend_h += step_axis(AX_H, now_ms, dt);
    pend_v += step_axis(AX_V, now_ms, dt);
    out->h = clamp_report(pend_h);
    out->v = clamp_report(pend_v);
    pend_h -= out->h;
    pend_v -= out->v;

    return out->x || out->y || out->h || out->v;
}
