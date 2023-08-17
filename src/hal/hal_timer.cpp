#include <libopencm3/cm3/systick.h>

#include "hal/hal_timer.hpp"

uint32_t HalTimer::system_ticks;

HalTimer::HalTimer() {
    this->ticks = HalTimer::system_ticks;
}

void HalTimer::reset(void) {
    this->ticks = HalTimer::system_ticks;
}

float HalTimer::get_time(void) const {
    return (HalTimer::system_ticks - this->ticks) / 1000.0F;
}

void HalTimer::sleep(uint32_t milliseconds) {
    uint32_t start = HalTimer::system_ticks;

    while (HalTimer::system_ticks - start < milliseconds) {
        continue;
    }
}

void HalTimer::increment_system_ticks(void) {
    HalTimer::system_ticks++;
}

extern "C" {
void sys_tick_handler(void) {
    HalTimer::increment_system_ticks();
}
}
