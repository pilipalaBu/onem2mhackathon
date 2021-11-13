#include <Arduino.h>
#include "EEPROM.h"
#include "alldefine.h"
#include "voice.h"
double values=analogRead(witerPin);
double values2 = analogRead(witerPin);
int waterhight;
double data1;
double data2;
void witer1() {
    values2 =(long)analogRead(witerPin);
    data1 = (values2 / 4096) * 40;
    pinMode(outputPin, OUTPUT);
    Serial.println("========================");
    Serial.println(data1);
    Serial.println("初始水位：");
    Serial.println(values2);
    digitalWrite(outputPin,LOW);
}

void witer2() {
    values=(long)analogRead(witerPin);
    data2 = (values / 4096) * 40;

    Serial.println("++++++++++++++++++++++++++++++++++++++");
    Serial.println(data2);
    Serial.println("实时水位：");
    Serial.println(values);
    Serial.println(data2);
    if(data1-data2>10)  // 差值大  停止
    {
        values2=values;
        digitalWrite(outputPin,LOW);
    }
    if(data2<10)
    {
        Serial.println("水槽该加水了");
        voice();
    }
    else{
        Serial.println("水槽水充足");
    }
}