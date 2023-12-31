#ifndef FEATURE_KEYCODES_H
#define FEATURE_KEYCODES_H

#include "keycodes.h"

enum feature_keycodes {
    FEATURE_KEYCODES = QK_PROGRAMMABLE_BUTTON_1,
    // LEADER HASH KEY
    FT_LEADER_HASH_1,
    FT_LEADER_HASH_2,
    FT_LEADER_HASH_3,
    // ALPHANUMERIC HASH FUNCTION KEY
    FT_ALPHANUMERIC_HASH,
    // KEYCODE RAWHID MODIFIER
    FT_RAW_MOD,
    // SCAN CODE MODIFIER
    FT_SCAN_MOD,
    // COUNTER KEYS
    COUNTER_TARE,
    COUNTER_INCR,
    COUNTER_DECR,
    COUNTER_VALUE,
};

enum feature_aliases {
    // LEADER HASH KEY
    LHASH1 = FT_LEADER_HASH_1,
    LHASH2 = FT_LEADER_HASH_2,
    LHASH3 = FT_LEADER_HASH_3,
    // ALPHANUMERIC HASH FUNCTION KEY
    AHASH = FT_ALPHANUMERIC_HASH,
    // KEYCODE RAWHID MODIFIER
    MDRAW = FT_RAW_MOD,
    // SCAN CODE MODIFIER
    MDSCN = FT_SCAN_MOD,
    // COUNTER KEYS
    XTARE = COUNTER_TARE,
    XINCR = COUNTER_INCR,
    XDECR = COUNTER_DECR,
    XVALU = COUNTER_VALUE
};

#endif