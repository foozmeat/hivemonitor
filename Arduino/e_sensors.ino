void readDHT22(DHT22 sensor, char* code)
{
  delay(100);
  DHT22_ERROR_t errorCode;
  errorCode = sensor.readData();

  switch(errorCode)
  {
  case DHT_ERROR_NONE:
    addKVPair(p("%s_T",code),celToFar(sensor.getTemperatureC()));
    addKVPair(p("%s_H",code),sensor.getHumidity());
    break;
  case DHT_ERROR_CHECKSUM:
    comment(p("An error occured reading from DHT22 %s: Checksum", code));
    break;
  case DHT_BUS_HUNG:
    comment(p("An error occured reading from DHT22 %s: Bus Hung", code));
    break;
  case DHT_ERROR_NOT_PRESENT:
    comment(p("An error occured reading from DHT22 %s: Not Present", code));
    break;
  case DHT_ERROR_ACK_TOO_LONG:
    comment(p("An error occured reading from DHT22 %s: ACK time out", code));
  case DHT_ERROR_SYNC_TIMEOUT:
    comment(p("An error occured reading from DHT22 %s: Sync Timeout", code));
    break;
  case DHT_ERROR_DATA_TIMEOUT:
    comment(p("An error occured reading from DHT22 %s: Data Timeout", code));
    break;
  case DHT_ERROR_TOOQUICK:
    comment(p("An error occured reading from DHT22 %s: Polled to quick", code));
    break;
  }
}

//void readDS18B20()
//{
//  // One-Wire
//  sensors.requestTemperatures(); // Send the command to get temperatures
//  float Cel = sensors.getTempCByIndex(0);
//  addKVPair("DS18B20", DallasTemperature::toFahrenheit(Cel));
//}

void readBMP085() 
{
  delay(100);
  float Cel = bmp.readTemperature();
  addKVPair("O_T2", celToFar(Cel));
  addKVPair("O_P",paToMB(bmp.readPressure()));

}

void readBeeCounter(int number)
{
  Wire.requestFrom(number, 9);

  int totalIn = 0;
  int totalOut = 0;
  char inChar[5];
  char outChar[5];
  char colon;

  if (Wire.available()) {

    inChar[0] = Wire.read();
    inChar[1] = Wire.read();
    inChar[2] = Wire.read();
    inChar[3] = Wire.read();
    inChar[4] = 0x0;

    colon = Wire.read();

    outChar[0] = Wire.read();
    outChar[1] = Wire.read();
    outChar[2] = Wire.read();
    outChar[3] = Wire.read();
    outChar[4] = 0x0;

    totalIn = atol(inChar);
    totalOut = atol(outChar);

  }

  addKVPair(p("BC_%i_IN",number), totalIn);
  addKVPair(p("BC_%i_OUT",number), totalOut);

}


