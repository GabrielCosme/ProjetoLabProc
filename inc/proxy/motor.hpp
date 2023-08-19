#ifndef __MOTOR_HPP__
#define __MOTOR_HPP__

#include "hal/pwm.hpp"

namespace proxy {
class Motor {
    public:
        struct Config {
            hal::Pwm::Config forward_pwm;
            hal::Pwm::Config backward_pwm;
        };

        /**
         * @brief Construct a new Motor object
         *
         * @param motor_config Configuration for each pwm of the motor
         * @param deadzone Minimum value of the pwm to start the motor
         */
        Motor(const Config& motor_config, float deadzone = 0.0);

        /**
         * @brief Set the speed object
         *
         * @param speed Speed of the motor
         */
        void set_speed(float speed);

        /**
         * @brief Maximum value the motor command
         */
        static constexpr float max_command = 100.0;

        /**
         * @brief Minimum value of the motor command
         */
        static constexpr float min_command = -max_command;

    private:
        /**
         * @brief PWM to control the motor in forward direction
         */
        hal::Pwm forward_pwm;

        /**
         * @brief PWM to control the motor in backward direction
         */
        hal::Pwm backward_pwm;

        /**
         * @brief Minimum value of the pwm to start the motor
         */
        float deadzone;
};
}  // namespace proxy

#endif // __MOTOR_HPP__
