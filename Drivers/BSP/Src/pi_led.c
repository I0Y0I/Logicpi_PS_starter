//
// Created by ioyoi on 25-6-29.
//

#include "pi_led.h"

void pi_led_init(void) {
    rcu_periph_clock_enable(RCU_GPIOB);
    gpio_init(GPIOB, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8);
    gpio_bit_set(GPIOB, GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8);
}

void pi_led_set(enum PI_LED_STATUS status) {
    switch (status) {
        case PI_LED_OFF:
            gpio_bit_set(GPIOB, GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8);
            break;
        case PI_LED_RED:
            gpio_bit_set(GPIOB, GPIO_PIN_6|GPIO_PIN_8);
            gpio_bit_reset(GPIOB, GPIO_PIN_7);
            break;
        case PI_LED_GREEN:
            gpio_bit_set(GPIOB, GPIO_PIN_7|GPIO_PIN_8);
            gpio_bit_reset(GPIOB, GPIO_PIN_6);
            break;
        case PI_LED_BLUE:
            gpio_bit_set(GPIOB, GPIO_PIN_6|GPIO_PIN_7);
            gpio_bit_reset(GPIOB, GPIO_PIN_8);
            break;
        case PI_LED_YELLOW:
            gpio_bit_set(GPIOB, GPIO_PIN_8);
            gpio_bit_reset(GPIOB, GPIO_PIN_6|GPIO_PIN_7);
            break;
        case PI_LED_MAGENTA:
            gpio_bit_set(GPIOB, GPIO_PIN_6);
            gpio_bit_reset(GPIOB, GPIO_PIN_7|GPIO_PIN_8);
            break;
        case PI_LED_CYAN:
            gpio_bit_set(GPIOB, GPIO_PIN_7);
            gpio_bit_reset(GPIOB, GPIO_PIN_6|GPIO_PIN_8);
            break;
    }
}