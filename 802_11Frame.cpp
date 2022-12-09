#include "string.h"
#include <WiFi.h>
#include <Wire.h>

#include "esp_wifi.h"
#include "defines.h"
#include "beacon_frame.h"
#include "probe_request_frame.h"
#include "802_11Frame.h"

#include "rom/crc.h"





void newFunc(uint8_t var) {
  for (uint8_t test = 0x80; test!= 0; test >>= 1) {
    Serial.write(var  & test ? '1' : '0');
  }
  Serial.println();
}


Frame802_11::~Frame802_11(){
  delete header;
  delete body;
}

Frame802_11::Frame802_11(wifi_promiscuous_pkt_t *p) {
  header = new FrameHeader;
  // this needs to change for ACK header that is shorter! test type subtype first
  memcpy(header, p->payload, sizeof(FrameHeader)); //error for all int16 because of little endian thing need to inverse the two bytes in each or define two int8 instead
  checksum = 0;

  // NOT SURE THE CHECKSUM IS INCLUDED...

  memcpy(((uint8_t*)&checksum), &(p->payload[p->rx_ctrl.sig_len-1]), 1);
  memcpy(((uint8_t*)&checksum)+1, &(p->payload[p->rx_ctrl.sig_len-2]), 1);
  memcpy(((uint8_t*)&checksum)+2, &(p->payload[p->rx_ctrl.sig_len-3]), 1);
  memcpy(((uint8_t*)&checksum)+3, &(p->payload[p->rx_ctrl.sig_len-4]), 1);

  uint32_t romCRC = (~crc32_le(0, (const uint8_t*)p->payload, p->rx_ctrl.sig_len-4))^0xffffffff;


  uint8_t t = (header->fctl.typeVer & TYPE_MASK) >> TYPE_OFF;
  uint8_t st = (header->fctl.typeVer & SUBTYPE_MASK) >> SUBTYPE_OFF;

  type = (TYPES) t;
  subType = st;
  if((TYPES)t == TYPES::MANAGEMENT && (MGMT)st == MGMT::BEACON){
    body = new Beacon_Frame(&(p->payload[sizeof(FrameHeader)]), p->rx_ctrl.sig_len - 4 - sizeof(FrameHeader));
  }
  else if((TYPES)t == TYPES::MANAGEMENT && (MGMT)st == MGMT::PROBE_REQUEST){
    body = new Probe_Request_Frame(&(p->payload[sizeof(FrameHeader)]), p->rx_ctrl.sig_len - 4 - sizeof(FrameHeader));
  }
  else{
    body = new Frame_Body(&(p->payload[sizeof(FrameHeader)]), p->rx_ctrl.sig_len - 4 - sizeof(FrameHeader));
  }


}

void Frame802_11::print(){

  uint8_t t = (header->fctl.typeVer & TYPE_MASK) >> TYPE_OFF;
  uint8_t st = (header->fctl.typeVer & SUBTYPE_MASK) >> SUBTYPE_OFF;


  Serial.print(F("Type : ")); Serial.print(TYPES_NAMES[t]);
  Serial.print(F("  Subtype : ")); Serial.print(SUBTYPES_NAMES[(t<<4)+st]);
  Serial.println();
}  







