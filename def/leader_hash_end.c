#include "leader_hash_end.h"

// Define leader sequences with associated function pointers
void macro_fname(void) {
    SEND_STRING("Alexander");
}

void macro_lname(void) {
    SEND_STRING("von Stuelpnagel");
}

void macro_email(void) {
    SEND_STRING("avons394@gmail.com");
}

void macro_phone(void) {
    SEND_STRING("3236466099");
}

void hotkey_vs_command(void) {
    register_code16(LS_);
    register_code16(LCTL(P_));
    unregister_code16(LS_);
}

void hotkey_vs_open(void) {
    register_code16(KC_LCTL);
    register_code16(K_);
    wait_ms(100);
    register_code16(O_);
    unregister_code16(KC_LCTL);
}

void function_reboot(void) {
    reset_keyboard();
}

LeaderSequence leader_sequences_1[] = {
    { (uint16_t[]){A_}, 1, macro_fname },
    { (uint16_t[]){V_}, 1, macro_lname },
    { (uint16_t[]){E_}, 1, macro_email },
    { (uint16_t[]){P_}, 1, macro_phone },
};

LeaderSequence leader_sequences_2[] = {
    { (uint16_t[]){P_}, 1, hotkey_vs_command },
    { (uint16_t[]){O_}, 1, hotkey_vs_open },
};

LeaderSequence leader_sequences_3[] = {
    { (uint16_t[]){R_, B_}, 2, function_reboot },
};


void leader_hash_end_user(uint16_t leader_key) {
    switch (leader_key) {
        case FT_LEADER_HASH_1:
            for (size_t i = 0; i < sizeof(leader_sequences_1) / sizeof(leader_sequences_1[0]); i++) {
                if (leader_hash_is(leader_sequences_1[i].sequence, leader_sequences_1[i].size)) {
                    leader_sequences_1[i].action();
                    return;
                }
            }
            break;
        case FT_LEADER_HASH_2:
            for (size_t i = 0; i < sizeof(leader_sequences_2) / sizeof(leader_sequences_2[0]); i++) {
                if (leader_hash_is(leader_sequences_2[i].sequence, leader_sequences_2[i].size)) {
                    leader_sequences_2[i].action();
                    return;
                }
            }
            break;
        case FT_LEADER_HASH_3:
            for (size_t i = 0; i < sizeof(leader_sequences_3) / sizeof(leader_sequences_3[0]); i++) {
                if (leader_hash_is(leader_sequences_3[i].sequence, leader_sequences_3[i].size)) {
                    leader_sequences_3[i].action();
                    return;
                }
            }
            break;
    }
}
