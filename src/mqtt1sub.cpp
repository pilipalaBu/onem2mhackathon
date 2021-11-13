 
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <Ticker.h>
#include <SimpleDHT.h>
#include <stdio.h>
#include <Wire.h>
#include <Adafruit_SGP30.h>
#include "alldefine.h"
#include "wi.h"
#include "soil.h"
#include "tem.h"
#include "co2.h"
#include "voice.h"
#include "witer.h"


Ticker ticker;
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
void subscribeTopic();
void tickerCount();
void connectMQTTServer();
void pubMQTTmsg();
void receiveCallback(char *topic, byte *payload, unsigned int length);
extern byte temt;
extern byte hum;
extern int soilMoisture;
extern Adafruit_SGP30 sgp;
extern int values;
extern int sunvalue2;
extern double data2;
int rqi=0;
void mqsub1()
{
 
 
  mqttClient.setServer(MqttServer, MqttServerPort);
  // 连接MQTT服务器
  connectMQTTServer();
  mqttClient.loop();
}

void mqsub2()
{
  Serial.println("----------------");


    pubMQTTmsg();
    mqttClient.setCallback(receiveCallback); //给过参数
    mqttClient.loop();


}



void connectMQTTServer()
{
  // 根据ESP8266的MAC地址生成客户端ID（避免与其它ESP8266的客户端ID重名）

  String clientId = "esp32-" + WiFi.macAddress(); //ClientId:esp8266-84:CC:A8:A9:35:65

  // 连接MQTT服务器
  if (mqttClient.connect(clientId.c_str()))
  {
    Serial.println("MQTT Server Connected.");
    Serial.println("Server Address: ");
    Serial.println(MqttServer);
    Serial.println("ClientId:");
    Serial.println(clientId);
    subscribeTopic(); // 建立订阅主题。
  }
  else
  {
    Serial.print("MQTT Server Connect Failed. Client State:");
    Serial.println(mqttClient.state());
    delay(3000);
  }
}

// 发布信息
void pubMQTTmsg()
{
  String topicString = "/oneM2M/req/S/Mobius2/json";    //主题: Pub-84:CC:A8:A9:35:65
  char publishTopic[topicString.length() + 1];
  strcpy(publishTopic, topicString.c_str());

char messageString[1024];
  sprintf(messageString,"{\"m2m:rqp\":{\"fr\":\"S\",\"to\":\"Mobius/ae_test/cnt_test02\",\"op\":1,\"rqi\":%d,\"pc\":{\"m2m:cin\":{\"cnf\":\"message\",\"con\":\"{\\\"temp\\\":%d,\\\"hum\\\":%d,\\\"soil\\\":%d,\\\"CO2\\\":%d,\\\"water\\\":%.1lf,\\\"light\\\":%d}\"}}, \"ty\":4}}",rqi,temt,hum,soilMoisture,sgp.eCO2,data2,sunvalue2);   //
  rqi++;
  // 实现ESP8266向主题发布信息
  if (mqttClient.publish(publishTopic, messageString)) //publishMsg
  {
    Serial.println("Publish Topic:");
    Serial.println(publishTopic);
    Serial.println("Publish message:");
    Serial.println(messageString); //publishMsg
  }
  else
  {
    Serial.println("Message Publish Failed.");
  }
}

void subscribeTopic()
{
  // 建立订阅主题。
  
  String topicString = "oneM2M/browser"; 
  char subTopic[topicString.length() + 1];
  strcpy(subTopic, topicString.c_str());

  // 通过串口监视器输出是否成功订阅主题以及订阅的主题名称
  if (mqttClient.subscribe(subTopic))
  {
    Serial.println("Subscrib Topic:");
    Serial.println(subTopic);
  }
  else
  {
    Serial.print("Subscribe Fail...");
  }
}

void receiveCallback(char *topic, byte *payload, unsigned int length)
{

  Serial.print("Message Received [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println("");
  Serial.print("Message Length(Bytes) ");
  Serial.println(length);

  if ((char)payload[0] == '1')
  {                                // 如果收到的信息以“1”为开始
    digitalWrite(outputPin, HIGH); // 打开水泵
    Serial.println("打开水泵");
    voice2();
  }
  else
  {
    digitalWrite(outputPin, LOW); // 关闭水泵
    Serial.println("关闭水泵");
  }
}