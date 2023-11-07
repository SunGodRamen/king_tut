// leds.h
#ifndef LEDS_H
#define LEDS_H

enum led_state {
    LED_OFF,
    LED_ON
};

void set_leds(enum led_state state, int led1, int led2, int led3);

#endif // LEDS_H