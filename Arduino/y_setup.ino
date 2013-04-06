void setup()  {
  Serial.begin(57600);

  comment("Setup");

  Wire.begin();
  RTC.begin();

  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  }

  // Programming delay
  digitalWrite(13,HIGH);
  delay(4000);
  digitalWrite(13,LOW);

  // Start up the one-wire library
//  sensors.begin();

  alarmSetup();
}



