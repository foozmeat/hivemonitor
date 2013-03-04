void loop() {
  wakeXBee();

  comment("Starting Loop");
  DHT22_ERROR_t errorCode;

  // One-Wire
  sensors.requestTemperatures(); // Send the command to get temperatures
  float Cel = sensors.getTempCByIndex(0);
  addKVPair("DS18B20", DallasTemperature::toFahrenheit(Cel));

  // DHT-22
  errorCode = myDHT22.readData();
  if (errorCode == DHT_ERROR_NONE) {
    addKVPair("DHT22T",DallasTemperature::toFahrenheit(myDHT22.getTemperatureC()));
    addKVPair("DHT22H",myDHT22.getHumidity());
  } else {
    comment("An error occured reading from DHT22");
  }

  sendOutput();

  // Sign off
  comment("Ending Loop");

//  sleepXBee();

  // Get ready to go to sleep...
  // wdt_reset();
  // Turn on the watchdog timer
  // watchdogEnable();
  // Go to sleep, watchdog timer will wake later
  // sleepNow();

  delay(1 * MINUTES);
}





