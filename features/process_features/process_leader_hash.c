#include "process_leader_hash.h"

bool process_leader_hash(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        if (leader_hash_active() && !leader_hash_timed_out()) {
#ifndef LEADER_HASH_STRICT_KEY_PROCESSING
            if (IS_QK_MOD_TAP(keycode)) {
                keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
            } else if (IS_QK_LAYER_TAP(keycode)) {
                keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
            }
#endif

            if (!leader_hash_add(keycode)) {
                leader_hash_end();
                return true;
            }

#ifdef LEADER_HASH_PER_KEY_TIMING
            leader_hash_reset_timer();
#endif

            return false;
        } else if ((keycode >= FT_LEADER_HASH_1) && (keycode <= FT_LEADER_HASH_3) ) {
            leader_hash_start(keycode);
        }
    }

    return true;
}
