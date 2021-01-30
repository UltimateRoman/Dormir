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
bool woke_up = false;


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
        woke_up = true;
        Serial.println("stop");
      }
      else if(woke_up) {
        woke_up = false;
        standby = true;
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
    u8x8.setCursor(0, 3);
    u8x8.print("Room Temp:");
    u8x8.print(temp);
    u8x8.print("C");
    u8x8.setCursor(0, 6);
    u8x8.print("Noise:");
    u8x8.print(so);
    delay(3000);
    u8x8.clear();
    if(temp>25.00) {
      u8x8.setFont(u8x8_font_amstrad_cpc_extended_r);
      u8x8.setCursor(0, 0);
      u8x8.print("High room Temp");
      u8x8.setCursor(0, 2);
      u8x8.print("Consider taking");
      u8x8.setCursor(0, 4);
      u8x8.print("a bath  :)");
      u8x8.setCursor(0, 6);
      u8x8.print("Good Night!");
    }
    else {
      u8x8.setFont(u8x8_font_amstrad_cpc_extended_r);
      u8x8.setCursor(0, 0);
      u8x8.print("Ambient");
      u8x8.setCursor(0, 2);
      u8x8.print("conditions for");
      u8x8.setCursor(0, 4);
      u8x8.print("sleep detected:)");
      u8x8.setCursor(0, 6);
      u8x8.print("Good Night!");
    }
    delay(3000);
  }
  
  else if (alarm_on) {
    if(!ring) {
      u8x8.setFont(u8x8_font_amstrad_cpc_extended_r);
      u8x8.draw2x2String(3, 1, "ALARM"); 
      u8x8.draw2x2String(4, 5, "MODE");
    }
    else {
      u8x8.clear();
      uint8_t tiles3[8] = { 255, 255, 255, 255, 255, 255, 255, 255};
      u8x8.setFont(u8x8_font_amstrad_cpc_extended_r);
      u8x8.draw1x2String(4, 1, "RISE AND"); 
      u8x8.draw1x2String(5, 4, "SHINE!");
      u8x8.drawTile(8, 7, 1, tiles3);
    }
    if(msg.compareTo("ring\n")==0) {
      ring = true;
    }
    if(ring) {
      tone(buzz, 300);
      delay(1000);
      noTone(buzz);
    }
  }
  
  else if(woke_up) {
    u8x8.clear();
    u8x8.setFont(u8x8_font_amstrad_cpc_extended_r);
    u8x8.draw1x2String(0, 0, "Get some"); 
    u8x8.draw1x2String(0, 3, "Sunlight for");
    u8x8.draw1x2String(0, 6, "2 minutes");
    delay(5000);
    u8x8.clear();
    u8x8.setFont(u8x8_font_amstrad_cpc_extended_r);
    u8x8.draw1x2String(5, 0, "Take 5"); 
    u8x8.draw1x2String(4, 3, "push-ups");
    u8x8.draw1x2String(3, 6, "right now!");
    delay(3000);
  }
  u8x8.refreshDisplay();  
  delay(200);
}
