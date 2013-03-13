#define sleep_bod_disable() \
{ \
  uint8_t tempreg; \
  __asm__ __volatile__("in %[tempreg], %[mcucr]" "\n\t" \
                       "ori %[tempreg], %[bods_bodse]" "\n\t" \
                       "out %[mcucr], %[tempreg]" "\n\t" \
                       "andi %[tempreg], %[not_bodse]" "\n\t" \
                       "out %[mcucr], %[tempreg]" \
                       : [tempreg] "=&d" (tempreg) \
                       : [mcucr] "I" _SFR_IO_ADDR(MCUCR), \
                         [bods_bodse] "i" (_BV(BODS) | _BV(BODSE)), \
                         [not_bodse] "i" (~_BV(BODSE))); \
}

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
      
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // Sleep mode is set here
   
  sleep_enable();                      // Enables the sleep bit in the mcucr register
                                       // so sleep is possible. just a safety pin 
  attachInterrupt(0, Alarm, FALLING);
  cli(); 
  sleep_bod_disable(); // Disable brown out detection during sleep. Saves more power
  sei();
      

  power_all_disable(); //This shuts down ADC, TWI, SPI, Timers and USART
  sleep_cpu();         // Sleep the CPU as per the mode set earlier(power down)  

  sleep_disable();                     // First thing after waking from sleep:
                                       // disable sleep...

  power_all_enable();  //This enables ADC, TWI, SPI, Timers and USART
  // Give the DHT sensors 2 seconds to start up
  delay(2000);
}

void alarmSetup()
{
  
  pinMode(alarmPin, INPUT);
  digitalWrite(alarmPin, HIGH);
  RTC.enableInterrupts(EveryMinute); //interrupt at  EverySecond, EveryMinute, EveryHour
  attachInterrupt(0, Alarm, FALLING);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);

}

void Alarm()
{
  sleep_disable();
  detachInterrupt(0);
  alarmFired = true;
}

void wakeXBee() {
  // Enable XBee
  digitalWrite(XBeeSleep, LOW);
  // Wait for XBee Wakeup
  delay(100);
}

void sleepXBee() {
  delay(15); //This delay is required to allow print to complete
  // Disable XBee
  digitalWrite(XBeeSleep, HIGH);
}

