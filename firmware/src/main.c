#include "../inc/config.h"
#include "../inc/xtal.h"
#include <xc.h>

void main(void) {
    /* Set oscillator @ 64MHz frequency */
    OSCFRQ = 0x08;
    
    /* Set outputs */
    TRISB = 0x00;
    PORTB = 0x00;
    
    /**/
    while (1) {
        PORTB = 0xFF;
        PORTB = 0x00;
    }
    
    return;
}
