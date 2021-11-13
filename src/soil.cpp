
#include <Arduino.h>

#include "alldefine.h"
#include "voice.h"

 int soilValue;
 int soilMoisture;

void soil(){
    soilValue = analogRead(soilPIN);
    soilMoisture = map(soilValue,0,4095,100,0);
    if(soilMoisture<15){
        digitalWrite(outputPin, HIGH);
        voice2();
    }

    if(soilMoisture>40){
        digitalWrite(outputPin, LOW);
        voice2();
    }
          
    Serial.print("soilMositure: ");
    Serial.print(soilMoisture);
    Serial.println("%");
}
