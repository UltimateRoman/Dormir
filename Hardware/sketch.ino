#include <Arduino.h>
#include <U8x8lib.h>
#include "DHT.h"

#define DHTPIN 3
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
 
 U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);

char buzz = 5;
char button = 6;
char light = A6;
char sound = A2;


void setup(void) {
  Serial.begin(9600);
  u8x8.setBusClock(100000);
  u8x8.begin();
  u8x8.setFlipMode(1);
  dht.begin();
  pinMode(button, INPUT);
  pinMode(light, INPUT);
  pinMode(sound, INPUT);
  pinMode(buzz, OUTPUT);
}
 
void loop(void) { 
  String msg = Serial.readString();
  float temp = dht.readTemperature();
  int li = analogRead(light);
  int so = analogRead(sound);
  int b = digitalRead(button);
  if(b) {
    tone(buzz, 300);
    delay(1000);
    noTone(buzz);
  }
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.setCursor(0, 0);
  u8x8.print("Room Light:");
  u8x8.print(li);
  u8x8.setCursor(0, 2);
  u8x8.print("Room Temp:");
  u8x8.print(temp);
  u8x8.print("C");
  u8x8.setCursor(0, 4);
  u8x8.print("Noise:");
  u8x8.print(so);
  u8x8.setCursor(0, 6);
  u8x8.print(b);
  u8x8.refreshDisplay();
  delay(200);
}
