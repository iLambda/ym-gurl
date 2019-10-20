#ifndef __YM_GURL_AUDIO_YM2612CMD
#define __YM_GURL_AUDIO_YM2612CMD

#include <mbed.h>

#include "ym2612reg.h"

namespace audio {

    /* A structure representing a ym2612 command */
    struct ym2612cmd_t {
        uint8_t address;
        uint8_t part;
        uint8_t data;
    };

    /* A structure representing a ym2612 pin map */
    struct ym2612pinmap_t {
        PinName dataBus[8];
        PinName commandBus[5];
        PinName clockPin;
    };

};

#endif