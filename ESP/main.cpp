/**------------------------------------------------------------------------
 *                           Libraries
 *------------------------------------------------------------------------**/
#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "SPIFFS.h"
#include <AsyncWebSocket.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <AsyncTCP.h>
#include <AsyncElegantOTA.h>
#include "FS.h"
#include "SD.h"
#include "SPI.h"
/*---------------------------- END OF Libraries ----------------------------*/

/**------------------------------------------------------------------------
 *                           Global Variables
 *------------------------------------------------------------------------**/
File fsUploadFile;
unsigned long startTime;
const size_t bufferSize = 1024;
char fileBuffer[bufferSize];
String content;
/*---------------------------- END OF Global Variables ----------------------------*/

/**--------------------------------------------
 *               WiFi Settings
 *---------------------------------------------**/
const char *ssid = "SPECTRO";
const char *password = "123456789";
void initAP()
{
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
}
/*--------------- END OF WiFi Settings --------------*/

/**--------------------------------------------
 *               WebSocket Settings
 *---------------------------------------------**/

AsyncWebServer server(80); // Create AsyncWebServer object on port 80
AsyncWebSocket ws("/ws");  // Create a WebSocket object
/*--------------- END OF WebSocket Settings --------------*/

/**--------------------------------------------
 *               Initialize SPIFFS
 *---------------------------------------------**/
void initSPIFFS()
{
  if (!SPIFFS.begin(true))
  {
    Serial.println("An error has occurred while mounting SPIFFS");
  }
  else
  {
    Serial.println("SPIFFS mounted successfully");
  }
}
/*--------------- END OF Initialize SPIFFS --------------*/

/**--------------------------------------------
 *               File Upload
 *---------------------------------------------**/
bool writeToDatabase(const char *basePath, const DynamicJsonDocument &doc)
{
  // Create a new file with the name from the 'name' field
  String filename = String(basePath) + "/" + doc["name"].as<String>() + ".txt";
  File file = SD.open(filename, FILE_APPEND);
  if (file)
  {
    // Convert JSON to txt format
    serializeJson(doc, file);
    file.println(); // Add a newline for better separation between entries
    file.close();
    return true;
  }
  else
  {
    Serial.println("Error opening file");
    return false;
  }
}

DynamicJsonDocument readFromDatabase(const char *filename)
{
  DynamicJsonDocument doc(1024);
  File file = SD.open(filename);
  if (file)
  {
    // Parse txt to JSON
    if (deserializeJson(doc, file))
    {
      // Assuming the txt structure matches the expected fields
    }
    else
    {
      Serial.println("Failed to parse JSON from txt");
    }
    file.close();
  }
  else
  {
    Serial.println("Error opening file");
  }

  // Return the parsed JSON document
  return doc;
}

DynamicJsonDocument doc(2048);
JsonObject getFilesJson(const char *directory)
{
  File dir = SD.open(directory);
  int count = 1;
  while (File file = dir.openNextFile())
  {
    if (!file.isDirectory())
    {
      String fileName = file.name();
      fileName.replace(".txt", ""); // Remove ".txt" extension
      doc["presets"] = "presets";
      doc["file" + String(count++)] = fileName;
    }
  }
  doc["presetsno"] = count - 1;
  dir.close();

  return doc.as<JsonObject>();
}
/*--------------- END OF File Upload --------------*/

/**--------------------------------------------
 *               Communication Functions
 *---------------------------------------------**/

String sendCMD(const String &input)
{
  // Send the command to the STM32 via UART
  Serial2.println(input);
  Serial.println(input); // debug
  Serial.println("sent command"); // debug
  // Wait for a response from the STM32
  int startTime = millis();
  while (Serial2.available() == 0 && millis() - startTime < 2000)
  {
    delay(1);
  }
  Serial.println("Read from Ahmed");
  // Read and return the response
  String response = Serial2.readStringUntil('\n');
  Serial.println(response);
  return response;
}
String outputSBar[3] = {"UV", "VI", "WL"};
String getOutputStates()
{
  DynamicJsonDocument doc(1024);
  JsonArray sbar = doc.createNestedArray("sbar");
  for (int i = 0; i < 3; i++)
  {
    JsonObject element = sbar.createNestedObject();
    element["output"] = outputSBar[i];
    element["state"] = sendCMD(outputSBar[i]);
  }
  // Serialize the JSON document to a string
  String jsonString;
  serializeJson(doc, jsonString);
  return jsonString;
}

void notifyClients(String state)
{
  ws.textAll(state); // send data to the connected webpage
}

const unsigned long interval = 600000; // 10 minutes in milliseconds
unsigned long previousMillis;
bool loginflag = false; // to check if the user loged in before accessing control page

void startCountdown()
{
  // Call this function to start the countdown
  previousMillis = millis(); // Initialize the timer when starting to count
}

void checkCountdown()
{
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval)
  {
    // Time has passed, reset the timer and update loginFlag
    previousMillis = currentMillis;
    loginflag = false;
  }
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
      Serial.print("WS received");

      notifyClients(getOutputStates());
      Serial.print("WS sent");
    }
    // to handle login
    else if (doc.containsKey("username"))
    {
      Serial.print("rescived car");
      if (doc["username"].as<String>() == "esp32" && doc["password"].as<String>() == "123")
      {
        String jsonString = "";
        DynamicJsonDocument pass(1024);
        pass["username"] = true;
        pass["password"] = true;
        serializeJson(pass, Serial);
        loginflag = true;
        startCountdown();
        serializeJson(pass, jsonString);
        notifyClients(jsonString);
        Serial.println(jsonString);
      }
      else
      {
        String jsonString = "";
        DynamicJsonDocument pass(1024);
        pass["username"] = false;
        pass["password"] = false;
        serializeJson(pass, Serial);
        serializeJson(pass, jsonString);
        notifyClients(jsonString);
      }
    }
    else if (doc.containsKey("flag"))
    {
      String jsonString = "";
      DynamicJsonDocument object(29);
      object["flag"] = loginflag;
      checkCountdown();
      serializeJson(object, jsonString);
      notifyClients(jsonString);
    }
    // lamps check
    else if (doc.containsKey("uvlampstutus"))
    {

      String jsonString = "";
      DynamicJsonDocument object(20);
      // Adding two fields to the JSON object
      // String stutus;
      // stutus=sendCMD((char*)"snduv\n");
      String stutus = "on";
      object["uvlampstutus"] = stutus; // for testing
      serializeJson(object, jsonString);
      notifyClients(jsonString);
    }
    else if (doc.containsKey("vilampstutus"))
    {
      String jsonString = "";
      DynamicJsonDocument object(20);
      // Adding two fields to the JSON object
      // String stutus;
      // stutus=sendCMD((char*)"sndvi\n");
      String stutus = "on";
      object["vilampstutus"] = stutus; // for testing
      serializeJson(object, jsonString);
      notifyClients(jsonString);
    }
    else if (doc.containsKey("turnuvon"))
    {
      String jsonString = "";
      DynamicJsonDocument object(20);
      // Adding two fields to the JSON object
      // String stutus;
      // stutus=sendCMD((char*)"uvon\n");
      String stutus = "on";
      object["uvlampstutus"] = stutus; // for testing
      serializeJson(object, jsonString);
      notifyClients(jsonString);
    }
    else if (doc.containsKey("turnuvoff"))
    {
      String jsonString = "";
      DynamicJsonDocument object(20);
      // Adding two fields to the JSON object
      // String stutus;
      // stutus=sendCMD((char*)"vioff\n");
      String stutus = "off";
      object["uvlampstutus"] = stutus; // for testing
      serializeJson(object, jsonString);
      notifyClients(jsonString);
    }
    else if (doc.containsKey("turnvion"))
    {
      String jsonString = "";
      DynamicJsonDocument object(20);
      // Adding two fields to the JSON object
      // String stutus;
      // stutus=sendCMD((char*)"vion\n");
      String stutus = "on";
      object["vilampstutus"] = stutus; // for testing
      serializeJson(object, jsonString);
      notifyClients(jsonString);
    }
    else if (doc.containsKey("turnvioff"))
    {
      String jsonString = "";
      DynamicJsonDocument object(20);
      // Adding two fields to the JSON object
      // String stutus;
      // stutus=sendCMD((char*)"vioff\n");
      String stutus = "off";
      object["vilampstutus"] = stutus; // for testing
      serializeJson(object, jsonString);
      notifyClients(jsonString);
    }
    else if (doc.containsKey("savepreset"))
    {
      writeToDatabase("/presets", doc);
    }
    else if (doc.containsKey("deletepreset"))
    {
      SD.remove("/presets/" + doc["name"].as<String>() + ".txt");
    }
    else if (doc.containsKey("showpreset"))
    {
      const char *directory = "/presets";
      JsonObject result = getFilesJson(directory);
      String jsonString = "";
      serializeJson(result, jsonString);
      notifyClients(jsonString);
    }
    else if (doc.containsKey("loadthis"))
    {
      String selectthis = doc["loadthis"].as<String>();
      String path = "/presets/" + selectthis + ".txt";
      Serial.print(path);
      String jsonString = "";
      DynamicJsonDocument preset = readFromDatabase(path.c_str());
      serializeJson(preset, jsonString);
      notifyClients(jsonString);
      Serial.print("ana ba3tet malesh feh");
    }
    else if (doc.containsKey("supplystutus"))
    {
      // String stutusp12=sendCMD((char*)"p12\n");
      // String stutusn12=sendCMD((char*)"n12ff\n");
      // String stutusp5=sendCMD((char*)"p5\n");
      // String stutusp33=sendCMD((char*)"p33\n");
      // String stutustwelve=sendCMD((char*)"twelve\n");
      DynamicJsonDocument object(1024);
      object["supplystutus"] = "good";
      object["p12"] = "+11.9"; // for test
      object["n12"] = "-11.8";
      object["p5"] = "4.9";
      object["p33"] = "2.7";
      object["twelve"] = "11";
      String jsonString = "";
      serializeJson(object, jsonString);
      notifyClients(jsonString);
    }

    else if (doc.containsKey("command"))
    {
      String command = doc["command"].as<String>();

      if (command == "Scan")
      {
        if (doc.containsKey("wavelength"))
        {
          Serial2.println("wavelength");
          float wavelengthValue = doc["wavelength"].as<float>();
          delay(100);
          String scanData = String("{\"wavelength\":") + String(wavelengthValue);
          delay(100);
          scanData = scanData + String(",\"intensitySample\":") + sendCMD("sample");
          delay(100);
          scanData = scanData + String(",\"intensity0\":") + sendCMD("reference") + String("}");

          Serial.print("data sent");
          notifyClients(scanData);
          Serial.print("scan data sent");
          // notifyClients(sendCMD(String(wavelengthValue)));
          // ws.textAll("Wavelength value received: " + String(wavelengthValue));
        }
        else
        {
          ws.textAll("Invalid Scan command: Wavelength value is missing.");
        }
      }

      else
      {
        ws.textAll("Unknown command");
      }
    }
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
void sdinit()
{
  if (!SD.begin(5))
  {
    Serial.println("Card Mount Failed");
    return;
  }
  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);
}

void sendFileToClient(AsyncWebSocketClient *client)
{
  // Replace "file.txt" with the path to your file on the SD card
  File file = SD.open("/file.txt");

  if (!file)
  {
    Serial.println("Failed to open file");
    return;
  }

  while (file.available())
  {
    size_t bytesRead = file.readBytes(fileBuffer, sizeof(fileBuffer));
    client->binary(fileBuffer, bytesRead);
  }

  file.close();

  // Notify the client that the file transfer is complete
  client->text("fileSent");
}
void setup()
{

  // Serial port for debugging purposes
  Serial.begin(115200);
  Serial2.begin(115200);
  initSPIFFS();
  initAP();
  initWebSocket();
  sdinit();

  Serial.printf("Total space: %lluMB\n", SD.totalBytes() / (1024 * 1024));
  Serial.printf("Used space: %lluMB\n", SD.usedBytes() / (1024 * 1024));

  server.on(
      "/upload", HTTP_POST, [](AsyncWebServerRequest *request)
      { request->send(200); },
      [](AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final)
      {
        if (!index)
        {
          Serial.printf("Receiving file: %s\n", filename.c_str());
          fsUploadFile = SD.open("/" + filename, FILE_WRITE);
          startTime = millis();
        }
        if (fsUploadFile)
        {
          fsUploadFile.write(data, len);
        }
        if (final)
        {
          fsUploadFile.close();
          unsigned long endTime = millis();
          Serial.printf("File %s uploaded successfully. Time taken: %lu milliseconds\n", filename.c_str(), endTime - startTime);
        }
      });

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/index.html", "text/html"); });

  server.serveStatic("/", SPIFFS, "/");

  // Handle requests for files not found
  server.onNotFound([](AsyncWebServerRequest *request)
                    { request->send(404, "text/plain", "Not Found"); });

  AsyncElegantOTA.begin(&server); // Start ElegantOTA
  // Start the server
  server.begin();
}
void loop()
{
  // Check for new WebSocket messages
  ws.cleanupClients();

  delay(1000); // Delay before sending the next command
}