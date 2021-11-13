#include <Wire.h>
#include <Arduino.h>
// 引入驱动OLED0.96所需的库
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_SGP30.h>
 
#define SCREEN_WIDTH 128 // 设置OLED宽度,单位:像素
#define SCREEN_HEIGHT 64 // 设置OLED高度,单位:像素
 
// 自定义重置引脚,虽然教程未使用,但却是Adafruit_SSD1306库文件所必需的
#define OLED_RESET 4

extern byte temt;
extern byte hum;
extern int soilMoisture;
extern Adafruit_SGP30 sgp;
extern double data2;
extern int sunvalue2;
extern int values3;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
 void words_display();
void oledstart()
{
  // 初始化OLED并设置其IIC地址为 0x3C
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}
 
void oled()
{
  words_display();
  display.display();
}
 
void words_display()
{
  // 清除屏幕
  display.clearDisplay();
 
  // 设置字体颜色,白色可见
  display.setTextColor(WHITE);
 
  //设置字体大小
  display.setTextSize(2.0);
 
  //设置光标位置
  display.setCursor(0, 0);
  display.print("CO2:");
  display.print(sgp.eCO2);
  display.print("ppm");
  display.setCursor(0, 16);
  display.print("temp:");
  display.print(temt);
  display.print("*C");
  display.setCursor(0, 32);
  display.print("SMO:");
  display.print(soilMoisture);
  display.print("%");
  display.setCursor(0, 48);
  display.print("WL:");
  display.print(data2);
  display.print("mm");
}
