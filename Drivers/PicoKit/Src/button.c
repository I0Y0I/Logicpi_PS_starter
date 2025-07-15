/**
 * @file button.c
 * @brief Implements the button driver with support for single, double, and long press events.
 */

#include "button.h"

// --- Private Function Prototypes ---

/**
 * @brief Checks if the button is currently being pressed.
 *
 * This function reads the button's GPIO pin and compares it to the configured
 * active level (`valid` field in the button_struct).
 *
 * @param b Pointer to the button_struct instance.
 * @return `true` if the button is pressed, `false` otherwise.
 */
static bool is_pressed(const button_struct *b);

// --- Public Function Implementations ---

/**
 * @brief Initializes a button instance.
 */
void button_init(button_struct *b) {
    // Enable the clock for the GPIO peripheral.
    rcu_periph_clock_enable(b->rcu);
    // Configure the GPIO pin as a floating input.
    gpio_init(b->gpio, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, b->pin);
    // Initialize the button state.
    b->state = BUTTON_STATE_IDLE;
    b->update_time = get_time_tick();
}

/**
 * @brief Polls the button to get the latest event.
 */
BUTTON_EVENT get_button_event(button_struct *b) {
    const uint32_t now_time = get_time_tick();
    BUTTON_EVENT event = BUTTON_EVENT_IDLE;

    // --- Debouncing ---
    // Ignore rapid changes to prevent noise from being detected as a press.
    if (now_time - b->update_time <= BUTTON_DEBOUNCING_MILLIS) {
        return event;
    }

    // --- State Machine ---
    switch (b->state) {
        case BUTTON_STATE_IDLE:
            // If the button is pressed, transition to the wait-for-long-press state.
            if (is_pressed(b)) {
                b->state = BUTTON_STATE_WAIT_LONG;
                b->update_time = now_time;
            }
            break;

        case BUTTON_STATE_WAIT_LONG:
            if (!is_pressed(b)) {
                // Button was released before the long-press threshold.
                // Transition to wait-for-double-press state.
                b->state = BUTTON_STATE_WAIT_DOUBLE;
                b->update_time = now_time;
            } else if (now_time - b->update_time > BUTTON_LONG_PRESS_THRESHOLD) {
                // Button has been held long enough for a long press.
                b->state = BUTTON_STATE_LONG;
                event = BUTTON_EVENT_LONG_PRESS;
            }
            break;

        case BUTTON_STATE_WAIT_DOUBLE:
            if (is_pressed(b)) {
                // A second press was detected within the double-press threshold.
                b->state = BUTTON_STATE_DOUBLE;
                b->update_time = now_time;
                event = BUTTON_EVENT_DOUBLE_PRESS;
            } else if (now_time - b->update_time > BUTTON_DOUBLE_PRESS_THRESHOLD) {
                // No second press was detected in time, so it's a single press.
                b->state = BUTTON_STATE_IDLE;
                event = BUTTON_EVENT_SINGLE_PRESS;
            }
            break;

        case BUTTON_STATE_LONG:
        case BUTTON_STATE_DOUBLE:
            // For both long and double press states, wait for the button to be released.
            if (!is_pressed(b)) {
                b->state = BUTTON_STATE_IDLE;
                b->update_time = now_time;
            }
            break;

        default:
            // If the state is somehow invalid, reset to idle to be safe.
            b->state = BUTTON_STATE_IDLE;
            b->update_time = now_time;
            break;
    }

    return event;
}

// --- Private Function Implementations ---

/**
 * @brief Checks if the button is currently being pressed.
 */
static bool is_pressed(const button_struct *b) {
    return gpio_input_bit_get(b->gpio, b->pin) == b->valid;
}