void loop() 
{

  if (alarmFired) {
    DateTime now = RTC.now();

    if ((now.minute() % 5)==0) {
      wakeXBee();
      chargeStatus();
      BatteryVoltage();
      readDHT22(myDHT22_1, 1);
      readDHT22(myDHT22_2, 2);
      readDS18B20();
      readMic(MIC_1, 1);
      sendOutput();
      sleepXBee();
    }
    
    alarmFired = false;
    RTC.clearINTStatus();
    
  }

  sleepNow();

}





