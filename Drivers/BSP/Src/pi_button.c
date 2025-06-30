//
// Created by ioyoi on 25-6-30.
//

#include "pi_button.h"

FlagStatus button_status;
uint32_t button_status_update_time;

uint32_t button_released_time = 0;
uint32_t button_pressed_time = 0;
bool wait_for_double_pressed = false;
bool is_long_pressed = false;
bool button_is_pressed = false;

void pi_button_init() {
    rcu_periph_clock_enable(RCU_GPIOA);
    gpio_init(GPIOA, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, GPIO_PIN_8);
    button_status = gpio_input_bit_get(GPIOA, GPIO_PIN_8);
    button_status_update_time = get_time_tick();
}

bool pi_button_get_status() {
    const uint32_t now_time = get_time_tick();
    if (now_time - button_status_update_time > DEBOUNCING_MILLIS) {
        if (button_status != gpio_input_bit_get(GPIOA, GPIO_PIN_8) == SET) {
            button_status = !button_status;
            button_status_update_time = now_time;
        }
    }
    return !button_status;
}

enum PI_BUTTON_EVENT pi_button_get_event() {
    enum PI_BUTTON_EVENT event = PI_BUTTON_IDLE;
    const uint32_t now_time = get_time_tick();

    if (button_is_pressed != pi_button_get_status()) {
        button_is_pressed = !button_is_pressed;
        if (button_is_pressed) {
            button_pressed_time = now_time;
        }
        else {
            button_released_time = now_time;

            if (is_long_pressed) {
                is_long_pressed = false;
            }
            else if (wait_for_double_pressed) {
                event = PI_BUTTON_DOUBLE_PRESS;
                wait_for_double_pressed = false;
            }
            else {
                wait_for_double_pressed = true;
            }
        }
    }

    if (!button_is_pressed && wait_for_double_pressed && now_time - button_released_time > DOUBLE_PRESS_GAP_MILLIS) {
        event = PI_BUTTON_SINGLE_PRESS;
        wait_for_double_pressed = false;
    }
    else if (!is_long_pressed && button_is_pressed && now_time - button_pressed_time > LONG_PRESS_HOLD_MILLIS) {
        event = PI_BUTTON_LONG_PRESS;
        is_long_pressed = true;
        wait_for_double_pressed = false;
    }

    return event;
}