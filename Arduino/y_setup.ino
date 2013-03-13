void setup()  {
  Serial.begin(57600);

  wakeXBee();
  comment("Setup");
  sleepXBee();

  // Setup the XBee DTR pin
  pinMode(XBeeSleep, OUTPUT);

  pinMode(ONE_WIRE_BUS,INPUT);
  pinMode(DHT22_PIN_1, INPUT);
  pinMode(DHT22_PIN_2, INPUT);

  pinMode(MIC_1, INPUT);

  Wire.begin();
  RTC.begin();
  analogReference(INTERNAL);

  alarmSetup();
  analogRead(6);

  // Programming delay
  digitalWrite(13,HIGH);
  delay(10000);
  digitalWrite(13,LOW);

  // Start up the one-wire library
  sensors.begin();

  alarmSetup();
}


