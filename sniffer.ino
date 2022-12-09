
#include <WiFi.h>
#include <Wire.h>

#include "esp_wifi.h"


#include "802_11Frame.h"



int curChannel = 1;


void sniffer(void* buf, wifi_promiscuous_pkt_type_t type) {

  wifi_promiscuous_pkt_t *p = (wifi_promiscuous_pkt_t*)buf; 

  if (p->rx_ctrl.rx_state != 0) {delete p; return;}
  Frame802_11 *f = new Frame802_11(p);

  if(f->type == TYPES::MANAGEMENT && (MGMT)f->subType == MGMT::BEACON){
    f->body->print();
  }
  if(f->type == TYPES::MANAGEMENT && (MGMT)f->subType == MGMT::PROBE_REQUEST){
    f->body->print();
  }
  delete f;
  
}



void setup() {
  // put your setup code here, to run once:
  /* start Serial */

  
  Serial.begin(115200);

  /* setup wifi */
  wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
  esp_wifi_init(&cfg);
  esp_wifi_set_storage(WIFI_STORAGE_RAM);
  esp_wifi_set_mode(WIFI_MODE_NULL);
  esp_wifi_start();
  esp_wifi_set_promiscuous(true);
//  esp_wifi_set_promiscuous_filter(&filt);
  esp_wifi_set_promiscuous_rx_cb(&sniffer);
  esp_wifi_set_channel(curChannel, WIFI_SECOND_CHAN_NONE);
  
  Serial.println("starting!");
}
uint32_t timer = 0;
void loop() {
  if(timer< millis()-200){
  Serial.println(ESP.getFreeHeap());//Serial.print("  "); Serial.println(ESP.getHeapFragmentation());
  timer = millis();
  }
  

}
