#ifndef __YM_GURL_UI_DISPLAY
#define __YM_GURL_UI_DISPLAY

#define UI_DISPLAY_U8G2_INIT  u8g2_Setup_st7920_s_128x64_f /* u8g2_Setup_uc1611_ea_dogxl240_f */
#define UI_DISPLAY_U8G2_COMM  u8x8_byte_4wire_sw_spi /* u8x8_byte_hw_spi_mbed */
#define UI_DISPLAY_U8G2_ROT   U8G2_R2

#define UI_DISPLAY_MAX_SCREENS      16
#define UI_DISPLAY_REFRESH_UI_RATE  10

#define UI_DISPLAY_THREAD_PRIORITY_EVENT      osPriorityNormal
#define UI_DISPLAY_THREAD_PRIORITY_UI         osPriorityNormal
#define UI_DISPLAY_THREAD_QUEUE_SIZE          16
#define UI_DISPLAY_THREAD_FLAG_UI_DIRTY       0x01
#define UI_DISPLAY_THREAD_FLAG_EVENT_DRAWN    0x01

#include <mbed.h>
#include <rtos.h>
#include <u8g2.h>

#include "ui/screens/screen.h"

namespace ui {

    class Display {

        public:
            struct screenevent_t {
                /* A pointer to the screen */
                screen_t* screen;
                /* Its ID */
                uint8_t id;
            };

        private:
            /* The UI thread */
            static Thread m_threadUi;
            /* The event thread */
            static Thread m_threadEvent;
            /* The screen queue */
            static Queue<screenevent_t, UI_DISPLAY_THREAD_QUEUE_SIZE> m_screenQueue;
            /* The message pool */
            static MemoryPool<screenevent_t, UI_DISPLAY_THREAD_QUEUE_SIZE> m_screenEventPool;
            
            /* The display data */
            static u8g2_t m_display;
            /* The registered screens */
            static screen_t m_screens[UI_DISPLAY_MAX_SCREENS];
            /* The current screen id */
            static int8_t m_currentScreen;

        private:
            /* Create a display */
            Display() {}

        public:
            /* Run the display */
            static void run();

            /* Add a new screen */
            static bool add(uint8_t id, const screen_t& screen);
            /* Get the screen */
            static bool get(uint8_t id, screen_t& screen);
            /* Go to screen */
            static bool go(uint8_t id);
            /* The current screen id */
            static int8_t current();

            /* The screen width */
            __STATIC_FORCEINLINE u8g2_uint_t screenWidth() { return Display::m_display.width; }
            /* The screen height */
            __STATIC_FORCEINLINE u8g2_uint_t screenHeight() { return Display::m_display.height; }

        private:
            /* Repaint */
            static void repaint();
            /* Dirty */
            static void dirty();
            /* Draw the frame */
            static void drawFrame();

            /* The UI thread */
            static void uiThread();
            /* The event thread */
            static void eventThread();

    };

};

/* The u8glib gpio and delay procedure */
extern "C" uint8_t u8x8_gpio_and_delay_mbed(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
/* The u8glib spi hardware procedure */
extern "C" uint8_t u8x8_byte_hw_spi_mbed(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);

#endif