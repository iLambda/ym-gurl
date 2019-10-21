#ifndef __YM_GURL_INPUT_CONTROLLER
#define __YM_GURL_INPUT_CONTROLLER

#define IO_CONTROLLER_REFRESH_INPUT_RATE         1

#define IO_CONTROLLER_THREAD_PRIORITY_INPUT      osPriorityNormal
#define IO_CONTROLLER_THREAD_FLAG_BATTERY_ISR    0x01

#include <mbed.h>
#include <rtos.h>

#include "io/state.h"
#include "utils/event.h"

namespace io {

    class Controller {

        private:
            /* The input thread */
            static Thread m_threadInput;
            /* The state */
            static inputstate_t m_state;

            /* The battery change event */
            static utils::Event<batterystate_t> m_eventBatteryChange;

        private:
            Controller() {}

        public:
            /* Battery change event. The callbacks are run in input thread context */
            static const utils::Event<batterystate_t>& batteryChange();

        public:
            /* Run the controller  */
            static void run();
            /* Get the state */
            static inputstate_t get();
            
        private:
            /* Battery read interrupt */
            static void isrBattery();
            
            /* Update battery levels */
            __STATIC_FORCEINLINE void updateBattery();
            /* Update volume */
            __STATIC_FORCEINLINE void updateVolume();
            /* Update inputs */
            __STATIC_FORCEINLINE void updateInputs();

            /* The input thread */
            static void inputThread();
    };

};

#endif