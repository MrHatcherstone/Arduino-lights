#ifndef init_H
#define init_H

#include <ESP8266WebServer.h> //библиотека server
#define NO_OTA_PORT
#include <ArduinoOTA.h>

extern const char* ssid;
extern const char* password;

struct WiFiCredentials {
  char ssid[32];
  char password[64];
  char isNew[8];
};

void loadConfig(WiFiCredentials& credentials);
void handleRoot();
void handleUpdate();
void handleSettings();
void handleSettingsUpdate();


void wifiInit() {
  WiFiCredentials savedCredentials;
  loadConfig(savedCredentials);
  if (savedCredentials.isNew == "updated") {
    if (strlen(savedCredentials.ssid) > 0 && strlen(savedCredentials.password) > 0) {
        ssid = savedCredentials.ssid;
        password = savedCredentials.password;
    }
  }
  connectToWiFi();
  Serial.println("Ready"); 
  Serial.print("IP address: "); 
  Serial.println(WiFi.localIP());
}

void serverInit(ESP8266WebServer& server) {
  server.begin();
  server.on("/", HTTP_GET, handleRoot);
  server.on("/update", HTTP_GET, handleUpdate);
  server.on("/settings", HTTP_GET, handleSettings);
  server.on("/settingsupdate", HTTP_GET, handleSettingsUpdate);
  indexCreator();
}

void otaInit() {
  ArduinoOTA.onStart([]() {
    Serial.println("OTA Update Start");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nOTA Update End");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("OTA Progress: %u%%\r", (progress / (total / 100)), "\n");
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("OTA Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
}

#endif
