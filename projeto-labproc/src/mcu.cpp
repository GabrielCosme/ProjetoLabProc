#include "mcu.hpp"

void mcu_init(const ClockConfig& clock_config) {
    rcc_clock_setup_pll(clock_config.clock_scale);

    systick_set_reload(clock_config.reload);
    systick_set_clocksource(clock_config.clocksource);
    systick_counter_enable();
    systick_interrupt_enable();
}
