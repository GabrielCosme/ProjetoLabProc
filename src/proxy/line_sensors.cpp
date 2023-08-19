#ifndef __LINE_SENSORS_CPP__
#define __LINE_SENSORS_CPP__

#include "proxy/line_sensors.hpp"

namespace proxy {
constexpr uint32_t default_white_value = 3850;
constexpr uint32_t default_black_value = 4000;

template <uint8_t number_of_sensors>
LineSensors<number_of_sensors>::LineSensors(const typename hal::Adc<number_of_sensors>::Config& adc_config) :
    adc(adc_config) {
    for (uint8_t i = 0; i < number_of_sensors; i++) {
        this->sensors_weight[i] = i - (number_of_sensors - 1) / 2.0F;
    }

    this->white_readings.fill(default_white_value);
    this->black_readings.fill(default_black_value);
    this->line_thresholds.fill((default_white_value + default_black_value) / 2);
}

template <uint8_t number_of_sensors>
float LineSensors<number_of_sensors>::get_position() {
    this->adc.update_reading();

    float position = 0;
    uint8_t active_sensors = 0;

    for (uint8_t i = 0; i < number_of_sensors; i++) {
        if (this->adc.get_adc_reading(i) < this->line_thresholds[i]) {
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
    this->adc.update_reading();

    for (uint8_t i = 0; i < number_of_sensors; i++) {
        this->white_readings[i] = this->adc.get_adc_reading(i);
        this->line_thresholds[i] = (this->white_readings[i] + this->black_readings[i]) / 2;
    }
}

template <uint8_t number_of_sensors>
void LineSensors<number_of_sensors>::calibrate_black() {
    this->adc.update_reading();

    for (uint8_t i = 0; i < number_of_sensors; i++) {
        this->black_readings[i] = this->adc.get_adc_reading(i);
        this->line_thresholds[i] = (this->white_readings[i] + this->black_readings[i]) / 2;
    }
}
}  // namespace proxy

#endif // __LINE_SENSORS_CPP__
