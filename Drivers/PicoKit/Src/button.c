#include "button.h"

void button_init(struct button_struct *b) {
    rcu_periph_clock_enable(b->rcu);
    gpio_init(b->gpio, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, b->pin);
    b->status = gpio_input_bit_get(b->gpio, b->pin);
    b->update_time = get_time_tick();
}

enum BUTTON_EVENT get_button_event(struct button_struct *b) {
    const uint32_t now_time = get_time_tick();
    enum BUTTON_EVENT event = BUTTON_IDLE;

    // 消抖，状态改变后等待一段时间再检测下一次改变。
    if (now_time - b->update_time > BUTTON_DEBOUNCING_MILLIS) {
        if (b->status != gpio_input_bit_get(b->gpio, b->pin)) {
            b->status = !b->status;
            b->update_time = now_time;
        }
    }

    // 当按键状态发生改变时，更新按键状态并记录改变发生的时间。
    if (b->is_pressed != (b->status == b->valid)) {
        b->is_pressed = !b->is_pressed;
        if (b->is_pressed) {
            b->pressed_time = now_time;
        }
        else {
            b->released_time = now_time;

            // 释放按键时，如果为长按，则已经触发过了按键事件，只需要清空标志位。
            if (b->is_long_pressed) {
                b->is_long_pressed = false;
            }
            // 如果前面已记录一次按下，触发双击事件，并清空标志位，长按优先于双击。
            else if (b->wait_for_double_press) {
                event = BUTTON_DOUBLE_PRESS;
                b->wait_for_double_press = false;
            }
            // 如果是首次按下，记录这次按下，等待双击，不进行事件触发。
            else {
                b->wait_for_double_press = true;
            }
        }
    }

    // 如果上次按键按下后等待一段时间仍未检测到双击，触发单击事件，清空标志位。
    if (!b->is_pressed && b->wait_for_double_press && now_time - b->released_time > BUTTON_DOUBLE_PRESS_GAP_MILLIS) {
        event = BUTTON_SINGLE_PRESS;
        b->wait_for_double_press = false;
    }

    // 已按下了足够长的时间，触发长按事件。
    if (!b->is_long_pressed && b->is_pressed && now_time - b->pressed_time > BUTTON_LONG_PRESS_HOLD_MILLIS) {
        event = BUTTON_LONG_PRESS;
        b->is_long_pressed = true;
    }

    return event;
}