#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiManager.h>
#include <WS2812FX.h>

#include "env.h"

// SETTINGS
#define LED_PIN 23                      // digital pin used to drive the LED strip
#define UPDATE_TIME_MILLISECONDS 10000  //DON'T PUT LESS THAN 9000, YOU WILL GET BANNED
// ........

#define LED_COUNT 25  // number of LEDs on the strip
#define REGION_COUNT 27 // amount of regions we get as response from the API

WS2812FX led_array = WS2812FX(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

WiFiManager wm;

const String url = String("https://api.alerts.in.ua/v1/iot/active_air_raid_alerts_by_oblast.json?token=") + API_TOKEN;

typedef struct
{
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
  { "Zhytomyr", 5 },
  { "Vinnytsia", 2 },
  { "Khmelnytskyi", 23 },
  { "Rivne", 17 },
  { "Volyn", 1 },
  { "Ternopil", 20 },
  { "Chernivtsi", 25 },
  { "Ivano-Frankivsk", 8 },
  { "Zakarpattia", 6 },
  { "Lviv", 13 },
  { "Kyiv City", 9 },
  { "Sevastopol City", 18 }
};

char unsorted_letters[REGION_COUNT + 1];

char sorted_letters[REGION_COUNT + 1];

uint32_t lastTime = 0;


void setup() {
  wm.autoConnect("AutoConnectAP");  // password protected ap

  Serial.begin(115200);

  led_array.init();
  led_array.setBrightness(60);
  led_array.start();
}

void loop() {
  if (millis() - lastTime >= UPDATE_TIME_MILLISECONDS) {
    lastTime = millis();
    if (WiFi.status() == WL_CONNECTED) {
      fetchData();
      sortData();
    }
    displayData();
  }
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
    led_array.setPixelColor(i, c);
  }

  handleSpecial(27, 0, ORANGE);   // Crimea & Sevastopol
  handleSpecial(26, 13, ORANGE);  // Kyiv City & Kyiv Oblast

  led_array.show();
}

void handleSpecial(uint8_t idxA, uint8_t idxN, uint32_t color) {
  if (sorted_letters[idxA] == 'A' && sorted_letters[idxN] == 'N') {
    led_array.setPixelColor(idxN, color);
  }
}

void sortData() {
  for (int i = 0; i < REGION_COUNT; i++) {
    sorted_letters[i] = unsorted_letters[(regions[i].string_index)];
  }
}
