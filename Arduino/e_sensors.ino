void readDHT22(DHT22 sensor, int number)
{
  DHT22_ERROR_t errorCode;

  // DHT-22
  errorCode = sensor.readData();
  if (errorCode == DHT_ERROR_NONE) {
    addKVPair(p("DHT22T_%i",number),DallasTemperature::toFahrenheit(sensor.getTemperatureC()));
    addKVPair(p("DHT22H_%i",number),sensor.getHumidity());
  } 
  else {
    comment(p("An error occured reading from DHT22 %i: %i", number, errorCode));
  }

}

void readDS18B20()
{
  // One-Wire
  sensors.requestTemperatures(); // Send the command to get temperatures
  float Cel = sensors.getTempCByIndex(0);
  addKVPair("DS18B20", DallasTemperature::toFahrenheit(Cel));
}

void readMic(int port, int number)
{
  addKVPair(p("MIC_%i",number), analogRead(port));
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
