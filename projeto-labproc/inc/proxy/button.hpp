#ifndef __BUTTON_HPP__
#define __BUTTON_HPP__

#include "hal/hal_gpio.hpp"
#include "hal/hal_timer.hpp"

/**
 * @brief Button status type
 */
enum button_status_t {
    BUTTON_NO_PRESS,
    BUTTON_SHORT_PRESS,
    BUTTON_LONG_PRESS,
    BUTTON_EXTRA_LONG_PRESS,
};

/**
 * @brief Type of pull resistor configuration
 */
enum button_pull_resistor_t {
    BUTTON_PULL_UP,
    BUTTON_PULL_DOWN,
};

class Button {
    public:
        /**
         * @brief Construct a new Button object
         *
         * @param pio_config Configuration of the button GPIO port
         * @param pull_resistor Type of pull resistor configuration
         */
        Button(const GpioConfig& gpio_config, button_pull_resistor_t pull_resistor);

        /**
         * @brief Provides the status of the chosen button.
         *
         * @return Status of the button.
         */
        button_status_t get_status();

    private:
        /**
         * @brief GPIO where the button is read from
         */
        const HalGpio hal_gpio;

        /**
         * @brief Pull resistor configuration
         */
        button_pull_resistor_t pull_resistor;

        /**
         * @brief Timer to check if button is debouncing
         */
        HalTimer debounce_timer;

        /**
         * @brief Timer to determine type of button press
         */
        HalTimer status_timer;

        /**
         * @brief Flag to know when button is debouncing
         */
        bool is_debouncing = false;

        /**
         * @brief Flag to know if button was being pressed
         */
        bool previous_state = false;

        /**
         * @brief Flag to know if button is being pressed
         */
        bool current_state = false;

        /**
         * @brief Reads the button state
         *
         * @return True if button is pressed
         */
        bool is_pressed() const;

        /**
         * @brief Updates the state of the button
         */
        void update_state();

        /**
         * @brief Checks if the button was just pressed
         *
         * @return True if the button was just pressed, false otherwise
         */
        bool is_rising_edge() const;

        /**
         * @brief Checks if the button was just released
         *
         * @return True if the button was just released, false otherwise
         */
        bool is_falling_edge() const;
};

#endif // __BUTTON_HPP__
