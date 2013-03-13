#include <avr/sleep.h>
#include <avr/power.h>
#include <stdarg.h>

// Sensors
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <DHT22.h>
#include "DS3231.h"

#define SECONDS 1000
#define MINUTES 60000

// Pins
#define alarmPin 2 // RTC Alarm
#define XBeeSleep 4 // Connect to XBee DTR
#define ONE_WIRE_BUS 6
#define DHT22_PIN_1 7
#define DHT22_PIN_2 8
#define LED 13

#define MIC_1 0

// DHT22
DHT22 myDHT22_1(DHT22_PIN_1);
DHT22 myDHT22_2(DHT22_PIN_2);

// One Wire
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

volatile boolean alarmFired = false;

DS3231 RTC; //Create the DS3231 object

String output = "{";
