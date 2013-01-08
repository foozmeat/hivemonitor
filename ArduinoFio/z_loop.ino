void loop() {
  println("### Starting Loop");
  DHT22_ERROR_t errorCode;

  aJsonObject *root,*fmt;
  root = aJson.createObject();

  // One-Wire
  sensors.requestTemperatures(); // Send the command to get temperatures
  float Cel = sensors.getTempCByIndex(0);
  aJson.addNumberToObject(root,"DS18B20", DallasTemperature::toFahrenheit(Cel));

  // DHT-22
  errorCode = myDHT22.readData();
  if (errorCode == DHT_ERROR_NONE) {
    aJson.addNumberToObject(root,"DHT22T", DallasTemperature::toFahrenheit(myDHT22.getTemperatureC()));
    aJson.addNumberToObject(root,"DHT22H", myDHT22.getHumidity());
  }

  Serial.print(aJson.print(root));

  // Sign off
  Serial.print("\n");
  println("### Ending Loop");

  delay(15 * SECONDS);
}

