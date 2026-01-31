// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

// ---------- Tri-layer (giữ LOWER + RAISE → ADJUST) ----------
#define TRI_LAYER_LOWER_LAYER  1  // _LOWER
#define TRI_LAYER_UPPER_LAYER  2  // _RAISE
#define TRI_LAYER_ADJUST_LAYER 3  // _ADJUST

// ---------- Home Row Mods — tap/hold thoải mái hơn ----------
#define TAPPING_TERM 200       // ms: tap nhanh = chữ, giữ lâu = mod
#define PERMISSIVE_HOLD        // mod-tap: nếu phím khác nhấn trước khi thả → coi là hold (mod)
