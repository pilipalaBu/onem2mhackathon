#ifndef __MQTT1SUB_H__
#define __MQTT1SUB_H__
#include <Arduino.h>
#include <WiFi.h>
#include <SimpleDHT.h>
#include "alldefine.h"
#include "wi.h"
#include "tem.h"
void mqsub1();
void mqsub2();
void connectMQTTServer();
void pubMQTTmsg();
void subscribeTopic();
void receiveCallback(char* topic,byte* payload, unsigned int length);
#endif
