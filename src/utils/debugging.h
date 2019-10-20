#ifndef __STM32_INTERNAL_DEBUG_UTILS
#define __STM32_INTERNAL_DEBUG_UTILS

#include <mbed.h>
#include <inttypes.h>

namespace dbg {
    
    extern mbed::Serial* serial;
    extern mbed::DigitalOut* led;

    void printf(const char* format, ...);

    __attribute__((always_inline)) inline void setLED(bool state) {
        /* Set */
        dbg::led->write(!!state);
    }

    __attribute__((always_inline)) inline void setLEDs(uint8_t state) {
        /* Set */
        dbg::led->write(state & 0x01);
    }
    
}

#endif