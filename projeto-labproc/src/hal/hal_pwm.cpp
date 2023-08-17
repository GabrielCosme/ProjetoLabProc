#include "hal/hal_pwm.hpp"

HalPwm::HalPwm(const PwmConfig& pwm_config) : timer(pwm_config.timer), channel(pwm_config.oc_id) {
    gpio_mode_setup(pwm_config.gpio.port, pwm_config.gpio.mode, pwm_config.gpio.pull_resistor, pwm_config.gpio.pin);
    gpio_set_af(pwm_config.gpio.port, pwm_config.gpio.alt_func_num, pwm_config.gpio.pin);
    gpio_set_output_options(pwm_config.gpio.port, pwm_config.gpio.otype, pwm_config.gpio.speed, pwm_config.gpio.pin);

    rcc_periph_clock_enable(pwm_config.gpio.rcc_clock);
    rcc_periph_clock_enable(pwm_config.rcc_clock);

    timer_set_prescaler(pwm_config.timer, pwm_config.prescaler);
    timer_set_period(pwm_config.timer, pwm_config.period);
    timer_set_clock_division(pwm_config.timer, pwm_config.clock_div);

    timer_set_oc_mode(pwm_config.timer, pwm_config.oc_id, pwm_config.oc_mode);
    timer_enable_oc_output(pwm_config.timer, pwm_config.oc_id);
    timer_set_oc_fast_mode(pwm_config.timer, pwm_config.oc_id);
    timer_set_oc_polarity_high(pwm_config.timer, pwm_config.oc_id);

    timer_continuous_mode(pwm_config.timer);
    timer_enable_counter(pwm_config.timer);
}

void HalPwm::set_compare(uint32_t compare) {
    timer_set_oc_value(this->timer, this->channel, compare);
}
