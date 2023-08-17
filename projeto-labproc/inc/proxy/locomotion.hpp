#ifndef __LOCOMOTION_HPP__
#define __LOCOMOTION_HPP__

#include "proxy/motor.hpp"

class Locomotion {
    public:
        /**
         * @brief Construct a new Locomotion object
         *
         * @param left_motor_config Configuration of the left motor
         * @param right_motor_config Configuration of the right motor
         * @param left_deadzone Deadzone of the left motor
         * @param right_deadzone Deadzone of the right motor
         */
        Locomotion(const MotorConfig& left_motor_config, const MotorConfig& right_motor_config,
                   float left_deadzone = 0.0, float right_deadzone = 0.0);

        /**
         * @brief Set the speeds of the motors
         *
         * @param linear Linear speed
         * @param angular Angular speed
         */
        void set_speeds(float linear, float angular);

        /**
         * @brief Compute the linear decay of the angular error
         *
         * @param angular_error Angular error
         * @param dependency Dependency of the linear decay
         * @return Linear decay
         */
        static float linear_decay(float angular_error, float dependency);

    private:
        /**
         * @brief Left motor instance
         */
        Motor left_motor;

        /**
         * @brief Right motor instance
         */
        Motor right_motor;
};

#endif // __LOCOMOTION_HPP__
