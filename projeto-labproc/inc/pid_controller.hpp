#ifndef __PID_CONTROLLER_HPP__
#define __PID_CONTROLLER_HPP__

#include <hal/hal_timer.hpp>

/**
 * @brief Implementation of simple PID controller
 *        Response = Kp(error + Ki * integral(error) Kd * d/dt(error))
 */
class PidController {
    public:
        /**
         * @brief Construct a new Pid Controller object
         *
         * @param kp Proportional constant
         * @param ki Integrative constant
         * @param kd Derivative constant
         * @param setpoint Desired state
         * @param saturation Maximum response returned by the controller
         * @param max_integral Maximum integrative response
         */
        PidController(float kp, float ki, float kd, float setpoint = 0.0, float saturation = -1.0,
                      float max_integral = -1.0);

        /**
         * @brief Set the setpoint object
         *
         * @param setpoint Desired state
         */
        void set_setpoint(float setpoint);

        /**
         * @brief Set the controller parameters
         *
         * @param kp Proportional constant
         * @param ki Integrative constant
         * @param kd Derivative constant
         * @param saturation Maximum response returned by the controller
         * @param max_integral Maximum integrative response
         */
        void set_parameters(float kp, float ki, float kd, float saturation = -1.0, float max_integral = -1.0);

        /**
         * @brief Reset prev_error and error_acc objects
         */
        void reset();

        /**
         * @brief Update PID with new state and return response
         *
         * @param state Current value of the controlled variable
         *
         * @return Response
         */
        float update(float state);

        /**
         * @brief Update PID with new state and return response
         *
         * @param state Current value of the controlled variable
         * @param state_change Derivative of the controlled variable
         *
         * @return Response
         */
        float update(float state, float state_change);

    private:
        float kp;                /**< Proportional constant */
        float ki;                /**< Integrative constant */
        float kd;                /**< Derivative constant */
        float setpoint;          /**< Desired state */
        float saturation;        /**< Maximum response returned by the controller */
        float max_integral;      /**< Maximum integrative accumulative response */
        float error_acc = 0;     /**< Accumulated error for i term */
        float prev_state = 0;    /**< Previous state for d term */
        float last_response = 0; /**< Last response returned by the controller */

        HalTimer timer;  /**< Timer used to compute the loop time */
};

#endif // __PID_CONTROLLER_HPP__
