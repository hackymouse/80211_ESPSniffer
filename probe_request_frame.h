
#ifndef PROBE_REQUEST_FRAME_h
#define PROBE_REQUEST_FRAME_h


#include "Arduino.h" 
#include "defines.h"
#include "frame_body.h"

#include <WiFi.h>
#include <Wire.h>

#include "esp_wifi.h"

class Probe_Request_Frame : public Frame_Body {
public:
  Probe_Request_Frame(unsigned char *p, uint16_t l);
  ~Probe_Request_Frame();
	void print();
  unsigned char *ssid;
  uint8_t ssid_l;

private:

};


#endif