

#include "string.h"
#include <WiFi.h>
#include <Wire.h>

#include "esp_wifi.h"
#include "defines.h"

#include "frame_body.h"
#include "beacon_frame.h"

void Beacon_Frame::print(){
  Serial.print(F("BEACON FRAME | SSID : "));
  Serial.print((char*)ssid);
  Serial.println();
}


//unsigned char ssids[10][33];


Beacon_Frame::Beacon_Frame(unsigned char *p, uint16_t _l): Frame_Body(p, l) {
  
  if(raw[12] == 0x00){
    ssid_l = raw[13]+1;
    
    if(ssid_l > 1){
      ssid = new unsigned char[ssid_l];
      for(int i = 0; i < ssid_l; i ++){
        ssid[i] = raw[14+i];
      }
      ssid[ssid_l - 1] = '\0';
    }
    else{
      ssid_l = 7;
      ssid = new unsigned char[ssid_l];
      strcpy((char *) ssid,"hidden");
    }
  }
  else{
    ssid_l = 3;
    ssid = new unsigned char[ssid_l];
    ssid[0] = 'N';
    ssid[1] = 'A';
    ssid[2] = '\0';
  }

}

Beacon_Frame::~Beacon_Frame(){
  //Serial.print("f");
  delete ssid;
}