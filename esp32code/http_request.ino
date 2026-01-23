void fetchData(){
    HTTPClient http;

    Serial.print("[HTTP] begin...\n");

    http.begin(url);

    Serial.print("[HTTP] GET...\n");
    int httpCode = http.GET();

    if (httpCode > 0) {
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);

      if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        payload.remove(0,1);
        payload.remove(REGION_COUNT,1);
        Serial.println(payload);
        payload.toCharArray(unsorted_letters, sizeof(unsorted_letters));

      }
    } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
}

 



