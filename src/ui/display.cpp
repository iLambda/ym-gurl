#include "display.h"
#include "utils/utils.h"

ui::Display::Display() {

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

bool ui::Display::add(uint8_t id, const screen_t& screen) {
    /* If exists, couldn't add. Return false */
    if (this->m_screens[id].render) { return false; }
    /* Add it */
    this->m_screens[id] = screen;
    /* Return */
    return true;
}

bool ui::Display::get(uint8_t id, screen_t& screen) {
    /* If not exists, couldn't get. Return false */
    if (!this->m_screens[id].render) { return false; }
    /* Return it */
    screen = this->m_screens[id];
    /* Return */
    return true;
}

bool ui::Display::go(uint8_t id) {
    /* If not exists, couldn't get. Return false */
    if (!this->m_screens[id].render) { return false; }
    /* Allocate a message */
    screenevent_t* message = this->m_screenEventPool.alloc();
    /* Check if message could be allocated */
    if (message == nullptr) {
        return false;
    }
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

}

void ui::Display::repaint() {
    /* Check if id fine */
    if (this->m_currentScreen < 0) { return; }
    /* Get screen */
    screen_t& screen = this->m_screens[this->m_currentScreen];
    /* Check if current screen is fine */
    if (!screen.render) { return; }
    /* Clear */
    u8g2_ClearBuffer(&this->m_display);
    /* Check if need to draw frame */
    if (screen.framed) {
        /* Draw */
        this->drawFrame();
        /* Restrict frame draw */
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

void ui::Display::eventThread() {
    /* Dirty flag & current screen */
    bool dirty = false;
    /* Thread loop */
    while (1) {
        /* Reset dirty flag */
        dirty = false;
        /* Check if screen exists */
        if (this->m_currentScreen > 0 && this->m_screens[m_currentScreen].update) {
            /* Get screen */
            screen_t& screen = this->m_screens[m_currentScreen];
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
            screenevent_t* event = (screenevent_t*)result.value.p;
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