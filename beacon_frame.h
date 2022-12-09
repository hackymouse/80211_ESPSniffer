
#ifndef BEACON_FRAME_h
#define BEACON_FRAME_h


#include "Arduino.h" 
#include "defines.h"
#include "frame_body.h"

#include <WiFi.h>
#include <Wire.h>

#include "esp_wifi.h"

class Beacon_Frame : public Frame_Body {
public:
  Beacon_Frame(unsigned char *p, uint16_t l);
  ~Beacon_Frame();
	void print();
  unsigned char *ssid;
  uint8_t ssid_l;

private:

};


#endif