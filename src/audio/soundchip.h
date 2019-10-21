#ifndef __YM_GURL_AUDIO_SOUNDCHIP
#define __YM_GURL_AUDIO_SOUNDCHIP

#define AUDIO_BUFFER_SIZE_LOG       7
#define AUDIO_BUFFER_SIZE_MASK      127
#define AUDIO_BUFFER_SIZE           128

#define AUDIO_IRQ                   IRQn_Type::TIM7_IRQn
#define AUDIO_IRQ_CLK_ENABLE        __TIM7_CLK_ENABLE
#define AUDIO_IRQ_TIMER             TIM7
#define AUDIO_IRQ_HANDLER           void TIM7_IRQHandler


#include <mbed.h>
#include <stm32f7xx_hal_tim.h>

#include "audio/devices/ym2612.h"
#include "audio/command.h"

namespace audio {

    class Soundchip {

        private:
            /* The data bus */
            static BusOut* m_dataBus;
            /* The command bus */
            static BusInOut* m_commandBus;
            /* The clock pin */
            static DigitalOut* m_clock;

            /* The timer */
            static TIM_HandleTypeDef m_TIMhandle;
            /* The ym2612 command buffer */
            static CircularBuffer<ym2612cmd_t, AUDIO_BUFFER_SIZE> m_buffer;
            /* Are we playing ? */
            static bool m_playing;

        private:
            Soundchip() {}

        public:
            /* Run */
            static void run(ym2612_t chip);

            /* Return true iff audio engine is playing */
            static bool isPlaying() { return Soundchip::m_playing; }
            /* Play */
            static void start();
            /* Stop */
            static void stop();

        private:
            /* Attach IRQ */
            __STATIC_FORCEINLINE void attachIRQ() {
                /* Setup TIM11 */
                Soundchip::m_TIMhandle.Instance = AUDIO_IRQ_TIMER;
                Soundchip::m_TIMhandle.Init.CounterMode = TIM_COUNTERMODE_UP;
                /* (TIM_CLOCK = 80 MHz / (Prescaler + 1)) / (Period +1) */
                Soundchip::m_TIMhandle.Init.Prescaler = 7;
                Soundchip::m_TIMhandle.Init.Period = 0;

                /* Enter critical section */
                {
                    /* Lock */
                    CriticalSectionLock lock;
                    /* Enable TIM11 clock */
                    AUDIO_IRQ_CLK_ENABLE();
                    /* Init timer */
                    HAL_TIM_Base_Init(&Soundchip::m_TIMhandle);     // Init timer
                    /* Start interrupts */
                    HAL_TIM_Base_Start_IT(&Soundchip::m_TIMhandle); // start timer interrupts
                    /* Set priority (Highest) */
                    HAL_NVIC_SetPriority(AUDIO_IRQ, 0, 0);
                    /* Enable IRQ */
                    HAL_NVIC_EnableIRQ(AUDIO_IRQ);
                }
            }
            /* Detach IRQ */
            __STATIC_FORCEINLINE void detachIRQ() {
                /* Disable IRQ */
                HAL_NVIC_DisableIRQ(AUDIO_IRQ);
            }

            /* Next */
            __STATIC_FORCEINLINE void next(ym2612cmd_t& out) {
                /* Pop and return only if buffer was full enough */
                Soundchip::m_buffer.pop(out);
            }

    };

};

/* The IRQ handler */
extern "C" AUDIO_IRQ_HANDLER();

#endif