#include <Wire.h>

const int numberOfGates = 20;
const int debeebounce = 300;
const int outputDelay = 5000;
unsigned long lastOutput = 0;
unsigned long now = 0;
volatile bool dataRequested = false;

typedef struct
{
  char gates[numberOfGates + 1]; // need to add a slot for the NULL character

  int inPin[numberOfGates];
  int outPin[numberOfGates];

  int inCount[numberOfGates];
  int outCount[numberOfGates];

  int inReading[numberOfGates];
  int outReading[numberOfGates];

  int lastInReading[numberOfGates];
  int lastOutReading[numberOfGates];

  int lastInTime[numberOfGates];
  int lastOutTime[numberOfGates];

  int inTotal;
  int outTotal;

} 
BeeCounter;

static BeeCounter bc = {
  "abcdefghijklnortuvwx", // gate letters
  { 44,42,40,38,16,14,12,10,8 ,35,34,33,32,19,25,7 ,5 ,3 ,2 ,0   } , // inPins
  { 45,43,41,39,17,15,13,11,9 ,31,30,29,28,18,24,26,6 ,4 ,1 ,27  } // outPins
};


char* p(char *fmt, ... ){
  char tmp[128]; // resulting string limited to 128 chars
  va_list args;
  va_start (args, fmt );
  vsnprintf(tmp, 128, fmt, args);
  va_end (args);
  return tmp;
}

void requestEvent()
{
  Wire.write(p("%04i:%04i", bc.inTotal, bc.outTotal));
  resetCounts();
}

void resetCounts()
{
  bc.inTotal = 0;
  bc.outTotal = 0;
  for (int i = 0; i < numberOfGates; i++) {
    bc.inCount[i] = 0;
    bc.outCount[i] = 0;
  }
}

void arrayPrint(int array[])
{
  for (int i = 0; i < numberOfGates; i++) {
    Serial.print(array[i]);
    Serial.print(" ");
  }
  Serial.println();
}

//
// Main functions
//

void setup()
{
  Serial.begin(57600);
  Wire.begin(2);
  // Init pins
  for (int i = 0; i < numberOfGates; i++) {
    pinMode(bc.inPin[i], INPUT);
    pinMode(bc.outPin[i], INPUT);
  }
  resetCounts();
  Wire.onRequest(requestEvent); // register event
}


void loop()
{
  // Loop though the gates
  for (int i = 0; i < numberOfGates; i++) {
    now = millis();
    // Read Gates
    bc.inReading[i] = digitalRead(bc.inPin[i]);
    bc.outReading[i] = digitalRead(bc.outPin[i]);

    // Is our reading stable?
    if (now - bc.lastInTime[i] >= debeebounce && now - bc.lastOutTime[i] >= debeebounce) {

      // Is the bee going in?
      if (bc.inReading[i] != bc.lastInReading[i] && bc.inReading[i] > bc.outReading[i]) {
        bc.inCount[i]++;
        bc.inTotal++;
        bc.lastInTime[i] = now;
      }

      // Is the bee going out?
      if (bc.outReading[i] != bc.lastOutReading[i] && bc.inReading[i] < bc.outReading[i]) {
        bc.outCount[i]++;
        bc.outTotal++;
        bc.lastOutTime[i] = now;
      }
    }

    bc.lastInReading[i] = bc.inReading[i];
    bc.lastOutReading[i] = bc.outReading[i];
  }

  if (now - lastOutput >= outputDelay) {
    for (int i = 0; i < numberOfGates; i++) {
      Serial.print(bc.gates[i]);
      Serial.print(" ");
    }
    Serial.println();
    arrayPrint(bc.inCount);
    arrayPrint(bc.outCount);
    Serial.println(p("%04i:%04i", bc.inTotal, bc.outTotal));
    lastOutput = now;
  }


}

