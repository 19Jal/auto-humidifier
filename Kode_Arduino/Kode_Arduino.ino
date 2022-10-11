#include <SoftwareSerial.h> 
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define DHTPIN 4     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, 9);
DHT dht(DHTPIN, DHTTYPE);
SoftwareSerial BT(2,3);

int H_setpoint;

void setup() {
  Serial.begin(9600);
  BT.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3D)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println("Auto Humidifier");
  display.display(); 
  dht.begin();
  delay(3000);
}

void loop() {
  int H = dht.readHumidity();
  display.clearDisplay();
  display.println("Kelembaban:");
  display.setCursor(0, 12);
  display.println(H);
  Serial.print("Kelembaban: ");      
  Serial.print(H);
  Serial.println("%");  
  
  if(BT.available() > 0)  
  {
    H_setpoint = BT.parseInt();
    Serial.print("Setpoint: ");      
    Serial.print(H_setpoint);
    Serial.println("%");         
  }   
  
  if(H <= H_setpoint){
    digitalWrite(5,HIGH);
  }else if(H > H_setpoint){
    digitalWrite(5,LOW);
  }
}
