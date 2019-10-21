#include "controller.h"

Thread io::Controller::m_threadInput;
io::inputstate_t io::Controller::m_state = {0};

void io::Controller::run() {
    /* Set priority */
    Controller::m_threadInput.set_priority(IO_CONTROLLER_THREAD_PRIORITY_INPUT);
    /* Start the UI and event threads */
    Controller::m_threadInput.start(callback(&Controller::inputThread));
}

io::inputstate_t io::Controller::get() {
    /* Return the state */
    return Controller::m_state;
}

void io::Controller::onBatteryChange(Callback<void(batterystate_t)> callback) {
    /* Save */
    Controller::m_onBatteryChange = callback;
    
}

void io::Controller::isrBattery() {
    /*
     *  CAREFUL !!! This is ISR context
     */
    /* Send flag into thread loop */
    Controller::m_threadInput.flags_set(IO_CONTROLLER_THREAD_FLAG_BATTERY_ISR);   
}

void io::Controller::read() {
    /* Peripherals for the shift register */
    static DigitalIn ser(NC);
    static DigitalOut clk(NC, 1);
    static DigitalOut srclk(NC, 1);
    /* Analog input for potententiometer */
    AnalogIn vol(NC);

    /* Read volume level : 12-bit reading divided by 16.
       Should account for slight stationary variations */
    Controller::m_state.volume = vol.read_u16() << (12 - 8);
    /* Read shift register */
    /* TODO */
}

void io::Controller::readBattery() {
    /* TODO */
}

void io::Controller::inputThread() {
    /* The state */
    InterruptIn battery(NC);

    /* Hook the interrupts */
    battery.fall(callback(&Controller::isrBattery));
    battery.enable_irq();

    /* Thread loop */
    while(1) {
        /* Read all */
        read();
        /* Check if battery flag set */
        if (ThisThread::flags_get() & IO_CONTROLLER_THREAD_FLAG_BATTERY_ISR) {
            /* Clear flags */
            ThisThread::flags_clear(IO_CONTROLLER_THREAD_FLAG_BATTERY_ISR);
            /* Read battery */
            Controller::readBattery();
            /* If callback */
            if (Controller::m_onBatteryChange) {
                Controller::m_onBatteryChange(Controller::m_state.battery);
            }
        }
        /* Wait */
        wait_ms(IO_CONTROLLER_REFRESH_INPUT_RATE);
    }
}