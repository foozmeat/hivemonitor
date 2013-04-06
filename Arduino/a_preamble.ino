#include <stdarg.h>

// Sensors
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <DHT22.h>
#include "DS3231.h"
#include <Adafruit_BMP085.h>

#define SECONDS 1000
#define MINUTES 60000

// Digital Pins
#define alarmPin 2 // RTC Alarm
#define BrokenStalkerPin 5 // Probably can't use this one

#define ONE_WIRE_BUS 6
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

// One Wire
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

volatile boolean alarmFired = false;

DS3231 RTC; //Create the DS3231 object

Adafruit_BMP085 bmp;

String output = "{";
