#include "display.h"
#include "utils/utils.h"

ui::Display::Display(){
    
    /* Initialize screens */
    memset(this->m_screens, 0, utils::size(this->m_screens) * sizeof(screen_t));
    this->m_currentScreen = -1;

    /* Initialize u8g2 */
    UI_DISPLAY_U8G2_INIT(
        /* The display data */
        &this->m_display,
        /* The rotation procedure */
        UI_DISPLAY_U8G2_ROT,
        /* The communication mode */
        UI_DISPLAY_U8G2_COMM,
        /* The uC specific procedure */
        &Display::u8x8_gpio_and_delay_mbed);
        
    /* Initialize display */
    u8g2_InitDisplay(&this->m_display);
    /* Wake up the display */
    u8g2_SetPowerSave(&this->m_display, 0);

    /* Start the UI and event threads */
    this->m_threadUi.start(callback(this, &Display::uiThread));
    this->m_threadEvent.start(callback(this, &Display::eventThread));
}

bool ui::Display::add(uint8_t id, const screen_t &screen) {
    /* If exists, couldn't add. Return false */
    if (this->m_screens[id].render) {
        return false;
    }
    /* Add it */
    this->m_screens[id] = screen;
    /* Return */
    return true;
}

bool ui::Display::get(uint8_t id, screen_t &screen) {
    /* If not exists, couldn't get. Return false */
    if (!this->m_screens[id].render) {
        return false;
    }
    /* Return it */
    screen = this->m_screens[id];
    /* Return */
    return true;
}

bool ui::Display::go(uint8_t id) {
    /* If not exists, couldn't get. Return false */
    if (!this->m_screens[id].render) { return false; }
    /* Allocate a message */
    screenevent_t *message = this->m_screenEventPool.alloc();
    /* Check if message could be allocated */
    if (message == nullptr) { return false; }
    /* Fill it and send it */
    message->id = id;
    message->screen = &this->m_screens[id];
    this->m_screenQueue.put(message);
    /* Return */
    return true;
}

int8_t ui::Display::current() {
    /* Return the current display */
    return this->m_currentScreen;
}

void ui::Display::dirty() {
    /* Send */
    this->m_threadUi.flags_set(UI_DISPLAY_THREAD_FLAG_UI_DIRTY);
}

void ui::Display::drawFrame() {
    /* TODO */
}

void ui::Display::repaint() {
    /* Check if id fine */
    if (this->m_currentScreen < 0) { return; }
    /* Get screen */
    screen_t &screen = this->m_screens[this->m_currentScreen];
    /* Check if current screen is fine */
    if (!screen.render) { return; }
    /* Clear */
    u8g2_ClearBuffer(&this->m_display);
    /* Check if need to draw frame */
    if (screen.framed) {
        /* Draw */
        this->drawFrame();
        /* Restrict frame draw */
        /* TODO */
        // u8g2_SetClipWindow(&this->m_display, );
    }
    else {
        /* Reset frame draw restriction */
        u8g2_SetMaxClipWindow(&this->m_display);
    }
    /* Draw */
    screen.render(screen.state, &this->m_display);
    /* Send buffer */
    u8g2_SendBuffer(&this->m_display);
}

void ui::Display::uiThread() {
    /* Thread loop */
    while (1) {
        /* Wait for dirty event */
        ThisThread::flags_wait_all(UI_DISPLAY_THREAD_FLAG_UI_DIRTY);
        /* Repaint */
        repaint();
        /* Send redraw ok */
        this->m_threadEvent.flags_set(UI_DISPLAY_THREAD_FLAG_EVENT_DRAWN);
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
        if (this->m_currentScreen >= 0 && this->m_screens[this->m_currentScreen].update) {
            /* Get screen */
            screen_t &screen = this->m_screens[this->m_currentScreen];
            /* Do update */
            screen.update(screen.state, &dirty);
            /* Check dirty flag */
            if (dirty) {
                /* Set as dirty, but don't wait for drawn flag */
                this->dirty();
            }
        }
        /* Check queue */
        auto result = this->m_screenQueue.get(UI_DISPLAY_REFRESH_UI_RATE);
        /* If anything was found */
        if (result.status == osEventMessage) {
            /* Get message */
            screenevent_t *event = (screenevent_t *)result.value.p;
            /* Check if screen we want to go to is different */
            if (event->id != this->m_currentScreen) {
                /* Set current id */
                this->m_currentScreen = event->id;
                /* Free the event */
                this->m_screenEventPool.free(event);
                /* Clear flags in case */
                ThisThread::flags_clear(UI_DISPLAY_THREAD_FLAG_EVENT_DRAWN);
                /* Set as dirty */
                this->dirty();
                /* Wait for drawn flag */
                ThisThread::flags_wait_all(UI_DISPLAY_THREAD_FLAG_EVENT_DRAWN);
            }
        }
    }
}

/* The u8glib gpio and delay procedure */
uint8_t ui::Display::u8x8_gpio_and_delay_mbed(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr) {
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