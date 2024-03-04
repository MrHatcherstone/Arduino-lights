#include <Adafruit_NeoPixel.h> //библиотека подсветки
#include <ESP8266WiFi.h> //библиотека wi-fi
#include <ESP8266WebServer.h> //библиотека server
#include <Esp.h>
#include <FS.h>

#include <EEPROM.h>
#include "base64.hpp"

#include "ArduinoJson.h"
#include "ArduinoJson.hpp"

#include "wifiAuth.h"
#include "WeelColour.h"
#include "WeelColourReverse.h"
#include "staticColour.h"
#include "Randomizer.h"
#include "WeelColourPinkBlue.h"
#include "indexPage.h"
#include "loadSettings.h"
#include "saveSettings.h"
#include "WiFiConnect.h"
#include "settingsPage.h"
#include "init.h"

#define NO_OTA_PORT
#include <ArduinoOTA.h>

#define PIN D8
//#define LED1 D4 // встроенная светилка ESP-12E
#define pix_length 60 // половина длины ленты

int colour = 0;
int lightningType = 0;
int ledPosition = 0;
int tempLedPosition = 0;
int ledBright = 0;
int ledDelay = 0;
int int_R = 0;
int int_G = 0;
int int_B = 0;
int diff = 1;
File configFile;
bool workIsFinished = true;
unsigned long previousMillis = 0;
unsigned long currentMillis = 0;
String mainPage = "";
String settingsPage = "";
String finiser = "";
extern const char* ssid;
extern const char* password;


void loadConfig(WiFiCredentials& credentials) {
  EEPROM.begin(sizeof(WiFiCredentials));
  EEPROM.get(0, credentials);
  EEPROM.end();
}

void saveConfig(const WiFiCredentials& credentials) {
  EEPROM.begin(sizeof(WiFiCredentials));
  EEPROM.put(0, credentials);
  EEPROM.end();
}


ESP8266WebServer server(80);

//the Wemos WS2812B RGB shield has 1 LED connected to pin 2
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(2*pix_length, PIN, NEO_GRB + NEO_KHZ800);
int pix_count = 2 * pix_length;

void handleRoot() {
  String mainPageAltered = "";
  if (workIsFinished)
    finiser = "<input type=\"checkbox\" id=\"finished\" name=\"finished\" onchange=\"updateFinish(this.checked)\" checked>";
  else
    finiser = "<input type=\"checkbox\" id=\"finished\" name=\"finished\" onchange=\"updateFinish(this.checked)\"";
  if (mainPage) {
    mainPageAltered = mainPage;
    mainPageAltered.replace("${ledBright}", String(ledBright));
    mainPageAltered.replace("${ledDelay}", String(ledDelay));
    mainPageAltered.replace("${finished}", finiser);
    mainPageAltered.replace("${int_R}", String(int_R));
    mainPageAltered.replace("${int_G}", String(int_G));
    mainPageAltered.replace("${int_B}", String(int_B));
  }
  server.send(200, "text/html", mainPageAltered);
  finiser = "";
  mainPageAltered = "";
}

void handleUpdate() {
  if (server.hasArg("brightness")) {
    ledBright = server.arg("brightness").toInt();
  }
  if (server.hasArg("delay")) {
    ledDelay = server.arg("delay").toInt();
  }
  if (server.hasArg("finished")) {
    workIsFinished = server.arg("finished").toInt();
  }
  if (server.hasArg("red") && server.hasArg("green") && server.hasArg("blue")) {
    int_R = server.arg("red").toInt();
    int_G = server.arg("green").toInt();
    int_B = server.arg("blue").toInt();
  }
  if (server.hasArg("type")) {
    String type = server.arg("type");
    // Serial.println(type);
    workIsFinished = false;
    if (type == "static") {
      lightningType = 1;
      tempLedPosition = ledPosition;
      // Serial.println("staticColour_H");
    } else if (type == "weelcolour") {
      lightningType = 2;
      diff = 1530 / pix_count;
      // Serial.println("WeelColour_H");
    } else if (type == "weelcolourreverse") {
      lightningType = 3;
      diff = 1530 / pix_count;
      // Serial.println("WeelColourReverse_H");
    } else if (type == "random") {
      lightningType = 4;
      // Serial.println("Randomizer_H");
    } else if (type == "weelcolourpinkblue") {
      lightningType = 5;
      diff = 510 / pix_count;
      // Serial.println("WeelColourPinkBlue_H");
    } else {
    }
  }
  server.send(200, "text/plain", "OK");
  saveSettings();
}

void handleSettings() {
  settingsPageCreator();
  server.send(200, "text/html", settingsPage);
}

void handleSettingsUpdate() {
  String encodedSSID = server.arg("ssid");
  String encodedPassword = server.arg("pass");
  
  unsigned char decodedSSID[encodedSSID.length()];
  unsigned char decodedPassword[encodedPassword.length()];

  int ssidLength = decode_base64((unsigned char *)encodedSSID.c_str(), decodedSSID);
  int passLength = decode_base64((unsigned char *)encodedPassword.c_str(), decodedPassword);

  String newSSID = "";
  for (int i = 0; i < ssidLength; i++) {
      newSSID += (char)decodedSSID[i];
  }
  String newPassword = "";
  for (int i = 0; i < passLength; i++) {
      newPassword += (char)decodedPassword[i];
  }

  WiFiCredentials newCredentials;
  newSSID.toCharArray(newCredentials.ssid, sizeof(newCredentials.ssid));
  newPassword.toCharArray(newCredentials.password, sizeof(newCredentials.password));
  strcpy(newCredentials.isNew, "updated");
  saveConfig(newCredentials);
  server.send(200, "text/plain", "OK");
  delay(2000);
  ESP.restart();
}

void setup(void){
  Serial.begin(115200);
  pixels.begin(); 
  SPIFFS.begin(); 
  loadSettings();
  serverInit(server);
  otaInit();
  wifiInit();
}

void loop(void) {
  if (workIsFinished == false){
    switch (lightningType) {
        case 0:
          workIsFinished = true;
          break;;
        case 1:
          staticColour();
          break;;  
        case 2:
          WeelColour();
          break;;
        case 3:
          WeelColourReverse();
          break;;
        case 4:
          Randomizer();
          break;;
        case 5:
          WeelColourPinkBlue();
          break;;
    }
  }
  server.handleClient();
  ArduinoOTA.handle();
}
