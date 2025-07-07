//
// Created by ioyoi on 25-6-30.
//

#include "pi_button.h"

struct button_struct pi_button;

void pi_button_init() {
    pi_button.rcu = RCU_GPIOA;
    pi_button.gpio = GPIOA;
    pi_button.pin = GPIO_PIN_8;
    pi_button.valid = RESET;
    button_init(&pi_button);
}

enum BUTTON_EVENT pi_button_get_event() {
    return get_button_event(&pi_button);
}