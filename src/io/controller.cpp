#include "controller.h"
#include "midi/midi.h"

Thread io::Controller::m_threadInput;
io::inputstate_t io::Controller::m_state = {0};
utils::Event<io::batterystate_t> io::Controller::m_eventBatteryChange;
RawSerial* io::Controller::m_midi = new RawSerial(NC, NC, MIDI_BAUD_RATE);
io::midimode_t io::Controller::m_midimode = io::midimode_t::MIDI_OUT;

void io::Controller::run() {
    /* Set priority */
    Controller::m_threadInput.set_priority(IO_CONTROLLER_THREAD_PRIORITY_INPUT);
    Controller::m_threadMidi.set_priority(IO_CONTROLLER_THREAD_PRIORITY_MIDI);
    /* Start the UI and event threads */
    Controller::m_threadInput.start(callback(&Controller::inputThread));
}

io::inputstate_t io::Controller::get() {
    /* Return the state */
    return Controller::m_state;
}

void io::Controller::isrBattery() {
    /*
     *  CAREFUL !!! This is ISR context
     */
    /* Send flag into thread loop */
    Controller::m_threadInput.flags_set(IO_CONTROLLER_THREAD_FLAG_INPUT_BATTERY);   
}

void io::Controller::isrMidi(RawSerial* self) {
    /*
     *  CAREFUL !!! This is ISR context
     */
    /* Send data into queue */
    uint8_t* data = Controller::m_midiMail.alloc();
    *data = self->getc();
    /* Put in queue */
    m_midiMail.put(data);
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

void io::Controller::setMidiMode(midimode_t mode) {
    /* Check if the mode would be changed */
    if (Controller::m_midimode == mode) { return ;}
    /* Set the mode */
    Controller::m_midimode = mode;
    /* Check it */
    switch (Controller::m_midimode) {
        /* Midi IN mode */
        case midimode_t::MIDI_IN: {
            /* Start thread */
            Controller::m_threadMidi.start(callback(&Controller::midiThread));
            /* Hook the interrupt */
            Controller::m_midi->attach(callback(&Controller::isrMidi, &Controller::m_midi));
            break;
        }
        /* Midi OUT mode */
        case midimode_t::MIDI_OUT: {
            /* Stop interrupt */
            Controller::m_midi->attach(0);
            /* Stop thread */
            Controller::m_threadMidi.terminate();
            /* Empty the mail pool */
            while (!Controller::m_midiMail.empty()) {
                /* Get */
                auto mail = Controller::m_midiMail.get(0);
                /* If valid, */
                if (mail.status != osEventMail) { continue; }
                /* Free the memory */
                Controller::m_midiMail.free((uint8_t*)mail.value.p);
            }
            break;
        }
        /* Undefined ?? */
        default: break;
    }
}

void io::Controller::midiThread() {
    /* Some data */
    uint8_t payload[2] = {0};
    osEvent mail;
    midimsg_t midimessage;

    /* Thread loop */
    while (1) {
        /* Get the status byte  */
        mail = Controller::m_midiMail.get(osWaitForever);
        /* Get the status byte, and payload size. Free data */
        uint8_t status = *((uint8_t*)mail.value.p);
        int8_t payloadsize = midi_message_len(status) - 1;
        Controller::m_midiMail.free((uint8_t*)mail.value.p);
        /* Reset message, fill in status byte */
        midimessage = {0};
        midimessage.status.value = status;
        /* Get as many payload bytes as needed */
        for (size_t i = 0; i != payloadsize ; i++) {
            /* Read mail */
            mail = Controller::m_midiMail.get(IO_CONTROLLER_MIDI_MSG_TIMEOUT);
            /* If nothing receive, forget this whole command 
               and go back to waiting for a stat byte */
            if (mail.status != osEventMail) { goto payload_fail; }
            /* Get data and free mail */
            payload[i] = *((uint8_t*)mail.value.p);
            Controller::m_midiMail.free((uint8_t*)mail.value.p);
            /* Increment */
            i++;
        }
        /* Yeet that message */
        Controller::m_eventMidiReceive.fire(midimessage);
        /* Loop break label */
        payload_fail:;
    }
}

void io::Controller::inputThread() {
    /* The peripherals */
    InterruptIn battery(NC);
    /* Hook the interrupts */
    battery.fall(callback(&Controller::isrBattery));

    /* Thread loop */
    while(1) {
        /* Update volume */
        updateVolume();
        /* Update buttons */
        updateButtons();

        /* Check if battery flag set */
        if (ThisThread::flags_get() & IO_CONTROLLER_THREAD_FLAG_INPUT_BATTERY) {
            /* Clear flags */
            ThisThread::flags_clear(IO_CONTROLLER_THREAD_FLAG_INPUT_BATTERY);
            /* Read battery */
            Controller::updateBattery();
            /* Fire */
            Controller::m_eventBatteryChange.fire(Controller::m_state.battery);
        }
        /* Wait */
        wait_ms(IO_CONTROLLER_REFRESH_INPUT_RATE);
    }
}