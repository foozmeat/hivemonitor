// Sleep
#include <avr/wdt.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

#define LED 13

// JSON
#include <aJSON.h>

// Sensors
#include <OneWire.h>
#include <DallasTemperature.h>
#include <DHT22.h>

#define SECONDS 1000

// Connect to XBee DTR
#define XBeeSleep 2

// Number of 8 second cycles before waking
// up XBee and sending data (8*8 = 64 seconds)
#define WAITPERIOD 8

// DHT22
#define DHT22_PIN 7
DHT22 myDHT22(DHT22_PIN);

// One Wire
#define ONE_WIRE_BUS 4

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

aJsonObject *root;

