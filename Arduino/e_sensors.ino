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

