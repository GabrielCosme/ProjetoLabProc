
#include "proxy/button.hpp"

namespace proxy {
static constexpr float debounce_delay = 0.01;
static constexpr float long_press_time = 0.9;
static constexpr float extra_long_press_time = 3.0;

Button::Button(const hal::Gpio::Config& gpio_config, pull_resistor_t pull_resistor) :
    gpio(gpio_config), pull_resistor(pull_resistor) {
}

void Button::update_state() {
    bool raw_reading = this->is_pressed();

    if ((this->current_state != raw_reading) && !this->is_debouncing) {
        this->is_debouncing = true;
        this->debounce_timer.reset();
    } else if ((this->debounce_timer.get_time() < debounce_delay) && this->is_debouncing) {
        if (this->current_state == raw_reading) {
            this->is_debouncing = false;
            return;
        }
    } else {
        this->is_debouncing = false;
        this->previous_state = this->current_state;
        this->current_state = raw_reading;
    }
}

bool Button::is_rising_edge() const {
    return (this->current_state && !this->previous_state);
}

bool Button::is_falling_edge() const {
    return (!this->current_state && this->previous_state);
}

bool Button::is_pressed() const {
    return (this->gpio.read() == (bool) this->pull_resistor);
}

Button::status_t Button::get_status() {
    this->update_state();

    if (this->is_rising_edge()) {
        this->status_timer.reset();
    } else if (this->is_falling_edge()) {
        if (this->status_timer.get_time() > extra_long_press_time) {
            return Button::EXTRA_LONG_PRESS;
        } else if (this->status_timer.get_time() > long_press_time) {
            return Button::LONG_PRESS;
        } else {
            return Button::SHORT_PRESS;
        }
    }

    return Button::NO_PRESS;
}
}  // namespace proxy
