
#ifndef __LINE_SENSORS_HPP__
#define __LINE_SENSORS_HPP__

#include <array>
#include <cstdint>

#include "hal/hal_adc.hpp"

template <uint8_t number_of_sensors>
class LineSensors {
    public:
        /**
         * @brief Construct a new Line Sensors object
         *
         * @param adc_config Configuration of the ADC used to read the line sensors
         */
        LineSensors(const AdcConfig& adc_config);

        /**
         * @brief Gets the line position.
         *
         * @return Position of the line.
         */
        float get_position();

        /**
         * @brief Calibrates the line sensors for the white line
         */
        void calibrate_white();

        /**
         * @brief Calibrates the line sensors for the black background
         */
        void calibrate_black();

    private:
        /**
         * @brief ADC used to read the line sensors
         */
        HalAdc<number_of_sensors> hal_adc;

        /**
         * @brief Weight of each sensor to calculate the line position
         */
        std::array<float, number_of_sensors> sensors_weight;

        /**
         * @brief Sensors reading of the white line
         */
        std::array<uint32_t, number_of_sensors> white_readings;

        /**
         * @brief Sensors reading of the black background
         */
        std::array<uint32_t, number_of_sensors> black_readings;

        /**
         * @brief Thresholds to determine if the sensor is on the line or not
         */
        std::array<uint32_t, number_of_sensors> line_thresholds;
};

#include "../src/proxy/line_sensors.cpp"

#endif // __LINE_SENSORS_HPP__
