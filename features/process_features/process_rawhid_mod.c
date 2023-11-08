#include "process_rawhid_mod.h"

bool raw_modifying = false;
uint8_t response_data[32] = {0};

void set_leds(enum led_state state, int led1, int led2, int led3);

bool process_rawhid_mod(uint16_t keycode, keyrecord_t *record) {
    // Handle FT_RAW_MOD first
    if (keycode == FT_RAW_MOD) {
        if (record->event.pressed) {
            raw_modifying = true;
        } else {
            raw_modifying = false;
        }
        return false; // Don't process FT_RAW_MOD any further
    }

    // If raw_modifying is true and the keycode is a layer toggle
    if (raw_modifying && IS_LAYER_TOGGLE(keycode)) {
        // Use QMK's timer feature to differentiate between tap and hold
        static uint16_t layer_key_timer;

        if (record->event.pressed) {
            layer_key_timer = timer_read();
            return false; // Don't process the key further here, wait to decide between tap or hold
        } else {
            if (timer_elapsed(layer_key_timer) < TAPPING_TERM) {
                // Key was tapped
                convert_keycode_to_raw_hid(keycode, true, response_data);

                uprintf("Sending Raw Data: [%02X, %02X, %02X]\n", response_data[0], response_data[1], response_data[2]);
                raw_hid_send(response_data, 32);
                return false; // Don't process this key as a regular keypress
            } else {
                // Key was held, the layer switch will be handled by QMK's default process
                return true;
            }
        }
    }

    // Process raw HID functionality for other keys
    if (raw_modifying) {
        if (record->event.pressed) {
            convert_keycode_to_raw_hid(keycode, true, response_data);
        } else {
            convert_keycode_to_raw_hid(keycode, false, response_data);
        }
        uprintf("Sending Raw Data: [%02X, %02X, %02X]\n", response_data[0], response_data[1], response_data[2]);
        raw_hid_send(response_data, 32);
        return false; // Don't process this key further
    }

    return true; // Process other keycodes normally
}

// Define constants for ping request and pong response
#define PING_REQUEST 0x01
#define PONG_RESPONSE 0x02

void raw_hid_receive(uint8_t *data, uint8_t length) {
    if (length > 0) {
        uprintf("Received Raw Data: [%02X, %02X, %02X]\n", data[0], data[1], data[2]);

        // Check if the received data is a ping request
        if (data[0] == PING_REQUEST) {
            set_leds(LED_ON, 1, 0, 0);
            // Respond with a pong
            response_data[0] = PONG_RESPONSE;
            for (int i = 1; i < 32; i++) {
                response_data[i] = 0; // Clear the rest of the response data
            }
        }

        uprintf("Sending Raw Response: [%02X, %02X, %02X]\n", response_data[0], response_data[1], response_data[2]);

        raw_hid_send(response_data, 32);

        if (data[0] == PING_REQUEST) {
            set_leds(LED_OFF, 1, 0, 0);
        }
    } else {
        uprintf("Data length less than expected.\n");
    }
}

void set_leds(enum led_state state, int led1, int led2, int led3) {
    // Control the first LED
    if (state == LED_ON && led1) {
        ergodox_right_led_1_on();
    } else {
        ergodox_right_led_1_off();
    }

    // Control the second LED
    if (state == LED_ON && led2) {
        ergodox_right_led_2_on();
    } else {
        ergodox_right_led_2_off();
    }

    // Control the third LED
    if (state == LED_ON && led3) {
        ergodox_right_led_3_on();
    } else {
        ergodox_right_led_3_off();
    }
}

