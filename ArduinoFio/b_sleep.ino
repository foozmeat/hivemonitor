void sleepNow()
{
  /* Now is the time to set the sleep mode. In the Atmega8 datasheet
   * http://www.atmel.com/dyn/resources/prod_documents/doc2486.pdf on page 35
   * there is a list of sleep modes which explains which clocks and 
   * wake up sources are available in which sleep modus.
   *
   * In the avr/sleep.h file, the call names of these sleep modus are to be found:
   *
   * The 5 different modes are:
   *     SLEEP_MODE_IDLE         -the least power savings 
   *     SLEEP_MODE_ADC
   *     SLEEP_MODE_PWR_SAVE
   *     SLEEP_MODE_STANDBY
   *     SLEEP_MODE_PWR_DOWN     -the most power savings
   *
   *  the power reduction management <avr/power.h>  is described in 
   *  http://www.nongnu.org/avr-libc/user-manual/group__avr__power.html
   */
      
  set_sleep_mode(SLEEP_MODE_PWR_SAVE); // Sleep mode is set here
   
  sleep_enable();                      // Enables the sleep bit in the mcucr register
                                       // so sleep is possible. just a safety pin 
  sleep_mode();                        // Here the device is actually put to sleep!!
                                       // THE PROGRAM CONTINUES FROM HERE AFTER WAKING UP
  sleep_disable();                     // First thing after waking from sleep:
                                       // disable sleep...
}

ISR (WDT_vect) {                       // WDT Wakeup
  cli();
  wdt_disable();
  sei();
}

void watchdogEnable() {                // Turn on watchdog timer; interrupt mode every 8.0s
  cli();
  MCUSR = 0;
  WDTCSR |= B00011000;
  //WDTCSR = B01000111;                // 2 Second Timeout
  //WDTCSR = B01100000;                // 4 Second Timeout
  WDTCSR = B01100001;                  // 8 Second Timeout
  sei();
}
