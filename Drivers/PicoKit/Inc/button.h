//
// Created by ioyoi on 25-7-7.
//

#ifndef BUTTON_H
#define BUTTON_H

#include "gd32f30x.h"
#include "systick.h"

#include <stdbool.h>

#define BUTTON_DEBOUNCING_MILLIS 20
#define BUTTON_DOUBLE_PRESS_GAP_MILLIS 250
#define BUTTON_LONG_PRESS_HOLD_MILLIS 800

enum BUTTON_EVENT {
    BUTTON_IDLE = 0,
    BUTTON_SINGLE_PRESS,
    BUTTON_DOUBLE_PRESS,
    BUTTON_LONG_PRESS
};

struct button_struct {
    // 按键基本配置
    rcu_periph_enum rcu;
    uint32_t gpio;
    uint32_t pin;
    FlagStatus valid;       // 有效电平

    FlagStatus status;      // 当前电平
    uint32_t update_time;   // 上次更新时间
    uint32_t released_time; // 释放时间
    uint32_t pressed_time;  // 按下时间
    bool wait_for_double_press; // 状态位，正在等待双击
    bool is_long_pressed;       // 状态位，状态位，当前动作为长按
    bool is_pressed;            // 状态位，当前被按下
};

void button_init(struct button_struct *b);
enum BUTTON_EVENT get_button_event(struct button_struct *b);

#endif //BUTTON_H
