#ifndef __YM_GURL_INPUT_STATE
#define __YM_GURL_INPUT_STATE

#include <mbed.h>

namespace io {

    /* The button state */
    union buttonstate_t {
        /* The flags register */
        uint8_t value;
        /* The buttons as a packed 1-bit wide struct */
        struct {
            /* The UDLR buttons */
            uint8_t up : 1;
            uint8_t down : 1;
            uint8_t left : 1;
            uint8_t right : 1;
            /* The START/SELECT buttons */
            uint8_t start : 1;
            uint8_t select : 1;
            /* The A/B buttons */
            uint8_t a : 1;
            uint8_t b : 1;
        };
    };

    /* The battery state */
    struct batterystate_t {
        /* The percentage */
        uint8_t percentage;
        /* Is the battery charging ? */
        bool charging;
    };

    /* The input state */    
    struct inputstate_t {
        /* The buttons */
        buttonstate_t buttons;
        /* The battery state */
        batterystate_t battery;
        /* The volume potentiometer input */
        uint8_t volume;
    };
}

#endif