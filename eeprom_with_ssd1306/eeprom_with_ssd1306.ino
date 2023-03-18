#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include "CX01.h"

Adafruit_SSD1306 display(128, 64, &Wire, -1);

unsigned char bitmap_buffers[512] = {0};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC, SSD1306_ADDRESS)){
    Serial.print(F("Unable to init SSD1306!"));
  }
  Wire.begin();
  display.display();
  delay(2000);
  display.clearDisplay();
  
  //print for the moon first:
  for(int a=0; a<=BITMAP_BUFFERS_SIZE; a++){
    bitmap_buffers[a] = (char)getDataEEPROM(moon_start+a);
  }
  display.drawBitmap(0, 0, bitmap_buffers, BITMAP_WIDTH, BITMAP_HEIGHT, SSD1306_WHITE);
  display.display();
  delay(3000);
  display.clearDisplay();
  
  //star_start
  for(int a=0; a<=BITMAP_BUFFERS_SIZE; a++){
    bitmap_buffers[a] = (char)getDataEEPROM(star_start+a);
  }
  display.drawBitmap(0, 0, bitmap_buffers, BITMAP_WIDTH, BITMAP_HEIGHT, SSD1306_WHITE);
  display.display();
  delay(3000);
  display.clearDisplay();

  //moonstar_start
  for(int a=0; a<=BITMAP_BUFFERS_SIZE; a++){
    bitmap_buffers[a] = (char)getDataEEPROM(moonstar_start+a);
  }
  display.drawBitmap(0, 0, bitmap_buffers, BITMAP_WIDTH, BITMAP_HEIGHT, SSD1306_WHITE);
  display.display();
  delay(3000);
  display.clearDisplay();
}

void loop() {
  

}

byte getDataEEPROM(int address){
  byte data = 0xFF;
  Wire.beginTransmission(I2C_ADDRESS);
  Wire.write((int)(address >> 8)); //MSB
  Wire.write((int)(address & 0xFF));
  Wire.endTransmission();
  Wire.requestFrom(I2C_ADDRESS, 1);
  data = Wire.read();
  return data;
}
