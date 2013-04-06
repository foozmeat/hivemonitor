void loop() 
{

  if (alarmFired) {
    DateTime now = RTC.now();
    comment(p("%i:%i:%i", now.hour(), now.minute(), now.second()));

    if ((now.second() % 5)==0) {
      readDHT22(DHT22_2, "0U");
      readDHT22(DHT22_1, "0L");
      readDHT22(DHT22_3, "O");
      readBMP085_temp();
      readBMP085_pressure();
      //      readBeeCounter(BeeCounter_1);
    } 
    else {
      comment("X");
    }

    alarmFired = false;
    RTC.clearINTStatus();

  }
}








