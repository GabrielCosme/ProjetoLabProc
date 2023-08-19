#ifndef __UTILS_HPP__
#define __UTILS_HPP__

constexpr float constrain(float value, float min, float max) {
    return value < min ? min : (value > max ? max : value);
}

constexpr float map(float value, float from_min, float from_max, float to_min, float to_max) {
    return to_min + (to_max - to_min) * (value - from_min) / (from_max - from_min);
}

#endif // __UTILS_HPP__
