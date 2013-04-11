void alarmSetup()
{
  pinMode(alarmPin, INPUT);
  digitalWrite(alarmPin, HIGH);
  RTC.enableInterrupts(EveryMinute); //interrupt at  EverySecond, EveryMinute, EveryHour
  attachInterrupt(0, Alarm, FALLING);
}

void Alarm()
{
  alarmFired = true;
}
