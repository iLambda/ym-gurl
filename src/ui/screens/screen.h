#ifndef __YM_GURL_UI_SCREEN
#define __YM_GURL_UI_SCREEN

#include <mbed.h>
#include <u8g2.h>

namespace ui {

    /* Function that renders a screen */
    typedef void (*render_fun_t)(void*, u8g2_t*);
    /* Function that updates a screen */
    typedef void (*update_fun_t)(void*, bool*);

    /* Represents a screen */
    struct screen_t {
        /* The state */
        void* state;
        /* Draw the status bar and the frame ? */
        bool framed;
        /* The render method */
        render_fun_t render;
        /* The update method */
        update_fun_t update;
    };

};

#endif