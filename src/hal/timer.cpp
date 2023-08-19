#include <libopencm3/cm3/systick.h>

#include "hal/timer.hpp"

namespace hal {
uint32_t Timer::system_ticks;

Timer::Timer() : ticks(Timer::system_ticks) {
}

void Timer::reset(void) {
    this->ticks = Timer::system_ticks;
}

float Timer::get_time(void) const {
    return (Timer::system_ticks - this->ticks) / 1000.0F;
}

void Timer::sleep(uint32_t milliseconds) {
    uint32_t start = Timer::system_ticks;

    while (Timer::system_ticks - start < milliseconds) {
        continue;
    }
}

void Timer::increment_system_ticks(void) {
    Timer::system_ticks++;
}
}  // namespace hal

extern "C" {
void sys_tick_handler(void) {
    hal::Timer::increment_system_ticks();
}
}
