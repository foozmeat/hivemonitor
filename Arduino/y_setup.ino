void setup()  {
  Serial.begin(57600);

  comment("Setup");

  Wire.begin();
  RTC.begin();
  bmp.begin();

  // Programming delay
  digitalWrite(13,HIGH);
  delay(4000);
  digitalWrite(13,LOW);

  // Start up the one-wire library
//  sensors.begin();

  alarmSetup();
}



