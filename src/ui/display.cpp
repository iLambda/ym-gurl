#include "../img/bitmaps.h"
#include "display.h"
#include "utils/utils.h"

Thread ui::Display::m_threadUi;
Thread ui::Display::m_threadEvent;
Queue<ui::Display::screenevent_t, UI_DISPLAY_THREAD_QUEUE_SIZE> ui::Display::m_screenQueue;
MemoryPool<ui::Display::screenevent_t, UI_DISPLAY_THREAD_QUEUE_SIZE> ui::Display::m_screenEventPool;
u8g2_t ui::Display::m_display = {0};
ui::screen_t ui::Display::m_screens[UI_DISPLAY_MAX_SCREENS] = {0};
int8_t ui::Display::m_currentScreen = -1;

void ui::Display::run(){ 
    /* Initialize u8g2 */
    UI_DISPLAY_U8G2_INIT(
        /* The display data */
        &Display::m_display,
        /* The rotation procedure */
        UI_DISPLAY_U8G2_ROT,
        /* The communication mode */
        UI_DISPLAY_U8G2_COMM,
        /* The uC specific procedure */
        &u8x8_gpio_and_delay_mbed);
        
    /* Initialize display */
    u8g2_InitDisplay(&Display::m_display);
    /* Wake up the display */
    u8g2_SetPowerSave(&Display::m_display, 0);

    /* Start the UI and event threads */
    Display::m_threadUi.start(callback(&Display::uiThread));
    Display::m_threadEvent.start(callback(&Display::eventThread));
    /* Set priorities */
    Display::m_threadUi.set_priority(UI_DISPLAY_THREAD_PRIORITY_UI);
    Display::m_threadEvent.set_priority(UI_DISPLAY_THREAD_PRIORITY_EVENT);
}

bool ui::Display::add(uint8_t id, const screen_t &screen) {
    /* If exists, couldn't add. Return false */
    if (Display::m_screens[id].render) {
        return false;
    }
    /* Add it */
    Display::m_screens[id] = screen;
    /* Return */
    return true;
}

bool ui::Display::get(uint8_t id, screen_t &screen) {
    /* If not exists, couldn't get. Return false */
    if (!Display::m_screens[id].render) {
        return false;
    }
    /* Return it */
    screen = Display::m_screens[id];
    /* Return */
    return true;
}

bool ui::Display::go(uint8_t id) {
    /* If not exists, couldn't get. Return false */
    if (!Display::m_screens[id].render) { return false; }
    /* Allocate a message */
    screenevent_t *message = Display::m_screenEventPool.alloc();
    /* Check if message could be allocated */
    if (message == nullptr) { return false; }
    /* Fill it and send it */
    message->id = id;
    message->screen = &Display::m_screens[id];
    Display::m_screenQueue.put(message);
    /* Return */
    return true;
}

int8_t ui::Display::current() {
    /* Return the current display */
    return Display::m_currentScreen;
}

void ui::Display::dirty() {
    /* Send */
    Display::m_threadUi.flags_set(UI_DISPLAY_THREAD_FLAG_UI_DIRTY);
}

void ui::Display::drawFrame() {
    /* Draw top bar */
    u8g2_SetDrawColor(&Display::m_display, 1);
    u8g2_DrawBox(&Display::m_display, 0, 0, screenWidth(), 9);
    /* Draw battery symbol */
    u8g2_uint_t xposBattery = screenWidth() - IMG_BATTERY_WIDTH - 2;
    u8g2_SetDrawColor(&Display::m_display, 1);
    u8g2_DrawXBM(&Display::m_display, xposBattery, 2, IMG_BATTERY);
    /* Fill it */
    u8g2_uint_t batfillwidth = 4;
    u8g2_SetDrawColor(&Display::m_display, 0);
    u8g2_DrawBox(&Display::m_display, xposBattery + 1, 3, batfillwidth, 3);
    /* Draw battery percentage */
    const char* batperc = "95%";
    u8g2_SetFont(&Display::m_display, u8g2_font_tom_thumb_4x6_mr);
    u8g2_uint_t xposText = xposBattery - u8g2_GetStrWidth(&Display::m_display, batperc) - 1;
    u8g2_SetFontPosTop(&Display::m_display);
    u8g2_SetDrawColor(&Display::m_display, 0);
    u8g2_DrawStr(&Display::m_display, xposText, 1, batperc);

    /* Current position of widget icon */
    u8g2_uint_t xposAfter = xposText - 2;
    u8g2_uint_t iconMargin = 3;

    /* If charging */
    if (true) {
        /* Remove width */
        xposAfter -= (IMG_CHARGING_WIDTH + iconMargin);
        /* Draw charging */
        u8g2_SetDrawColor(&Display::m_display, 1);
        u8g2_DrawXBM(&Display::m_display, xposAfter, 0, IMG_CHARGING);
    }
    /* If headphones */
    if (true) {
        /* Remove width */
        xposAfter -= (IMG_HEADPHONES_WIDTH + iconMargin);
        /* Draw charging */
        u8g2_SetDrawColor(&Display::m_display, 1);
        u8g2_DrawXBM(&Display::m_display, xposAfter, 1, IMG_HEADPHONES);
    }


    /* Restrict */
    // u8g2_SetClipWindow(&Display::m_display, 0, 9, screenWidth(), screenHeight() - 9);
}

void ui::Display::repaint() {
    /* Check if id fine */
    if (Display::m_currentScreen < 0) { return; }
    /* Get screen */
    screen_t &screen = Display::m_screens[Display::m_currentScreen];
    /* Check if current screen is fine */
    if (!screen.render) { return; }
    /* Clear */
    u8g2_ClearBuffer(&Display::m_display);
    /* Draw */
    screen.render(screen.state, &Display::m_display);
    /* Check if need to draw frame */
    if (screen.framed) {
        /* Draw */
        Display::drawFrame();
    }
    /* Send buffer */
    u8g2_SendBuffer(&Display::m_display);
}

void ui::Display::uiThread() {
    /* Thread loop */
    while (1) {
        /* Wait for dirty event */
        ThisThread::flags_wait_all(UI_DISPLAY_THREAD_FLAG_UI_DIRTY);
        /* Repaint */
        repaint();
        /* Send redraw ok */
        Display::m_threadEvent.flags_set(UI_DISPLAY_THREAD_FLAG_EVENT_DRAWN);
    }
}

void ui::Display::eventThread()
{
    /* Dirty flag & current screen */
    bool dirty = false;
    /* Thread loop */
    while (1) {
        /* Reset dirty flag */
        dirty = false;
        /* Check if screen exists */
        if (Display::m_currentScreen >= 0 && Display::m_screens[Display::m_currentScreen].update) {
            /* Get screen */
            screen_t &screen = Display::m_screens[Display::m_currentScreen];
            /* Do update */
            screen.update(screen.state, &dirty);
            /* Check dirty flag */
            if (dirty) {
                /* Set as dirty, but don't wait for drawn flag */
                Display::dirty();
            }
        }
        /* Check queue */
        auto result = Display::m_screenQueue.get(UI_DISPLAY_REFRESH_UI_RATE);
        /* If anything was found */
        if (result.status == osEventMessage) {
            /* Get message */
            screenevent_t *event = (screenevent_t *)result.value.p;
            /* Check if screen we want to go to is different */
            if (event->id != Display::m_currentScreen) {
                /* Set current id */
                Display::m_currentScreen = event->id;
                /* Free the event */
                Display::m_screenEventPool.free(event);
                /* Clear flags in case */
                ThisThread::flags_clear(UI_DISPLAY_THREAD_FLAG_EVENT_DRAWN);
                /* Set as dirty */
                Display::dirty();
                /* Wait for drawn flag */
                ThisThread::flags_wait_all(UI_DISPLAY_THREAD_FLAG_EVENT_DRAWN);
            }
        }
    }
}

/* The u8glib spi hardware procedure */
uint8_t u8x8_byte_hw_spi_mbed(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr) {
    /* Internal data */
    static DigitalOut dc(NC);
    static SPI spi(NC, NC, NC);
    /* Temporary variables */
    uint8_t *data;
    /* Checkup on message */
    switch (msg) {
        /* Send one or more bytes, located at arg_ptr, arg_int contains the number of bytes. */
        case U8X8_MSG_BYTE_SEND:
            data = (uint8_t *)arg_ptr;
            while (arg_int > 0) {
                spi.write((uint8_t)*data);
                data++;
                arg_int--;
            }
            break;

        /* Send once during the init phase of the display */
        case U8X8_MSG_BYTE_INIT:
            /* Disable CS */
            u8x8_gpio_SetCS(u8x8, u8x8->display_info->chip_disable_level);
            /* Set good polarity (TODO : check)*/
            spi.format(8, u8x8->display_info->spi_mode);
            /* Set good frequency and begin */
            spi.frequency(/* TODO */);
            break;

        /* Set the level of the data/command pin. 
           arg_int contains the expected output level. */
        case U8X8_MSG_BYTE_SET_DC:
            /* Set the DC level */
            u8x8_gpio_SetDC(u8x8, arg_int);
            break;
        
        /* Set the chip select line here. 
           u8x8->display_info->chip_enable_level contains the expected level. 
           Use u8x8_gpio_SetCS(u8x8, u8x8->display_info->chip_enable_level) 
           to call the GPIO procedure.*/
        case U8X8_MSG_BYTE_START_TRANSFER:
            /* Raise CS and wait */
            u8x8_gpio_SetCS(u8x8, u8x8->display_info->chip_enable_level);
            u8x8->gpio_and_delay_cb(u8x8, U8X8_MSG_DELAY_NANO, u8x8->display_info->post_chip_enable_wait_ns, NULL);
            break;

        /* Unselect the device. 
           Use the CS level from here: 
           u8x8->display_info->chip_disable_level. */
        case U8X8_MSG_BYTE_END_TRANSFER:
            /* Wait */
            u8x8->gpio_and_delay_cb(u8x8, U8X8_MSG_DELAY_NANO, u8x8->display_info->pre_chip_disable_wait_ns, NULL);
            /* Unselect */
            u8x8_gpio_SetCS(u8x8, u8x8->display_info->chip_disable_level);
            break;
        default:
            return 0;
    }
    return 1;
}


/* The u8glib gpio and delay procedure */
uint8_t u8x8_gpio_and_delay_mbed(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr) {
    /* State */
    static DigitalOut m_cs(A2);
    static DigitalOut m_mosi(A1);
    static DigitalOut m_sclk(A0);
    static DigitalOut m_rst(A3);

    switch (msg)
    {
        case U8X8_MSG_GPIO_AND_DELAY_INIT: // called once during init phase of u8g2/u8x8
            break;                         // can be used to setup pins

        case U8X8_MSG_DELAY_NANO:          // delay arg_int * 1 nano second
            wait_ns(arg_int);
            break;
            
        case U8X8_MSG_DELAY_100NANO: // delay arg_int * 100 nano seconds
            wait_ns(100 * arg_int);
            break;

        case U8X8_MSG_DELAY_10MICRO: // delay arg_int * 10 micro seconds
            wait_ms(10 * arg_int);
            break;

        case U8X8_MSG_DELAY_MILLI: // delay arg_int * 1 milli second
            wait_ms(arg_int);
            break;

        case U8X8_MSG_DELAY_I2C: // arg_int is the I2C speed in 100KHz, e.g. 4 = 400 KHz
            break;               // arg_int=1: delay by 5us, arg_int = 4: delay by 1.25us
            
        case U8X8_MSG_GPIO_D0:   // D0 or SPI clock pin: Output level in arg_int
                                //case U8X8_MSG_GPIO_SPI_CLOCK:
            m_sclk.write(arg_int);
            break;

        case U8X8_MSG_GPIO_D1: // D1 or SPI data pin: Output level in arg_int
                            //case U8X8_MSG_GPIO_SPI_DATA:
            m_mosi.write(arg_int);
            break;

        case U8X8_MSG_GPIO_D2: // D2 pin: Output level in arg_int
            break;

        case U8X8_MSG_GPIO_D3: // D3 pin: Output level in arg_int
            break;

        case U8X8_MSG_GPIO_D4: // D4 pin: Output level in arg_int
            break;

        case U8X8_MSG_GPIO_D5: // D5 pin: Output level in arg_int
            break;

        case U8X8_MSG_GPIO_D6: // D6 pin: Output level in arg_int
            break;

        case U8X8_MSG_GPIO_D7: // D7 pin: Output level in arg_int
            break;

        case U8X8_MSG_GPIO_E: // E/WR pin: Output level in arg_int
            break;

        case U8X8_MSG_GPIO_CS: // CS (chip select) pin: Output level in arg_int
            m_cs.write(arg_int);
            break;

        case U8X8_MSG_GPIO_DC: // DC (data/cmd, A0, register select) pin: Output level in arg_int
            break;

        case U8X8_MSG_GPIO_RESET: // Reset pin: Output level in arg_int
            m_rst.write(arg_int);
            break;

        case U8X8_MSG_GPIO_CS1: // CS1 (chip select) pin: Output level in arg_int
            break;

        case U8X8_MSG_GPIO_CS2: // CS2 (chip select) pin: Output level in arg_int
            break;
            
        case U8X8_MSG_GPIO_I2C_CLOCK: // arg_int=0: Output low at I2C clock pin
            break;                    // arg_int=1: Input dir with pullup high for I2C clock pin

        case U8X8_MSG_GPIO_I2C_DATA:  // arg_int=0: Output low at I2C data pin
            break;                    // arg_int=1: Input dir with pullup high for I2C data pin

        case U8X8_MSG_GPIO_MENU_SELECT:
            u8x8_SetGPIOResult(u8x8, /* get menu select pin state */ 0);
            break;

        case U8X8_MSG_GPIO_MENU_NEXT:
            u8x8_SetGPIOResult(u8x8, /* get menu next pin state */ 0);
            break;

        case U8X8_MSG_GPIO_MENU_PREV:
            u8x8_SetGPIOResult(u8x8, /* get menu prev pin state */ 0);
            break;
            
        case U8X8_MSG_GPIO_MENU_HOME:
            u8x8_SetGPIOResult(u8x8, /* get menu home pin state */ 0);
            break;

        default:
            u8x8_SetGPIOResult(u8x8, 1); // default return value
            break;
    }
    return 1;
}