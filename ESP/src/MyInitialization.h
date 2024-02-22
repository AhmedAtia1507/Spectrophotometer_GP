#ifndef MY_INITIALIZATION_H
#define MY_INITIALIZATION_H

#include <WiFi.h>
#include <SPIFFS.h>
#include <SD.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>

class MyInitialization {
public:
  static void initAP();
  static void initSPIFFS();
  static void sdInit();
  static void initWeb(AsyncWebServer& server);
};

#endif  // MY_INITIALIZATION_H
