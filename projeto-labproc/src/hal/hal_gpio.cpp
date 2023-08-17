#include "hal/hal_gpio.hpp"

HalGpio::HalGpio(const GpioConfig& gpio_config) : port(gpio_config.port), pin(gpio_config.pin) {
    rcc_periph_clock_enable(gpio_config.rcc_clock);
    gpio_mode_setup(gpio_config.port, gpio_config.mode, gpio_config.pull_resistor, gpio_config.pin);

    if (gpio_config.mode == GPIO_MODE_OUTPUT) {
        gpio_set_output_options(gpio_config.port, gpio_config.otype, gpio_config.speed, gpio_config.pin);
    }
}

bool HalGpio::read() const {
    return gpio_get(this->port, this->pin);
}

void HalGpio::write(bool pin_state) {
    if (pin_state) {
        gpio_set(this->port, this->pin);
    } else {
        gpio_clear(this->port, this->pin);
    }
}

void HalGpio::toggle() {
    gpio_toggle(this->port, this->pin);
}
