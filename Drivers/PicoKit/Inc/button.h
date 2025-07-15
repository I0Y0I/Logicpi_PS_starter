/**
 * @file button.h
 * @brief Provides a driver for handling button events, including single press, double press, and long press.
 *
 * This driver uses a state machine to detect various button events with proper debouncing. It is designed
 * to be non-blocking and can be integrated into a main loop for periodic polling.
 */

#ifndef BUTTON_H
#define BUTTON_H

#include "gd32f30x.h"
#include "systick.h"

#include <stdbool.h>

// --- Public Macros ---

#define BUTTON_DEBOUNCING_MILLIS 20   ///< Debouncing time in milliseconds to prevent mechanical switch noise.
#define BUTTON_DOUBLE_PRESS_THRESHOLD 250 ///< Maximum time in milliseconds between two presses to be considered a double press.
#define BUTTON_LONG_PRESS_THRESHOLD 800   ///< Time in milliseconds a button must be held down to be considered a long press.

// --- Public Enums ---

/**
 * @brief Defines the possible button events that can be detected.
 */
typedef enum BUTTON_EVENT {
    BUTTON_EVENT_IDLE = 0,          ///< No new event has occurred.
    BUTTON_EVENT_SINGLE_PRESS,      ///< A single, short press was detected.
    BUTTON_EVENT_DOUBLE_PRESS,      ///< Two consecutive short presses were detected.
    BUTTON_EVENT_LONG_PRESS         ///< The button was held down for an extended period.
} BUTTON_EVENT;

/**
 * @brief Defines the internal states of the button state machine.
 * @note For internal use by the driver.
 */
typedef enum BUTTON_STATE {
    BUTTON_STATE_IDLE = 0,          ///< The button is not being pressed and no event is pending.
    BUTTON_STATE_WAIT_LONG,         ///< The button has been pressed, waiting to see if it's a long press.
    BUTTON_STATE_WAIT_DOUBLE,       ///< The button has been released, waiting for a potential second press.
    BUTTON_STATE_DOUBLE,            ///< A second press has occurred, confirming a double press.
    BUTTON_STATE_LONG,              ///< The button is being held down for a long press.
} BUTTON_STATE;

// --- Public Structs ---

/**
 * @brief Structure to hold the configuration and state of a single button.
 */
typedef struct button_struct {
    // --- Hardware Configuration ---
    rcu_periph_enum rcu;    ///< The RCU peripheral for the button's GPIO port.
    uint32_t gpio;          ///< The GPIO port where the button is connected.
    uint32_t pin;           ///< The GPIO pin where the button is connected.
    FlagStatus valid;       ///< The electrical level when the button is pressed (SET for high, RESET for low).

    // --- Internal State ---
    BUTTON_STATE state;     ///< The current state of the button's state machine.
    uint32_t update_time;   ///< The timestamp of the last state change, used for timing events.
} button_struct;

// --- Public Function Prototypes ---

/**
 * @brief Initializes a button instance.
 *
 * This function configures the GPIO pin for the button and initializes its internal state.
 * It should be called once for each button before its state is polled.
 *
 * @param b Pointer to the button_struct instance to initialize.
 */
void button_init(button_struct *b);

/**
 * @brief Polls the button to get the latest event.
 *
 * This function should be called periodically in the main loop to update the button's state machine
 * and detect events like single press, double press, or long press.
 *
 * @param b Pointer to the button_struct instance to poll.
 * @return The detected BUTTON_EVENT, default BUTTON_EVENT_IDLE if no new event has occurred.
 */
BUTTON_EVENT get_button_event(button_struct *b);

#endif //BUTTON_H
