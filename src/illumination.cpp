
#include <Arduino.h>
#include "alldefine.h"
int sunvalue;
int sunvalue2;
void suns() {   
  Serial.print("SUN Reading: ");  
  sunvalue = analogRead(sunPin);
  sunvalue2 = map(sunvalue,0,4095,100,0);
  Serial.println(sunvalue2); 
}