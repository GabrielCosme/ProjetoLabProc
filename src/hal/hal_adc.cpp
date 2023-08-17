#ifndef __HAL_ADC_CPP__
#define __HAL_ADC_CPP__

#include "hal/hal_adc.hpp"

template <uint8_t number_of_channels>
HalAdc<number_of_channels>::HalAdc(const AdcConfig& adc_config) : adc_number(adc_config.adc_number) {
    adc_power_off(adc_config.adc_number);

    gpio_mode_setup(adc_config.gpio.port, adc_config.gpio.mode, adc_config.gpio.pull_resistor, adc_config.gpio.pin);

    rcc_periph_clock_enable(adc_config.gpio.rcc_clock);
    rcc_periph_clock_enable(adc_config.rcc_clock);
    rcc_periph_reset_pulse(adc_config.rcc_reset);

    adc_set_multi_mode(adc_config.mode);
    adc_set_clk_prescale(adc_config.prescaler);
    adc_set_resolution(adc_config.adc_number, adc_config.resolution);
    adc_set_right_aligned(adc_config.adc_number);
    adc_enable_scan_mode(adc_config.adc_number);
    adc_set_single_conversion_mode(adc_config.adc_number);
    adc_disable_discontinuous_mode_regular(adc_config.adc_number);
    adc_eoc_after_each(adc_config.adc_number);

    adc_disable_external_trigger_regular(adc_config.adc_number);
    adc_set_regular_sequence(adc_config.adc_number, number_of_channels, adc_config.channels);
    adc_set_sample_time_on_all_channels(adc_config.adc_number, adc_config.sample_time);

    adc_power_on(adc_config.adc_number);
}

template <uint8_t number_of_channels>
void HalAdc<number_of_channels>::update_reading(void) {
    adc_start_conversion_regular(this->adc_number);

    for (uint8_t i = 0; i < number_of_channels; i++) {
        while (not adc_eoc(this->adc_number)) {
            continue;
        }

        adc_clear_flag(this->adc_number, ADC_SR_EOC);
        this->adc_reading[i] = adc_read_regular(this->adc_number);
    }
}

template <uint8_t number_of_channels>
uint32_t HalAdc<number_of_channels>::get_adc_reading(uint8_t channel) const {
    return this->adc_reading[channel];
}

#endif // __HAL_ADC_CPP__
