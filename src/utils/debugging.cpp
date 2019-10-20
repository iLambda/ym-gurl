#include "debugging.h"

mbed::Serial* dbg::serial = new mbed::Serial(USBTX, USBRX);
mbed::BusOut* dbg::leds = new BusOut(LED1, LED2, LED3);

void dbg::printf(const char* format, ...) {
    /* Send to pc */
    va_list args;
    va_start(args, format);
    dbg::serial->vprintf(format, args);
    va_end(args);
}