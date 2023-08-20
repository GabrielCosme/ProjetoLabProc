#ifndef __BUTTON_HPP__
#define __BUTTON_HPP__

#include "hal/gpio.hpp"
#include "hal/timer.hpp"

namespace proxy {
class Button {
    public:
        /**
         * @brief Button status type
         */
        enum status_t {
            NO_PRESS,
            SHORT_PRESS,
            LONG_PRESS,
            EXTRA_LONG_PRESS,
        };

        /**
         * @brief Type of pull resistor configuration
         */
        enum pull_resistor_t {
            PULL_UP,
            PULL_DOWN,
        };

        /**
         * @brief Construct a new Button object
         *
         * @param pio_config Configuration of the button GPIO port
         * @param pull_resistor Type of pull resistor configuration
         */
        Button(const hal::Gpio::Config& gpio_config, pull_resistor_t pull_resistor);

        /**
         * @brief Provides the status of the chosen button.
         *
         * @return Status of the button.
         */
        status_t get_status();

    private:
        /**
         * @brief GPIO where the button is read from
         */
        const hal::Gpio gpio;

        /**
         * @brief Pull resistor configuration
         */
        pull_resistor_t pull_resistor;

        /**
         * @brief Timer to check if button is debouncing
         */
        hal::Timer debounce_timer;

        /**
         * @brief Timer to determine type of button press
         */
        hal::Timer status_timer;

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
}  // namespace proxy

#endif // __BUTTON_HPP__
