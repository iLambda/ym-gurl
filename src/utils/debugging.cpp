#include "debugging.h"

mbed::Serial* dbg::serial = new mbed::Serial(USBTX, USBRX);
mbed::DigitalOut* dbg::led = new DigitalOut(LED1, 0);

void dbg::printf(const char* format, ...) {
    /* Send to pc */
    va_list args;
    va_start(args, format);
    dbg::serial->vprintf(format, args);
    va_end(args);
}