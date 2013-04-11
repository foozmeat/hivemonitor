void loop() 
{

  if (alarmFired) {
    DateTime now = RTC.now();
    comment("Alarm");

    if ((now.minute() % 5)==0) {
      readDHT22(DHT22_2, "0U");
      readDHT22(DHT22_1, "0L");
      readDHT22(DHT22_3, "O");
      readBMP085();
      readBeeCounter(BeeCounter_0);
      comment("End of Sensor readings");
    } 

    alarmFired = false;
    RTC.clearINTStatus();

  }
}









