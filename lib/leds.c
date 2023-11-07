#include "leds.h"

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
