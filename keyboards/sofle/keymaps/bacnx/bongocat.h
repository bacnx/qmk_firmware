// SPDX-License-Identifier: GPL-2.0-or-later
// Bongo cat OLED animation for slave half (WPM-based).
// Call from oled_task_user() when !is_keyboard_master().

#pragma once

#ifdef OLED_ENABLE
void render_bongocat_slave(void);
#endif
