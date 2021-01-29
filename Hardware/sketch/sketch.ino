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

bool standby = true;
bool check = false;
bool alarm_on = false;
bool ring = false;


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
  int bp = digitalRead(button);
  if(bp) {
    delay(200);
    if(bp) {
      if(standby) {
        standby = false;
        check = true; 
      }
      else if(check) {
        check = false;
        alarm_on = true;
        Serial.println("start");
      }
      else if(alarm_on) {
        alarm_on = false;
        ring = false;
        standby = true;
        Serial.println("stop");
      }
      u8x8.clear();
    }
  }
  if(standby) {
    uint8_t tiles[8] = { 1, 3, 7, 15, 31, 63, 127, 255};
    uint8_t tiles2[8] = { 255, 127, 63, 31, 15, 7, 3, 1};
    u8x8.drawTile(5, 1, 1, tiles);
    u8x8.drawTile(4, 2, 1, tiles);
    u8x8.drawTile(8, 1, 1, tiles2);
    u8x8.drawTile(9, 2, 1, tiles2);
    u8x8.setFont(u8x8_font_amstrad_cpc_extended_r);
    u8x8.draw2x2String(2, 5, "DORMIR");  
  }
  else if(check) {
    u8x8.clear();
    u8x8.setFont(u8x8_font_amstrad_cpc_extended_r);
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
    delay(5000);
    u8x8.clear();
    u8x8.setFont(u8x8_font_amstrad_cpc_extended_r);
    u8x8.setCursor(0, 0);
    u8x8.print("Ambient");
    u8x8.setCursor(0, 2);
    u8x8.print("conditions for");
    u8x8.setCursor(0, 4);
    u8x8.print("sleep detected:)");
    u8x8.setCursor(0, 6);
    u8x8.print("Good Night!");
    delay(5000);
  }
  else if (alarm_on) {
    u8x8.setFont(u8x8_font_amstrad_cpc_extended_r);
    u8x8.draw2x2String(3, 1, "ALARM"); 
    u8x8.draw2x2String(6, 5, "ON");
    if(msg.compareTo("ring")==0) {
      ring = true;
    }
    if(ring) {
      tone(buzz, 300);
      delay(1000);
      noTone(buzz);
    }
  }
  u8x8.refreshDisplay();  
  delay(200);
}
