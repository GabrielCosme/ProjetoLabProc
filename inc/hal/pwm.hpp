#ifndef __PWM_HPP__
#define __PWM_HPP__

#include <cstdint>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/stm32/rcc.h>

#include "hal/gpio.hpp"

namespace hal {
class Pwm {
    public:
        struct Config {
            Gpio::Config     gpio;
            uint32_t         timer;
            tim_oc_id        oc_id;
            rcc_periph_clken rcc_clock;
            uint32_t         period;
            uint32_t         clock_div;
            uint32_t         prescaler;
            tim_oc_mode      oc_mode;
        };

        /**
         * @brief Construct a new Pwm object
         *
         * @param pwm_config Configuration for the pwm instance
         */
        Pwm(const Config& pwm_config);

        /**
         * @brief Set the PWM duty cycle
         *
         * @param compare Value to set the duty cycle
         */
        void set_compare(uint32_t compare);

    private:
        /**
         * @brief Timer where the PWM is generated
         */
        uint32_t timer;

        /**
         * @brief Channel of the PWM timer
         */
        tim_oc_id channel;
};
}  // namespace hal

#endif // __PWM_HPP__
