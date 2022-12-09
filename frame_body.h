
#ifndef FRAME_BODY_h
#define FRAME_BODY_h


#include "Arduino.h" 
#include "defines.h"

#include <WiFi.h>
#include <Wire.h>

#include "esp_wifi.h"

class Frame_Body {
public:
	Frame_Body(unsigned char *p, uint16_t l);
  virtual ~Frame_Body();
	virtual void print();
  unsigned char *raw;
  uint16_t l;
private:

};


#endif