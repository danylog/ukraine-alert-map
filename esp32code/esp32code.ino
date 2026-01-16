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

WiFiManager wm;
String url;

void setup() {
  wm.autoConnect("AutoConnectAP");  // password protected ap

  url = "https://api.alerts.in.ua/v1/iot/active_air_raid_alerts_by_oblast.json?token=" + api_token;

  Serial.begin(115200);
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;

    Serial.print("[HTTP] begin...\n");

    http.begin(url);

    Serial.print("[HTTP] GET...\n");
    int httpCode = http.GET();

    if (httpCode > 0) {
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);

      if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        Serial.println(payload);
      }
    } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  }

  delay(10000);
}
