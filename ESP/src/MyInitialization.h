#ifndef MY_INITIALIZATION_H
#define MY_INITIALIZATION_H

#include <WiFi.h>
#include <SD.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
#include <ArduinoJson.h>
#include <map>

class MyInitialization {
public:
  static void initAP();
  static void sdInit();
  static void initWeb(AsyncWebServer& server);
 
};

#endif  // MY_INITIALIZATION_H
