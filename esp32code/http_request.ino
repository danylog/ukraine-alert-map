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
        Serial.println(payload);
        payload.remove(0,1);
        Serial.println(payload);
        payload.remove(27,1);
        Serial.println(payload);
        payload.toCharArray(unsorted_letters, sizeof(unsorted_letters));
        Serial.println(" ");
        Serial.println(unsorted_letters);
        Serial.println(" ");
      }
    } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
}

 



