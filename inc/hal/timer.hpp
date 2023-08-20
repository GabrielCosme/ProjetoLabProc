#ifndef __TIMER_HPP__
#define __TIMER_HPP__

#include <cstdint>

namespace hal {
class Timer {
    public:
        /**
         * @brief Construct a new Timer object
         */
        Timer();

        /**
         * @brief Reset the timer
         */
        void reset();

        /**
         * @brief Get elapsed time since last reset
         *
         * @return Elapsed time in seconds
         */
        float get_time() const;

        /**
         * @brief Sleep for a given amount of time
         *
         * @param milliseconds Time to sleep in milliseconds
         */
        static void sleep(uint32_t milliseconds);

        /**
         * @brief Increment the system ticks
         */
        static void increment_system_ticks();

    private:
        /**
         * @brief Ticks since last timer reset
         */
        uint32_t ticks;

        /**
         * @brief Ticks since system start
         */
        static uint32_t system_ticks;
};
}  // namespace hal

#endif // __TIMER_HPP__
