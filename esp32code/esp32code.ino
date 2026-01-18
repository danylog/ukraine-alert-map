/**
 * BasicHTTPClient.ino
 *
 *  Created on: 24.05.2015
 *
 */

#include <Arduino.h>

#include <WiFi.h>
#include <WiFiMulti.h>

#include <HTTPClient.h>

#include "env.h"

#include <WiFiManager.h>

#define REGION_COUNT 27

WiFiManager wm;
String url;

typedef struct {
  char name[30];
  uint8_t string_index;
} Region;

const Region regions[]{
    { "Crimea", 0 },
    { "Kherson", 22 },
    { "Zaporizhzhia", 7 },
    { "Donetsk", 4 },
    { "Luhansk", 12 },
    { "Kharkiv", 21 },
    { "Dnipropetrovsk", 3 },
    { "Mykolaiv", 14 },
    { "Odesa", 15 },
    { "Kirovohrad", 11 },
    { "Poltava", 16 },
    { "Sumy", 19 },
    { "Chernihiv", 26 },
    { "Kyiv", 10 },
    { "Cherkasy", 24 },
    { "Vinnytsia", 2 },
    { "Zhytomyr", 5 },
    { "Rivne", 17 },
    { "Khmelnytsky", 23 },
    { "Chernivtsi", 25 },
    { "Ternopil", 20 },
    { "Ivano-Frankivsk", 8 },
    { "Zakarpattia", 6 },
    { "Lviv", 13 },
    { "Volyn", 1 },
    { "Kyiv City", 9 },
    { "Sevastopol City", 18 }
};







char unsorted_letters[REGION_COUNT+1];


char sorted_letters[REGION_COUNT+1];


void setup() {
  wm.autoConnect("AutoConnectAP");  // password protected ap

  url = "https://api.alerts.in.ua/v1/iot/active_air_raid_alerts_by_oblast.json?token=" + api_token;

  Serial.begin(115200);
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    fetchData();
    sortData();
  }


  delay(10000);
}

void sortData(){

for(int i = 0; i< REGION_COUNT; i++){
      sorted_letters[i] = unsorted_letters[(regions[i].string_index)];
      Serial.print(i);
      Serial.print(" ");
      Serial.print(regions[i].string_index);
      Serial.print(" ");
      Serial.print(unsorted_letters[(regions[i].string_index)]);
      Serial.print(" ");
      Serial.println(sorted_letters); 
}
Serial.println(" ");
Serial.println(unsorted_letters);
Serial.println(sorted_letters);
Serial.println("");
}
