#ifndef __ADC_CPP__
#define __ADC_CPP__

#include "hal/adc.hpp"

namespace hal {
template <uint8_t number_of_channels>
Adc<number_of_channels>::Adc(const Config& adc_config) : adc_number(adc_config.adc_number) {
    adc_power_off(adc_config.adc_number);

    gpio_mode_setup(adc_config.gpio.port, adc_config.gpio.mode, adc_config.gpio.pull_resistor, adc_config.gpio.pin);

    rcc_periph_clock_enable(adc_config.gpio.rcc_clock);
    rcc_periph_clock_enable(adc_config.rcc_clock);
    rcc_periph_reset_pulse(adc_config.rcc_reset);
    rcc_periph_clock_enable(adc_config.dma.rcc_clock);

    dma_channel_select(adc_config.dma.dma_number, adc_config.dma.stream, adc_config.dma.channel);
    dma_set_priority(adc_config.dma.dma_number, adc_config.dma.stream, adc_config.dma.priority);
    dma_set_memory_size(adc_config.dma.dma_number, adc_config.dma.stream, adc_config.dma.memory_size);
    dma_set_peripheral_size(adc_config.dma.dma_number, adc_config.dma.stream, adc_config.dma.peripheral_size);
    dma_enable_memory_increment_mode(adc_config.dma.dma_number, adc_config.dma.stream);
    dma_enable_circular_mode(adc_config.dma.dma_number, adc_config.dma.stream);
    dma_set_peripheral_address(adc_config.dma.dma_number, adc_config.dma.stream, adc_config.dma.peripheral_address);
    dma_set_memory_address(adc_config.dma.dma_number, adc_config.dma.stream, (uint32_t) this->buffer);
    dma_set_number_of_data(adc_config.dma.dma_number, adc_config.dma.stream, number_of_channels);
    dma_enable_stream(adc_config.dma.dma_number, adc_config.dma.stream);

    adc_set_multi_mode(adc_config.mode);
    adc_set_clk_prescale(adc_config.prescaler);
    adc_set_resolution(adc_config.adc_number, adc_config.resolution);
    adc_set_right_aligned(adc_config.adc_number);
    adc_enable_scan_mode(adc_config.adc_number);
    adc_disable_discontinuous_mode_regular(adc_config.adc_number);
    adc_set_continuous_conversion_mode(adc_config.adc_number);
    adc_eoc_after_each(adc_config.adc_number);
    adc_disable_external_trigger_regular(adc_config.adc_number);
    adc_set_regular_sequence(adc_config.adc_number, number_of_channels, adc_config.channels);
    adc_set_sample_time_on_all_channels(adc_config.adc_number, adc_config.sample_time);
    adc_power_on(adc_config.adc_number);
    adc_start_conversion_regular(this->adc_number);
}

template <uint8_t number_of_channels>
void Adc<number_of_channels>::update_reading() {
    for (uint8_t i = 0; i < number_of_channels; i++) {
        this->adc_reading[i] = this->buffer[i];
    }
}

template <uint8_t number_of_channels>
uint32_t Adc<number_of_channels>::get_reading(uint8_t channel) const {
    return this->adc_reading[channel];
}
}  // namespace hal

#endif // __ADC_CPP__
