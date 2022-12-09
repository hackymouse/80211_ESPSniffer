

#include "string.h"
#include <WiFi.h>
#include <Wire.h>

#include "esp_wifi.h"
#include "defines.h"

#include "frame_body.h"
#include "probe_request_frame.h"
const char hidden_string[7] = "hidden";

void Probe_Request_Frame::print(){
  Serial.print(F("PROBE REQUEST FRAME | SSID : "));
  Serial.print((char*)ssid);
  Serial.println();
}


//unsigned char ssids[10][33];


Probe_Request_Frame::Probe_Request_Frame(unsigned char *p, uint16_t _l): Frame_Body(p, l) {

  
  
  if(raw[0] == 0x00){
  
    ssid_l = raw[1]+1;
    
    
    if(ssid_l > 1){
      ssid = new unsigned char[ssid_l];
      for(int i = 0; i < ssid_l; i ++){
        ssid[i] = raw[2+i];
      }
      ssid[ssid_l - 1] = '\0';
    }
    else{
      ssid_l = 7;
      ssid = new unsigned char[ssid_l];
      //strcpy((char *) ssid,hidden_string);
    }
  }
  else{
    ssid_l = 7;
    ssid = new unsigned char[ssid_l];
    //strcpy((char *) ssid,hidden_string);
  }

}

Probe_Request_Frame::~Probe_Request_Frame()  {
  delete ssid;
}