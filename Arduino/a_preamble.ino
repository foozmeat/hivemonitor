#include <stdarg.h>

// Sensors
#include <Wire.h>
#include <DHT22.h>
#include "DS3231.h"
#include <swI2C_BMP085.h>
#include <I2cMaster.h>

#define SECONDS 1000
#define MINUTES 60000

// Digital Pins
#define alarmPin 2 // RTC Alarm

#define DHT22_PIN_1 7 // Lower
#define DHT22_PIN_2 8 // Upper
#define DHT22_PIN_3 9 // Outside

#define LED 13

// Bee Counter
#define BeeCounter_0 2

// DHT22
DHT22 DHT22_1(DHT22_PIN_1);
DHT22 DHT22_2(DHT22_PIN_2);
DHT22 DHT22_3(DHT22_PIN_3);

volatile boolean alarmFired = false;
boolean bmpPresent = true;

DS3231 RTC; //Create the DS3231 object

swI2C_BMP085 bmp;

