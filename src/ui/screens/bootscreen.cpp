#include "bootscreen.h"

const uint8_t ui::screen::BootScreen::SCREEN_ID = 0;

ui::screen::BootScreen::BootScreen() {
    x = 0;
}

void ui::screen::BootScreen::render(void* state, u8g2_t* display) {
    /* Get self */
    BootScreen* self = (BootScreen*)state;
    /* Set font */
    u8g2_DrawLine(display, 0, 0, 30, self->x);
}

void ui::screen::BootScreen::update(void* state, bool* dirty) {
    /* Get self */
    BootScreen* self = (BootScreen*)state;

    self->x = (self->x + 1) % 64;
    *dirty = true;
}