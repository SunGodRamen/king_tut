#include QMK_KEYBOARD_H

#include "features/features.h"
#include "features/feature_keycodes.h"

#ifdef COMBO_ENABLE
#include "def/keymap_combos.h"
#endif

#ifdef LEADER_HASH_ENABLE
#include "def/leader_hash_end.h"
#endif

#ifdef LEADER_ENABLE
#include "def/leader_end.h"
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return process_record_features(record);
}

void matrix_scan_user(void) {
  feature_task();
}

uint8_t layer_state_set_user(uint8_t state) {
    uint8_t layer = biton(state);

    ergodox_board_led_off();
    set_leds(LED_OFF, 1, 1, 1);  // Turn off all LEDs

    switch (layer) {
        case 1:
            set_leds(LED_ON, 1, 0, 0);
            break;
        case 2:
            set_leds(LED_ON, 0, 1, 0);
            break;
        case 3:
            set_leds(LED_ON, 1, 1, 0);
            break;
        case 4:
            set_leds(LED_ON, 0, 0, 1);
            break;
        case 5:
            set_leds(LED_ON, 1, 0, 1);
            break;
        case 6:
            set_leds(LED_ON, 0, 1, 1);
            break;
        case 7:
            set_leds(LED_ON, 1, 1, 1);
            break;
        default:
            break;
    }

    return state;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_ergodox_pretty(
    ___,  _F1,  _F2,  _F3,  _F4, _F5, ___,       ___,   _F6, _F7,  _F8,  _F9,  _F10, ___,
    ___,  SCL_, CM_,  DT_,  P_,  Y_,  MACRO,     MACRO, F_,  G_,   C_,   R_,   L_,   ___,
    ___,  A_,   AO_,  GE_,  CU_, I_,                    D_,  H_,   T_,   N_,   S_,   ___,
    ___,  DQ_,  Q_,   J_,   K_,  X_,  DM_P2,     DM_P1, B_,  M_,   W_,   V_,   Z_,   ___,
    _F13, _F14, _F15, _F16, _F17,                            _F18, _F19, _F20, _F21, _F22,
                                   ___, ___,     ___,   ___,
                                        ___,     ___,
                            MDRAW, LS_, AHASH,   MEDIA, NV_SPC, NUMBR
  ),
  [1] = LAYOUT_ergodox_pretty(
    ___, ___, ___, ___, ___, ___, ___,          ___, ___, ___,  ___,  ___,  ___,  ___,
    ___, ___, ___, ___, ___, ___, ___,          ___, ___, WBck, PTAB, NTAB, WFwd, ___,
    ___, ___, ___, ___, ___, ___,                    ___, ArL,  ArD,  ArU,  ArR,  ___,
    ___, ___, ___, ___, ___, ___, ___,          ___, ___, HOME, PGDN, PGUP, END,  ___,
    ___, ___, ___, ___, ___,                              ___,  ___,  ___,  ___,  ___,
                             ___, ___,          ___, ___,
                                  ___,          ___,
                        ___, ___, ___,          ___, FROM, ___
  ),
  [2] = LAYOUT_ergodox_pretty(
    ___, ___, ___, ___, ___, ___, ___,          ___, ___, ___, ___, ___, ___,     ___,
    ___, ___, ___, ___, ___, ___, ___,          ___, XTARE, _7,  _8,  _9,  XINCR,   ___,
    ___, ___, ___, ___, ___, ___,                    _0,    _4,  _5,  _6,  XVALU, ___,
    ___, ___, ___, ___, ___, ___, ___,          ___, XTARE, _1,  _2,  _3,  XDECR,   ___,
    ___, ___, ___, ___, ___,                              ___, ___, ___, ___, ___,
                             ___, ___,          ___, ___,
                                  ___,          ___,
                        ___, ___, ___,          ___, ___, FROM
  ),
  [3] = LAYOUT_ergodox_pretty(
    ___, ___, ___, ___, ___, ___, ___,          ___,   ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, ___, FROM,         FROM,  ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, ___,                      ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, ___, DM_R2,        DM_R1, ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___,                              ___, ___, ___, ___, ___,
                              ___, ___,         ___, ___,
                                   ___,         ___,
                         ___, ___, ___,         ___, ___, ___
  ),
  [4] = LAYOUT_ergodox_pretty(
    ___, ___, ___, ___, ___, ___, ___,          ___, ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, ___, ___,          ___, ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, ___,                    VUP, PRV, PLAY, NXT, ___, ___,
    ___, ___, ___, ___, ___, ___, ___,          ___, VDN, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___,                              ___, ___, ___, ___, ___,
                              ___, ___,         ___, ___,
                                   ___,         ___,
                         ___, ___, ___,         FROM, ___, ___
  ),
};

