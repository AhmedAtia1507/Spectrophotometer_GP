#include "MyInitialization.h"

void MyInitialization::initAP() {
  const char *ssid = "SPECTRO";
  const char *password = "123456789";
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
}

void MyInitialization::initSPIFFS() {
  if (!SPIFFS.begin(true)) {
    Serial.println("An error has occurred while mounting SPIFFS");
  } else {
    Serial.println("SPIFFS mounted successfully");
  }
}


void MyInitialization::sdInit() {
  if (!SD.begin(5)) {
    Serial.println("Card Mount Failed");
    return;
  }
  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);
  Serial.printf("Total space: %lluMB\n", SD.totalBytes() / (1024 * 1024));
  Serial.printf("Used space: %lluMB\n", SD.usedBytes() / (1024 * 1024));
}

void MyInitialization::initWeb(AsyncWebServer& server) {
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/index.html", "text/html"); });
  server.serveStatic("/", SPIFFS, "/");
  server.onNotFound([](AsyncWebServerRequest *request)
                    { request->send(404, "text/plain", "Not Found"); });
  AsyncElegantOTA.begin(&server);
  server.begin();
}
