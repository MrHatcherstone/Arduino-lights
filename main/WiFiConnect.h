#ifndef WiFiConnect_H
#define WiFiConnect_H

#include <ESP8266WiFi.h>
#include <ESP8266WiFi.h> //библиотека wi-fi

// ssid/password вафли и порт сервера
extern const char* ssid;
extern const char* password;
unsigned long connectionTimeout = 30000; //30 sec

void createAP() {
  Serial.println("Creating Access Point...");
  WiFi.softAP("espespesp", "espespesp");
  Serial.println("Access Point created!");

  Serial.println("IP Address: ");
  Serial.println(WiFi.softAPIP());
}

void connectToWiFi() {
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  unsigned long startTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startTime < connectionTimeout) {
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Connected to WiFi!");
    Serial.println("IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("Connection failed. Creating Access Point...");
    createAP();
  }
}

#endif
