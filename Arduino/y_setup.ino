void setup()  {
  Serial.begin(57600);

  comment("Setup");

  // Setup the XBee DTR pin
  pinMode(XBeeSleep, OUTPUT);

  wakeXBee();

  digitalWrite(LED, 1);
  delay(4000);
  digitalWrite(LED, 0);

//  sleepXBee();

  // Start up the one-wire library
  sensors.begin();
}


