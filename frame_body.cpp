

#include "string.h"
#include <WiFi.h>
#include <Wire.h>

#include "esp_wifi.h"
#include "defines.h"

#include "frame_body.h"

void Frame_Body::print(){

  for (int i=0; i<5; i++) { 
    if (raw[i]<0x10) {Serial.print("0");} 
    Serial.print(raw[i],HEX); 
    Serial.print(" "); 
  }
  Serial.println();
}

Frame_Body::Frame_Body(unsigned char *p, uint16_t _l) {
  l = _l;
  raw = new unsigned char[l];
  memcpy(raw, p, l);

}

Frame_Body::~Frame_Body() {
  //Serial.print('b');
  delete raw;
}