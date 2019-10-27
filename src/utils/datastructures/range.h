#ifndef __STM32_INTERNAL_UTILS_RANGE
#define __STM32_INTERNAL_UTILS_RANGE

#include <rtos.h>
#include <mbed.h>
#include <inttypes.h>
#include <type_traits>

namespace utils {
    
    /* A range */
    template <typename T>
    struct range_t {
        /* Beginning */
        T start;
        /* End */
        T end;

        /* Verify this is an integral type */
        static_assert(std::is_integral<T>::value, "Integral type required in range_t.");
    };

    /* Make in range */
    template <typename T>
    __always_inline inline range_t<T> range_make(const T& min, const T& max) {
        return { min, max };
    }
    /* Check if in range */
    template <typename T>
    __always_inline inline bool range_in(const range_t<T>& range, const T& x) {
        return x >= range.start && x <= range.end;
    }
    /* Clamp in range */
    template <typename T>
    __always_inline inline T range_clamp(const range_t<T>& range, const T& x) {
        return x < range.start ? range.start
             : x > range.end ? range.end
             : x;
    }

}

#endif