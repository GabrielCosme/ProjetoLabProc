#ifndef __MOTOR_HPP__
#define __MOTOR_HPP__

#include "hal/hal_pwm.hpp"

struct MotorConfig {
    PwmConfig forward_pwm;
    PwmConfig backward_pwm;
};

constexpr float max_motors_speed = 100.0;
constexpr float min_motors_speed = -max_motors_speed;

class Motor {
    public:
        /**
         * @brief Construct a new Motor object
         *
         * @param motor_config Configuration for each pwm of the motor
         * @param deadzone Minimum value of the pwm to start the motor
         */
        Motor(const MotorConfig& motor_config, float deadzone = 0.0);

        /**
         * @brief Set the speed object
         *
         * @param speed Speed of the motor
         */
        void set_speed(float speed);

    private:
        /**
         * @brief PWM to control the motor in forward direction
         */
        HalPwm forward_pwm;

        /**
         * @brief PWM to control the motor in backward direction
         */
        HalPwm backward_pwm;

        /**
         * @brief Minimum value of the pwm to start the motor
         */
        float deadzone;
};

#endif // __MOTOR_HPP__
