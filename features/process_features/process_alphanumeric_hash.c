#include "process_alphanumeric_hash.h"

bool process_alphanumeric_hash(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        if (alphanumeric_hash_active() && !alphanumeric_hash_timed_out()) {
#ifndef ALPHANUMERIC_HASH_STRICT_KEY_PROCESSING
            if (IS_QK_MOD_TAP(keycode)) {
                keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
            } else if (IS_QK_LAYER_TAP(keycode)) {
                keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
            }
#endif

            if (!alphanumeric_hash_add(keycode)) {
                alphanumeric_hash_end();
                return true;
            }

#ifdef ALPHANUMERIC_HASH_PER_KEY_TIMING
            alphanumeric_hash_reset_timer();
#endif

            return false;
        } else if (keycode == FT_ALPHANUMERIC_HASH) {
            alphanumeric_hash_start();
        }
    }

    return true;
}
