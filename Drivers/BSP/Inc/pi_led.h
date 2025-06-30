//
// Created by ioyoi on 25-6-29.
//

#ifndef PI_LED_H
#define PI_LED_H

#include "gd32f30x.h"

enum PI_LED_STATUS {
    PI_LED_OFF = 0,
    PI_LED_RED,
    PI_LED_GREEN,
    PI_LED_BLUE,
    PI_LED_YELLOW,
    PI_LED_MAGENTA,
    PI_LED_CYAN,
};

void pi_led_init(void);
void pi_led_set(enum PI_LED_STATUS status);

#endif //PI_LED_H
