#ifndef __MCU_HPP__
#define __MCU_HPP__

#include <cstdint>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/cm3/systick.h>

struct ClockConfig {
    const struct rcc_clock_scale* clock_scale;
    uint32_t                      reload;
    uint8_t                       clocksource;
};

/**
 * @brief Initializes MCU and some peripherals.
 *
 * @param clock_config Configuration of the clock
 */
void mcu_init(const ClockConfig& clock_config);

#endif // __MCU_HPP__
