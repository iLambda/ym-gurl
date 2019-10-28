#include <mbed.h>
#include <ui/display.h>
#include <ui/screens/bootscreen.h>
#include <utils/debugging.h>

/* The screens */
ui::screen::BootScreen bootScreen;


int main() {

  /* Start initialization */
  dbg::setLEDs(0x01);

  /* Initialize display */
  ui::Display::add(bootScreen.getID(), bootScreen.get());
  ui::Display::go(bootScreen.getID());
  ui::Display::run();

  /* Start initialization */
  dbg::setLEDs(0x03);

  while(1) {

  }
}