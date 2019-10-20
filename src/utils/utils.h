#ifndef __STM32_INTERNAL_UTILS
#define __STM32_INTERNAL_UTILS

#include <mbed.h>

namespace utils {
    
    /* Get array size */
    template <class T, size_t N>
    constexpr size_t size(const T (&array)[N]) noexcept {
        return N;
    }
}

#endif