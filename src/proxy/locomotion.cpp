#include <cmath>

#include "proxy/locomotion.hpp"

Locomotion::Locomotion(const MotorConfig& left_motor_config, const MotorConfig& right_motor_config, float left_deadzone,
                       float right_deadzone) :
    left_motor(left_motor_config, left_deadzone), right_motor(right_motor_config, right_deadzone) {
}

void Locomotion::set_speeds(float linear, float angular) {
    float left_command = linear + angular;
    float right_command = linear - angular;

    if (std::abs(left_command) > max_motors_speed) {
        left_command *= max_motors_speed / std::abs(left_command);
        right_command *= max_motors_speed / std::abs(left_command);
    }

    if (std::abs(right_command) > max_motors_speed) {
        left_command *= max_motors_speed / std::abs(right_command);
        right_command *= max_motors_speed / std::abs(right_command);
    }

    this->left_motor.set_speed(left_command);
    this->right_motor.set_speed(right_command);
}

float Locomotion::linear_decay(float angular_error, float dependency) {
    return dependency / (dependency + angular_error * angular_error);
}
