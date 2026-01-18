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

#include <WS2812FX.h>

#define LED_PIN 5     // digital pin used to drive the LED strip
#define LED_COUNT 25  // number of LEDs on the strip

WS2812FX led_array = WS2812FX(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

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







char unsorted_letters[REGION_COUNT + 1];


char sorted_letters[REGION_COUNT + 1];


void setup() {
  wm.autoConnect("AutoConnectAP");  // password protected ap

  url = "https://api.alerts.in.ua/v1/iot/active_air_raid_alerts_by_oblast.json?token=" + api_token;

  Serial.begin(115200);

  led_array.init();
  led_array.setBrightness(128);
  led_array.start();
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    fetchData();
    sortData();
  }

  displayData();
  delay(10000);
}

void displayData() {
  for (int i = 0; i < LED_COUNT; i++) {
    uint32_t c;
    switch (sorted_letters[i]) {
      case 'A':
        c = RED;
        break;
      case 'P':
        c = ORANGE;
        break;
      case 'N':
        c = GREEN;
        break;
    }
    Serial.print(regions[i].name);
    Serial.print(" ");
    Serial.println(sorted_letters[i]);
    led_array.setPixelColor(i, c);
    
  }

  handleSpecial(27, 0, ORANGE);  // Crimea & Sevastopol
  handleSpecial(26, 13, ORANGE); // Kyiv City & Kyiv Oblast

  led_array.show();
}

void handleSpecial(uint8_t idxA, uint8_t idxN, uint32_t color) {
  if(sorted_letters[idxA] == 'A' && sorted_letters[idxN] == 'N') {
    led_array.setPixelColor(idxN, color);
  }
}

void sortData() {

  for (int i = 0; i < REGION_COUNT; i++) {
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
