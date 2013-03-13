void chargeStatus()
{
  //  char CH_status_print[][4]= { "off","on ","ok ","err" };
  unsigned char CH_Status=0;

  unsigned int ADC6=analogRead(6);

  if(ADC6 > 900) {
    CH_Status = 0;

    //sleeping
  } 
  else if(ADC6 > 550) { 
    CH_Status = 1;

    //charging 
  } 
  else if(ADC6 > 350) {
    CH_Status = 2;

    //done 
  } 
  else { 
    CH_Status = 3;

    //error 
  } 

//  addKVPair("CHARGEV", ADC6);
  addKVPair("CHARGE", CH_Status);
}

void BatteryVoltage()
{
  int BatteryValue = analogRead(A7);
  float voltage = BatteryValue * (1.1 / 1023)* (10+2)/2;  //Voltage devider

  //  percent = (voltage/3.7)*100.0;
  // 4.2V - 3.7V
  
  float percent = mapfloat(voltage, 3.0, 4.24516, 0.0, 100.0);

  addKVPair("BATTV", voltage);
  addKVPair("BATTP", percent);
}

