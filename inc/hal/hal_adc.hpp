#ifndef __HAL_ADC_HPP__
#define __HAL_ADC_HPP__

#include <array>
#include <cstdint>
#include <libopencm3/stm32/adc.h>
#include <libopencm3/stm32/rcc.h>

#include "hal/hal_gpio.hpp"

struct AdcConfig {
    GpioConfig       gpio;
    uint32_t         adc_number;
    uint32_t         mode;
    rcc_periph_clken rcc_clock;
    rcc_periph_rst   rcc_reset;
    uint32_t         prescaler;
    uint32_t         resolution;
    uint8_t*         channels;
    uint8_t          sample_time;
};

template <uint8_t number_of_channels>
class HalAdc {
    public:
        /**
         * @brief Construct a new Hal Adc object
         *
         * @param adc_config Configuration of the ADC
         */
        HalAdc(const AdcConfig& adc_config);

        /**
         * @brief Update the ADC reading
         */
        void update_reading();

        /**
         * @brief Get the reading of the ADC
         *
         * @param channel Channel of the ADC
         * @return uint32_t Reading of the ADC channel
         */
        uint32_t get_adc_reading(uint8_t channel) const;

    private:
        /**
         * @brief ADC being used
         */
        uint32_t adc_number;

        /**
         * @brief Array to store the average ADC reading of each channel
         */
        std::array<uint32_t, number_of_channels> adc_reading;
};

#include "../src/hal/hal_adc.cpp"

#endif // __HAL_ADC_HPP__
