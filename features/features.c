#include "features.h"

#ifdef MOD_KEYS_ENABLE
#    include "process_features/process_mod_keys.h"
#endif

#ifdef LEADER_HASH_ENABLE
#    include "process_features/process_leader_hash.h"
#    include "leader_hash.h"
#endif

#ifdef ALPHANUMERIC_HASH_ENABLE
#    include "process_features/process_alphanumeric_hash.h"
#    include "alphanumeric_hash.h"
#endif

#ifdef RAWHID_MOD_ENABLE
#    include "process_features/process_rawhid_mod.h"
#endif

#ifdef COUNTER_KEYS_ENABLE
#    include "process_features/process_counter_keys.h"
#endif

bool process_record_features(keyrecord_t *record) {
    uint16_t keycode = get_record_keycode(record, true);
    if (!(
#ifdef MOD_KEYS_ENABLE
    process_mod_keys(keycode, record) &&
#endif
#ifdef LEADER_HASH_ENABLE
    process_leader_hash(keycode, record) &&
#endif
#ifdef ALPHANUMERIC_HASH_ENABLE
    process_alphanumeric_hash(keycode, record) &&
#endif
#ifdef RAWHID_MOD_ENABLE
    process_rawhid_mod(keycode, record) &&
#endif
#ifdef COUNTER_KEYS_ENABLE
    process_counter_keys(keycode, record) &&
#endif
            true)) {
        return false;
    }

    switch (keycode) {
    default:
        break;
    }

    return true;
}

void feature_task(void) {
#ifdef LEADER_HASH_ENABLE
    leader_hash_task();
#endif
#ifdef ALPHANUMERIC_HASH_ENABLE
    alphanumeric_hash_task();
#endif
}
