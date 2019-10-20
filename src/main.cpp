#include <mbed.h>
#include <ui/display.h>
#include <ui/screens/bootscreen.h>
#include <utils/debugging.h>

/* The peripherals */
ui::Display* display = nullptr;
/* The screens */
ui::screen::BootScreen bootScreen;


int main() {

  /* Start initialization */
  dbg::setLEDs(0x01);

  /* Initialize display */
  display = new ui::Display();
  display->add(bootScreen.getID(), bootScreen.get());
  display->go(bootScreen.getID());

  /* Start initialization */
  dbg::setLEDs(0x03);

  while(1) {

  }
}