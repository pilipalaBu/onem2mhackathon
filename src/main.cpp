
#include <Arduino.h>
#include <WiFi.h>
#include <SimpleDHT.h>
#include <PubSubClient.h>
#include <Ticker.h>
#include <stdio.h>
#include <Wire.h>
#include "Adafruit_SGP30.h"
#include "soil.h"
#include "tem.h"
#include "alldefine.h"
#include "wi.h"
#include "mqtt1sub.h"
#include "co2.h"
#include "witer.h"
#include "illumination.h"
#include "voice.h"
#include "oled.h"
void setup() {
  Serial.begin(9600);   
  Serial.println("success");
  wi();
  witer1();
  mqsub1();
  oledstart();
  
}

void loop() {
  tem();  
  soil();  
  co0();
  suns();
  witer2();
  mqsub2(); 
  oled();
  delay(2000);
}

