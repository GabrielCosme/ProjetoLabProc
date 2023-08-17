#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#define constrain(value, min, max) (value < min ? min : (value > max ? max : value))

#define map(value, from_min, from_max, to_min, to_max) \
    (to_min + (to_max - to_min) * (value - from_min) / (from_max - from_min))

#endif // __UTILS_HPP__
