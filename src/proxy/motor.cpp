#include <cmath>

#include "proxy/motor.hpp"
#include "utils.hpp"

namespace proxy {
static constexpr uint16_t motors_timer_counter_period = 1000;
static constexpr float max_stopped_command = 0.02;

Motor::Motor(const Config& motor_config, float deadzone) :
    forward_pwm(motor_config.forward_pwm), backward_pwm(motor_config.backward_pwm), deadzone(deadzone) {
    this->forward_pwm.set_compare(0);
    this->backward_pwm.set_compare(0);
}

void Motor::set_speed(float speed) {
    bool command_sign = std::signbit(speed);
    float command = std::abs(constrain(speed, Motor::min_command, Motor::max_command));

    if (command <= max_stopped_command * Motor::max_command) {
        command = 0;
    } else {
        command = map(command, 0, Motor::max_command,
                      this->deadzone * motors_timer_counter_period, motors_timer_counter_period);
    }

    if (command_sign) {
        this->forward_pwm.set_compare(0);
        this->backward_pwm.set_compare(command);
    } else {
        this->forward_pwm.set_compare(command);
        this->backward_pwm.set_compare(0);
    }
}
}
