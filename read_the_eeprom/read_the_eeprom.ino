#include <Wire.h>

const int I2C_ADDRESS = 0x50;
const uint8_t moon_start = 0;
const uint8_t moon_end   = 71;
const uint8_t star_start = 72;
const uint8_t star_end   = 143;
const uint8_t moonstar_start = 144;
const uint8_t moonstar_end = 215;

uint8_t bR = 16;
uint8_t bRIndex = 0;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);

  //print for the moon first:
  for(int a=moon_start; a<=moon_end; a++){
    Serial.print(getDataEEPROM(a));
    Serial.print(", ");
    bRIndex++;
    if(bRIndex == bR){
      bRIndex = 0;
      Serial.println("");
    }
  }
  bRIndex = 0;

  Serial.println("");
  Serial.println("");

  for(int a=star_start; a<=star_end; a++){
    Serial.print(getDataEEPROM(a));
    Serial.print(", ");
    bRIndex++;
    if(bRIndex == bR){
      bRIndex = 0;
      Serial.println("");
    }
  }
  bRIndex = 0;

  Serial.println("");
  Serial.println("");

  for(int a=moonstar_start; a<=moonstar_end; a++){
    Serial.print(getDataEEPROM(a));
    Serial.print(", ");
    bRIndex++;
    if(bRIndex == bR){
      bRIndex = 0;
      Serial.println("");
    }
  }
  bRIndex = 0; 
}

void loop() {
  // put your main code here, to run repeatedly:

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
