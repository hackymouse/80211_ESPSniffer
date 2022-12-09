
#ifndef FRAME_h
#define FRAME_h


#include "Arduino.h" 
#include "defines.h"
#include "frame_body.h"

#include <WiFi.h>
#include <Wire.h>

#include "esp_wifi.h"


typedef struct { 
  uint8_t typeVer;
  uint8_t  flags;
} __attribute__((packed)) FrameCtrlFld;

typedef struct { 
  uint8_t mac[6];
} __attribute__((packed)) MacAddr;

typedef struct { 
  FrameCtrlFld fctl;
  int16_t duration; //duration will be wrong du to int16 little endian
  MacAddr da;
  MacAddr sa;
  MacAddr bssid;
  int16_t seqctl;
} __attribute__((packed)) FrameHeader;

class Frame802_11 {
public:
	Frame802_11(wifi_promiscuous_pkt_t *p);
  ~Frame802_11();
	void print();
	FrameHeader *header;
  Frame_Body *body;
  int32_t checksum;
  TYPES type;
  uint8_t subType;
private:

};
#endif