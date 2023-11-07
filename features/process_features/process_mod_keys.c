#include "process_mod_keys.h"

bool process_mod_keys(uint16_t keycode, keyrecord_t *record) {
    static uint16_t registered_keycode = KC_NO;

    if (registered_keycode != KC_NO) {
        unregister_code16(registered_keycode);
        registered_keycode = KC_NO;
    }

    if (record->event.pressed) {
        const uint8_t mods = get_mods();
#ifndef NO_ACTION_ONESHOT
        uint8_t mod_masks = mods | get_weak_mods() | get_oneshot_mods();
#else
        uint8_t mod_masks = mods;
#endif

        if (mod_masks) {
            if ((IS_QK_MOD_TAP(keycode) || IS_QK_LAYER_TAP(keycode)) &&
                record->tap.count == 0) {
                return true;
            }

            for (int i = 0; i < NUM_CUSTOM_MOD_KEYS; ++i) {
                keypos_t modifier_keypos = {.col = custom_mod_keys[i].modifier & 0xF, .row = custom_mod_keys[i].modifier >> 4};
                uint16_t modifier_keycode = keymap_key_to_keycode(0, modifier_keypos);

                if (keycode == custom_mod_keys[i].keycode && ((mod_masks & MOD_BIT(custom_mod_keys[i].modifier)) || (modifier_keycode != KC_NO && (get_mods() & (1 << (modifier_keycode - KC_LCTL)))))) {
                    registered_keycode = custom_mod_keys[i].mod_keycode;
                    uint8_t mod_mask = MOD_BIT(custom_mod_keys[i].modifier);

                    if (IS_QK_MODS(registered_keycode) &&
                        (QK_MODS_GET_MODS(registered_keycode) & mod_mask) != 0) {
                        register_code16(registered_keycode);
                    } else {
                        if (IS_MODIFIER_KEYCODE(custom_mod_keys[i].modifier)) {
                            del_weak_mods(mod_mask);
#ifndef NO_ACTION_ONESHOT
                            del_oneshot_mods(mod_mask);
#endif
                            unregister_mods(mod_mask);
                        } else {
                            unregister_code(custom_mod_keys[i].modifier);
                        }
                        register_code16(registered_keycode);
                        set_mods(mods);
                    }
                    return false;
                }
            }
        }
    }

    return true;
}
