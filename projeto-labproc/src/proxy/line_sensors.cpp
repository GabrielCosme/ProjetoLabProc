#ifndef __LINE_SENSORS_CPP__
#define __LINE_SENSORS_CPP__

#include "proxy/line_sensors.hpp"

constexpr uint32_t default_white_value = 3850;
constexpr uint32_t default_black_value = 4000;

template <uint8_t number_of_sensors>
LineSensors<number_of_sensors>::LineSensors(const AdcConfig& adc_config) :
    hal_adc(adc_config) {
    for (uint8_t i = 0; i < number_of_sensors; i++) {
        sensors_weight[i] = i - (number_of_sensors - 1) / 2.0F;
    }

    white_readings.fill(default_white_value);
    black_readings.fill(default_black_value);
    line_thresholds.fill((default_white_value + default_black_value) / 2);
}

template <uint8_t number_of_sensors>
float LineSensors<number_of_sensors>::get_position() {
    hal_adc.update_reading();

    float position = 0;
    uint8_t active_sensors = 0;

    for (uint8_t i = 0; i < number_of_sensors; i++) {
        if (this->hal_adc.get_adc_reading(i) < line_thresholds[i]) {
            position += this->sensors_weight[i];
            active_sensors++;
        }
    }

    if (active_sensors > 0) {
        position /= active_sensors;
    }

    return position;
}

template <uint8_t number_of_sensors>
void LineSensors<number_of_sensors>::calibrate_white() {
    hal_adc.update_reading();

    for (uint8_t i = 0; i < number_of_sensors; i++) {
        white_readings[i] = hal_adc.get_adc_reading(i);
        line_thresholds[i] = (white_readings[i] + black_readings[i]) / 2;
    }
}

template <uint8_t number_of_sensors>
void LineSensors<number_of_sensors>::calibrate_black() {
    hal_adc.update_reading();

    for (uint8_t i = 0; i < number_of_sensors; i++) {
        black_readings[i] = hal_adc.get_adc_reading(i);
        line_thresholds[i] = (white_readings[i] + black_readings[i]) / 2;
    }
}

#endif // __LINE_SENSORS_CPP__
