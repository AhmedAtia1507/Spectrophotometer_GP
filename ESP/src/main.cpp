#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncWebSocket.h>
#include <ArduinoJson.h>
#include <AsyncTCP.h>
#include <AsyncElegantOTA.h>
#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include "MyInitialization.h"
#include "MySDFunctions.h"
#include "HandleMessage.h"

AsyncWebServer server(80); // Create AsyncWebServer object on port 80
AsyncWebSocket ws("/ws");  // Create a WebSocket object

void notifyClients(String state)
{
  ws.textAll(state); // send data to the connected webpage
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len)
{
  AwsFrameInfo *info = (AwsFrameInfo *)arg;

  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT)
  {
    data[len] = 0;
    String message = (char *)data;
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, message);
    if (strcmp((char *)data, "barStates") == 0)
    {
      notifyClients(getOutputStates());
    }
   handleifelse(doc);
  }
}
void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, uint8_t *data, size_t len)
{
  switch (type)
  {
  case WS_EVT_CONNECT:
    Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
    break;
  case WS_EVT_DISCONNECT:
    Serial.printf("WebSocket client #%u disconnected\n", client->id());
    break;
  case WS_EVT_DATA:
    handleWebSocketMessage(arg, data, len);
    break;
  case WS_EVT_PONG:
  case WS_EVT_ERROR:
    break;
  }
}

void initWebSocket()
{
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}
 void listFiles() {
    File root = SD.open("/");
    while (File file = root.openNextFile()) {
        Serial.println(file.name());
        file.close();
    }
}
void setup()
{
  Serial.begin(115200);
  Serial2.begin(115200);
  MyInitialization::initAP();
  initWebSocket();
  MyInitialization::sdInit();
  listFiles();
  MyInitialization::initWeb(server);
}
void loop()
{
  // Check for new WebSocket messages
  ws.cleanupClients();
  delay(1000); // Delay before sending the next command
}