#ifndef __ADC_HPP__
#define __ADC_HPP__

#include <array>
#include <cstdint>
#include <libopencm3/stm32/adc.h>
#include <libopencm3/stm32/rcc.h>

#include "hal/gpio.hpp"

namespace hal {
template <uint8_t number_of_channels>
class Adc {
    public:
        struct Config {
            Gpio::Config     gpio;
            uint32_t         adc_number;
            uint32_t         mode;
            rcc_periph_clken rcc_clock;
            rcc_periph_rst   rcc_reset;
            uint32_t         prescaler;
            uint32_t         resolution;
            uint8_t*         channels;
            uint8_t          sample_time;
        };

        /**
         * @brief Construct a new Adc object
         *
         * @param adc_config Configuration of the ADC
         */
        Adc(const Config& adc_config);

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
}  // namespace hal

#include "../src/hal/adc.cpp"

#endif // __ADC_HPP__
