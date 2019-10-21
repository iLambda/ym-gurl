#include "controller.h"

Thread io::Controller::m_threadInput;
io::inputstate_t io::Controller::m_state = {0};
utils::Event<io::batterystate_t> io::Controller::m_eventBatteryChange;

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

const utils::Event<io::batterystate_t>& io::Controller::batteryChange() {
    /* Return event as constant reference to forbid firing */
    return Controller::m_eventBatteryChange;
    
}

void io::Controller::isrBattery() {
    /*
     *  CAREFUL !!! This is ISR context
     */
    /* Send flag into thread loop */
    Controller::m_threadInput.flags_set(IO_CONTROLLER_THREAD_FLAG_BATTERY_ISR);   
}

void io::Controller::updateBattery() {
    /* The I2C controller for battery */
    static I2C batteryBus(NC, NC);
    /* TODO : read the battery state */
}

void io::Controller::updateVolume() {
    /* Analog input for potententiometer */
    AnalogIn vol(NC);
    /* Read volume level : 12-bit reading divided by 16.
       Should account for slight stationary variations */
    uint8_t volume = vol.read_u16() << (12 - 8);
    bool volumeChange = volume != Controller::m_state.volume;
    Controller::m_state.volume = volume;
    /* Request volume write if change */
    if (volumeChange) { 
        /* 
            This part of the routine must be 'atomic'.    
            Lock as critical the following code.
            !!! MUST BE SHORT    
        */
        CriticalSectionLock lock;
        /* TODO : write to the potentiometer */
    }
}

void io::Controller::updateButtons() {
    /* Peripherals for the shift register */
    static DigitalIn ser(NC);
    static DigitalOut clk(NC, 1);
    static DigitalOut srclk(NC, 1);
    /* 
        This routine must be 'atomic'.    
        Lock as critical the following code.
        !!! MUST BE SHORT    
    */
    CriticalSectionLock lock;
    /* TODO read shift register */
}

void io::Controller::inputThread() {
    /* The state */
    InterruptIn battery(NC);

    /* Hook the interrupts */
    battery.fall(callback(&Controller::isrBattery));
    battery.enable_irq();

    /* Thread loop */
    while(1) {
        /* Update volume */
        updateVolume();
        /* Update buttons */
        updateButtons();

        /* Check if battery flag set */
        if (ThisThread::flags_get() & IO_CONTROLLER_THREAD_FLAG_BATTERY_ISR) {
            /* Clear flags */
            ThisThread::flags_clear(IO_CONTROLLER_THREAD_FLAG_BATTERY_ISR);
            /* Read battery */
            Controller::updateBattery();
            /* Fire */
            Controller::m_eventBatteryChange.fire(Controller::m_state.battery);
        }
        /* Wait */
        wait_ms(IO_CONTROLLER_REFRESH_INPUT_RATE);
    }
}