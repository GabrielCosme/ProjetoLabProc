#ifndef __GPIO_HPP__
#define __GPIO_HPP__

#include <cstdint>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>

namespace hal {
class Gpio {
    public:
        struct Config {
            uint32_t         port;
            uint16_t         pin;
            uint8_t          mode;
            uint8_t          pull_resistor;
            rcc_periph_clken rcc_clock;
            uint8_t          otype;
            uint8_t          speed;
            uint8_t          alt_func_num;
        };

        /**
         * @brief Construct a new GPIO object
         *
         * @param gpio_config Configuration of the gpio instance
         */
        Gpio(const Config& gpio_config);

        /**
         * @brief Read the GPIO pin
         *
         * @return True if the pin is high, false otherwise
         */
        bool read() const;

        /**
         * @brief Write to the GPIO pin
         *
         * @param pin_state State of the GPIO pin
         */
        void write(bool pin_state);

        /**
         * @brief Toggle the GPIO pin
         */
        void toggle();

    private:
        /**
         * @brief Number of the GPIO port
         */
        uint32_t port;

        /**
         * @brief Number of the GPIO pin
         */
        uint16_t pin;
};
}  // namespace hal

#endif // __GPIO_HPP__
