#ifndef __YM_GURL_INPUT_CONTROLLER
#define __YM_GURL_INPUT_CONTROLLER

#define IO_CONTROLLER_REFRESH_INPUT_RATE         1

#define IO_CONTROLLER_MIDI_MSG_TIMEOUT           500
#define IO_CONTROLLER_MIDI_QUEUE_SIZE            256

#define IO_CONTROLLER_THREAD_PRIORITY_MIDI       osPriorityNormal
#define IO_CONTROLLER_THREAD_PRIORITY_INPUT      osPriorityNormal
#define IO_CONTROLLER_THREAD_FLAG_INPUT_BATTERY  0x01
#define IO_CONTROLLER_THREAD_FLAG_MIDI_RECEIVED  0x01

#include <mbed.h>
#include <rtos.h>

#include "io/midi/midi.h"
#include "io/state.h"
#include "utils/event.h"

namespace io {

    class Controller {

        private:
            /* The input thread */
            static Thread m_threadInput;
            /* The MIDI thread */
            static Thread m_threadMidi;
            /* The state */
            static inputstate_t m_state;

            /* The midi queue */
            static Mail<uint8_t, IO_CONTROLLER_MIDI_QUEUE_SIZE> m_midiMail;

            /* The battery change event */
            static utils::Event<batterystate_t> m_eventBatteryChange;
            /* The midi received event */
            static utils::Event<midimsg_t> m_eventMidiReceive;

        private:
            Controller() {}

        public:
            /* Battery change event. The callbacks are run in input thread context */
            static const utils::Event<batterystate_t>& batteryChange() { return m_eventBatteryChange; }
            /* Midi receive event. The callbacks are run in midi thread context */
            static const utils::Event<midimsg_t>& midiReceive() { return m_eventMidiReceive; }

        public:
            /* Run the controller  */
            static void run();
            /* Get the state */
            static inputstate_t get();
            
        private:
            /* Battery read interrupt */
            static void isrBattery();
            /* Midi in interrupt */
            static void isrMidi(RawSerial* self);
            
            /* Update battery levels */
            __STATIC_FORCEINLINE void updateBattery();
            /* Update volume */
            __STATIC_FORCEINLINE void updateVolume();
            /* Update buttons */
            __STATIC_FORCEINLINE void updateButtons();

            /* The input thread */
            static void inputThread();
            /* The MIDI thread */
            static void midiThread();
    };

};

#endif