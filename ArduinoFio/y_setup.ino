void setup()  {
  Serial.begin(57600);

  // Setup the XBee DTR pin
  pinMode(XBeeSleep, OUTPUT);

  // Disable XBee
  digitalWrite(XBeeSleep, 1);

  // Start up the one-wire library
  sensors.begin();
}


