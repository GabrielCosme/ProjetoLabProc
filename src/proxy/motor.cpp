#include <cmath>

#include "proxy/motor.hpp"
#include "utils.hpp"

static constexpr uint16_t motors_timer_counter_period = 1000;
static constexpr float max_stopped_command = 0.02;

Motor::Motor(const MotorConfig& motor_config, float deadzone) :
    forward_pwm(motor_config.forward_pwm), backward_pwm(motor_config.backward_pwm), deadzone(deadzone) {
    forward_pwm.set_compare(0);
    backward_pwm.set_compare(0);
}

void Motor::set_speed(float speed) {
    bool command_sign = std::signbit(speed);
    float command = std::abs(constrain(speed, min_motors_speed, max_motors_speed));

    if (command <= max_stopped_command * max_motors_speed) {
        command = 0;
    } else {
        command = map(command, 0, max_motors_speed,
                      this->deadzone * motors_timer_counter_period, motors_timer_counter_period);
    }

    if (command_sign) {
        forward_pwm.set_compare(0);
        backward_pwm.set_compare(command);
    } else {
        forward_pwm.set_compare(command);
        backward_pwm.set_compare(0);
    }
}
