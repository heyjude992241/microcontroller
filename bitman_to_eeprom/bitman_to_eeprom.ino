#include <Wire.h>

const int I2C_ADDRESS = 0x50;
const int BITMAP_ARRAY_SIZE = 72;
const uint8_t BITMAP_COUNT = 3;

unsigned char bitmaps[][BITMAP_ARRAY_SIZE] = {
  {
    0x00, 0xc0, 0x00, 0x03, 0xc0, 0x00, 0x07, 0x80, 0x00, 0x1d, 0x80, 0x00, 0x39, 0x00, 0x00, 0x31, 
    0x00, 0x00, 0x63, 0x00, 0x00, 0x63, 0x00, 0x00, 0x41, 0x00, 0x00, 0xc1, 0x00, 0x00, 0xc1, 0x80, 
    0x00, 0xc1, 0x80, 0x00, 0xc0, 0xc0, 0x00, 0xc0, 0x60, 0x00, 0x40, 0x30, 0x03, 0x40, 0x1e, 0x1f, 
    0x60, 0x0f, 0xfe, 0x30, 0x00, 0x06, 0x30, 0x00, 0x0c, 0x18, 0x00, 0x18, 0x0e, 0x00, 0x30, 0x07, 
    0x00, 0xe0, 0x01, 0xff, 0xc0, 0x00, 0x3e, 0x00
  },
  {
    0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x66, 0x00, 0x00, 
    0x66, 0x00, 0x00, 0x42, 0x00, 0x00, 0xc3, 0x00, 0x7f, 0x81, 0xfe, 0xf8, 0x00, 0x1f, 0xe0, 0x00, 
    0x07, 0x30, 0x00, 0x0e, 0x18, 0x00, 0x18, 0x0c, 0x00, 0x30, 0x06, 0x00, 0x60, 0x02, 0x00, 0x40, 
    0x06, 0x00, 0x60, 0x06, 0x00, 0x60, 0x04, 0x18, 0x20, 0x04, 0x3c, 0x20, 0x0c, 0xe7, 0x30, 0x0f, 
    0x81, 0xf0, 0x0e, 0x00, 0x70, 0x00, 0x00, 0x00
  },
  {
    0x00, 0xc0, 0x00, 0x03, 0x80, 0x08, 0x0f, 0x80, 0x1c, 0x19, 0x00, 0x1e, 0x33, 0x00, 0x0c, 0x32, 
    0x01, 0x00, 0x62, 0x03, 0x00, 0x42, 0x07, 0x80, 0x42, 0x0c, 0xe0, 0xc2, 0x0e, 0xc0, 0xc3, 0x03, 
    0x80, 0xc1, 0x03, 0x00, 0xc1, 0x80, 0x00, 0xc0, 0xc0, 0x00, 0xc0, 0xc0, 0x01, 0x40, 0x70, 0x07, 
    0x60, 0x1c, 0x1f, 0x20, 0x07, 0xf6, 0x30, 0x00, 0x04, 0x18, 0x00, 0x0c, 0x0c, 0x00, 0x18, 0x07, 
    0x00, 0x70, 0x01, 0xf7, 0xc0, 0x00, 0x7f, 0x00
  }
};
int addr_buffer = 0;
uint8_t bR = 16;
uint8_t bRIndex = 0;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
  for(int a=0; a<BITMAP_COUNT; a++){
    for(int b=0; b<BITMAP_ARRAY_SIZE; b++){
      setDataEEPROM(addr_buffer++, bitmaps[a][b]);
    }
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:
}

void setDataEEPROM(int address, byte data){
  Wire.beginTransmission(I2C_ADDRESS);
  Wire.write((int)(address >> 8));
  Wire.write((int)(address & 0xFF));
  Wire.write(data);
  Wire.endTransmission();
  delay(5);
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
