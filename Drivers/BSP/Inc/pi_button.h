//
// Created by ioyoi on 25-6-30.
//

#ifndef PI_BUTTON_H
#define PI_BUTTON_H

#include "gd32f30x.h"
#include "systick.h"
#include "button.h"

#include <stdbool.h>

#define BUTTON_DEBOUNCING_MILLIS 20
#define BUTTON_DOUBLE_PRESS_GAP_MILLIS 250
#define BUTTON_LONG_PRESS_HOLD_MILLIS 800

void pi_button_init(void);
BUTTON_EVENT pi_button_get_event(void);

#endif //PI_BUTTON_H
