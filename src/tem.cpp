#include<Arduino.h>
#include <SimpleDHT.h>
#include "alldefine.h"
#include "mqtt1sub.h"

SimpleDHT11 dht11(temDHT11);
byte temt = 0;
byte hum = 0;
void tem() {

  Serial.println("=================================");
  Serial.println("Sample DHT11...");
  

  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temt, &hum, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); 
    Serial.println(err);
    delay(1000);
    return;
  }
  
  Serial.print("Sample OK: ");
  Serial.print((int)temt); Serial.print(" *C, "); 
  Serial.print((int)hum); Serial.println(" H");
}
