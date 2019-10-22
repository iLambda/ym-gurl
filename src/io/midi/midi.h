#ifndef __YM_GURL_INPUT_MIDI_MIDI
#define __YM_GURL_INPUT_MIDI_MIDI

#define MIDI_BAUD_RATE      31250

#include <mbed.h>
#include <rtos.h>

namespace io {

    enum midimode_t {
        MIDI_IN,
        MIDI_OUT
    };

    enum midimsgtype_t {
        MIDI_TYPE_CC = 0xB0, 
        MIDI_TYPE_NOTEON = 0x90, 
        MIDI_TYPE_NOTEOFF = 0x80, 
        MIDI_TYPE_AFTERTOUCH = 0xA0, 
        MIDI_TYPE_PITCHBEND = 0xE0, 
        MIDI_TYPE_PROGCHANGE = 0xC0, 
        MIDI_TYPE_CHANPRESSURE = 0xD0, 
        MIDI_TYPE_CLOCK = 0xF8, 
        MIDI_TYPE_TICK = 0xF9, 
        MIDI_TYPE_START = 0xFA, 
        MIDI_TYPE_CONTINUE = 0xFB, 
        MIDI_TYPE_STOP = 0xFC, 
        MIDI_TYPE_ACTIVESENSE = 0xFE, 
        MIDI_TYPE_RESET = 0xFF, 
        MIDI_TYPE_TC_QUARTERFRAME = 0xF1, 
        MIDI_TYPE_SONGPOSITION = 0xF2, 
        MIDI_TYPE_SONGSELECT = 0xF3, 
        MIDI_TYPE_TUNEREQUEST = 0xF6
    };

    struct midimsg_t {
        /* The status byte */
        union {
            /* The value of the status byte */
            uint8_t value;
            /* The command and the channel */
            struct {
                uint8_t command : 4;
                uint8_t channel : 4;
            };
            /* The command and the channel */
            struct {
                uint8_t realtime : 4;
                uint8_t command : 4;
            };

        } status;
        /* The data */
        union {
            /* Value of the data as a 16-bit integer */
            uint16_t value;
            /* The two data bytes */
            struct {
                uint8_t byte1;
                uint8_t byte2;
            };
        } data;
    };

    /* Return midi message length */
    int8_t midi_message_len(uint8_t status) {
        /* Check */
        switch(status & 0xF0){
            /* 3 byte long messages */
            case MIDI_TYPE_CC:
            case MIDI_TYPE_NOTEON:
            case MIDI_TYPE_NOTEOFF:
            case MIDI_TYPE_AFTERTOUCH:
            case MIDI_TYPE_PITCHBEND:
                return 3;

            /* 2 byte long messages */
            case MIDI_TYPE_PROGCHANGE:
            case MIDI_TYPE_CHANPRESSURE:
            case MIDI_TYPE_SONGSELECT:
                return 2;

            /* Handle the midi realtime case */
            case 0xF0:
                switch(status) {
                    /* One byte midi messages */
                    case MIDI_TYPE_CLOCK:
                    case MIDI_TYPE_TICK:
                    case MIDI_TYPE_START:
                    case MIDI_TYPE_CONTINUE:
                    case MIDI_TYPE_STOP:
                    case MIDI_TYPE_ACTIVESENSE:
                    case MIDI_TYPE_RESET:
                    case MIDI_TYPE_TUNEREQUEST:
                        return 1;
                    /* Three byte midi message */
                    case MIDI_TYPE_SONGPOSITION:
                        return 3;
                    /* Two bytes midi message */
                    case MIDI_TYPE_TC_QUARTERFRAME:
                    case MIDI_TYPE_SONGSELECT:
                        return 2;
                    /* Undefined case */
                    default:
                        return -1;
                }

            /* Undefined case */
            default:
                return -1;
        }
    }
    /* Return midi message length */
    int8_t midi_message_len(midimsg_t msg) {
        return midi_message_len(msg.status.value);
    }
    /* Return midi message length */
    midimsgtype_t midi_message_type(midimsg_t msg) {
        return msg.status.value & 0xF0 != 0xF0 
                /* Usual command */
                ? (midimsgtype_t)(msg.status.value & 0xF0)
                /* Realtime command */
                : (midimsgtype_t)(msg.status.value);
    }
};

#endif