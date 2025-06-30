//
// Created by ioyoi on 25-6-30.
//

#ifndef PI_BUTTON_H
#define PI_BUTTON_H

#include "gd32f30x.h"
#include "systick.h"

#include <stdbool.h>

#define DEBOUNCING_MILLIS 20
#define DOUBLE_PRESS_GAP_MILLIS 250
#define LONG_PRESS_HOLD_MILLIS 800

enum PI_BUTTON_EVENT {
    PI_BUTTON_IDLE = 0,
    PI_BUTTON_SINGLE_PRESS,
    PI_BUTTON_DOUBLE_PRESS,
    PI_BUTTON_LONG_PRESS
};

void pi_button_init(void);
bool pi_button_get_status(void);
enum PI_BUTTON_EVENT pi_button_get_event(void);

#endif //PI_BUTTON_H
