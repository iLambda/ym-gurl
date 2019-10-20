#include "bootscreen.h"

const uint8_t ui::screen::BootScreen::SCREEN_ID = 0;

ui::screen::BootScreen::BootScreen() {
    x = 0;
}

void ui::screen::BootScreen::render(void* state, u8g2_t* display) {
    /* Get self */
    BootScreen* self = (BootScreen*)state;
    /* Set font */
    u8g2_DrawCircle(display, 64, 32, self->x, U8G2_DRAW_ALL);
}

void ui::screen::BootScreen::update(void* state, bool* dirty) {
    /* Get self */
    BootScreen* self = (BootScreen*)state;

    self->x = (self->x + 1) % 32;
    *dirty = true;
}