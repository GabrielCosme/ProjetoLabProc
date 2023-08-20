#ifndef __CLOCK_HPP__
#define __CLOCK_HPP__

#include <cstdint>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/cm3/systick.h>

namespace hal {
class Clock {
    public:
        struct Config {
            const struct rcc_clock_scale* clock_scale;
            uint32_t                      reload;
            uint8_t                       clocksource;
        };

        Clock() = delete;

        /**
         * @brief Configure and initializes system clock
         *
         * @param clock_config Configuration of the clock
         */
        static void init(const Config& clock_config);
};
}

#endif // __CLOCK_HPP__
