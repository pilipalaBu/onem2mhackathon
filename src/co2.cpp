#include <Wire.h>
#include <Arduino.h>
#include "Adafruit_SGP30.h"

Adafruit_SGP30 sgp;
void co0() {

  if (! sgp.begin()){
     Serial.println("Sensor not found :(");
    while (1);
  }
  Serial.print("Found SGP30 serial #");
  Serial.print(sgp.serialnumber[0], HEX);
  Serial.print(sgp.serialnumber[1], HEX);
  Serial.println(sgp.serialnumber[2], HEX);
  if (! sgp.IAQmeasure()) {
    Serial.println("Measurement failed");
    return;
  }
  Serial.print("eCO2 ");
  Serial.print(sgp.eCO2); Serial.println(" ppm"); //10000ppm = 1%
  }
// }