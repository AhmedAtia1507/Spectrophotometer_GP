#include "MyInitialization.h"
#include "MySDFunctions.h"

void MyInitialization::initAP()
{
  const char *ssid = "SPECTRO";
  const char *password = "123456789";
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
}

String getContentType(String filename)
{
  if (filename.endsWith(".html"))
    return "text/html";
  else if (filename.endsWith(".css"))
    return "text/css";
  else if (filename.endsWith(".js"))
    return "application/javascript";
  else if (filename.endsWith(".png"))
    return "image/png";
  else if (filename.endsWith(".jpg") || filename.endsWith(".jpeg"))
    return "image/jpeg";
  else if (filename.endsWith(".gif"))
    return "image/gif";
  else if (filename.endsWith(".ico"))
    return "image/x-icon";
  else if (filename.endsWith(".xml"))
    return "text/xml";
  else if (filename.endsWith(".pdf"))
    return "application/pdf";
  else if (filename.endsWith(".zip"))
    return "application/zip";
  else if (filename.endsWith(".json"))
    return "application/json";
  else if (filename.endsWith(".svg"))
    return "image/svg+xml";
  else if (filename.endsWith(".mp3"))
    return "audio/mpeg";
  else if (filename.endsWith(".ttf"))
    return "font/ttf";
  else if (filename.endsWith(".woff2"))
    return "font/woff2"; // Add this line for WOFF2 font files

  return "text/plain"; // Default to plain text if type is unknown
}

QueueHandle_t fileRequestQueue;
std::map<int, AsyncWebServerRequest *> requestMap;
int requestIdCounter = 0;                // Unique ID counter
const uint32_t idleTimeoutMs = 5000;    // Idle timeout in milliseconds
TaskHandle_t serveFileTaskHandle = NULL; // Global task handle
SemaphoreHandle_t fileSemaphore;

void serveFileTask(void *parameter)
{
  StaticJsonDocument<256> jsonDoc;
  uint32_t lastActivityTime = millis();
  while (true)
  {
    char jsonBuffer[256];

    if (xQueueReceive(fileRequestQueue, &jsonBuffer, 1000 / portTICK_PERIOD_MS) == pdPASS)
    {
      lastActivityTime = millis(); // Reset the idle timer

      DeserializationError error = deserializeJson(jsonDoc, jsonBuffer);
      if (error)
      {
        Serial.println("Failed to parse JSON request");
        continue;
      }

      int requestId = jsonDoc["requestId"];
      String path = jsonDoc["path"].as<String>();

      // Retrieve the request pointer from the map
      AsyncWebServerRequest *request = requestMap[requestId];
      requestMap.erase(requestId); // Remove the entry from the map

      // Acquire the semaphore before opening the file
      if (xSemaphoreTake(fileSemaphore, portMAX_DELAY) == pdTRUE)
      {
        File file = SD.open("/webpage" + path, "r");

           if (file) {
          String contentType = getContentType(path);

          AsyncWebServerResponse *response = request->beginChunkedResponse(contentType, [file](uint8_t *buffer, size_t maxLen, size_t index) mutable -> size_t {
            size_t bytesRead = file.read(buffer, maxLen);
            if (bytesRead == 0) {
              file.close();
              xSemaphoreGive(fileSemaphore);
            }
            return bytesRead;
          });
         
          // Add cache control headers for certain file types
          if (contentType.startsWith("image/") || contentType == "font/woff2" || contentType == "audio/mpeg" || path == "/css/all.min.css" || path =="/JavaScript/chart.js")  {
            response->addHeader("Cache-Control", "max-age=31536000"); // Cache for 1 year 
          }
          request->send(response);
        }
        else
        {
          // Release the semaphore if the file cannot be opened
          xSemaphoreGive(fileSemaphore);
          request->send(404, "text/plain", "File not found");
        }
      }
      else
      {
        request->send(500, "text/plain", "Failed to acquire file semaphore");
      }
    }

    // Check for idle timeout
    if (millis() - lastActivityTime > idleTimeoutMs||fileRequestQueue==NULL)
    {
      Serial.println("File serving task idle timeout, terminating task.");
      break;
    }
  }
  // Clear the task handle before deleting the task
  serveFileTaskHandle = NULL;
  vTaskDelete(NULL);
}

void serveStaticFile(AsyncWebServerRequest *request)
{
  StaticJsonDocument<256> jsonDoc;
  int requestId = requestIdCounter++;

  jsonDoc["requestId"] = requestId; // Store the unique request ID
  jsonDoc["path"] = request->url();

  char jsonBuffer[256];
  serializeJson(jsonDoc, jsonBuffer);

  // Store the request pointer in the map with the unique ID
  requestMap[requestId] = request;

  if (xQueueSend(fileRequestQueue, &jsonBuffer, portMAX_DELAY) != pdPASS)
  {
    request->send(500, "text/plain", "Server is busy, please try again later.");
    return;
  }
  if (serveFileTaskHandle == NULL)
  {
    BaseType_t taskCreated = xTaskCreate(serveFileTask, "serveFileTask", 8192, NULL, 1, &serveFileTaskHandle);
    if (taskCreated != pdPASS)
    {
      request->send(500, "text/plain", "Failed to create file serving task.");
      return;
    }
    Serial.println("File serving task created.");
  }

  Serial.println("File request added to queue for: " + request->url());
}

void MyInitialization::sdInit()
{
  if (!SD.begin(5))
  {
    Serial.println("Card Mount Failed");
    return;
  }

    uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);
  Serial.printf("Total space: %lluMB\n", SD.totalBytes() / (1024 * 1024));
  Serial.printf("Used space: %lluMB\n", SD.usedBytes() / (1024 * 1024));
}


void handleFileUpload(AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final){
    if(filename.startsWith("/readings")){
    String bath = "/ReadingsDB.txt";
    SdWriteString(bath, filename); // save the name of the file into database
    }
    else{
    String bath = "/presetsDB.txt";
    SdWriteString(bath, filename); // save the name of the file into database  
    }
    if(!index){
        Serial.printf("UploadStart: %s\n", filename.c_str());
        if (SD.exists(filename)) {
            SD.remove(filename);
        }
        File file = SD.open(filename, FILE_WRITE);
        if (!file) {
            Serial.println("Failed to open file for writing");
            return;
        }
        file.close();
    }

    File file = SD.open(filename, FILE_APPEND);
    if (file) {
        if (file.write(data, len) != len) {
            Serial.println("Write failed");
        }
        file.close();
    } else {
        Serial.println("Failed to open file for appending");
    }
    if (final) {
        Serial.printf("UploadEnd: %s, %u B\n", filename.c_str(), index + len);
        request->send(200, "text/plain", "File Uploaded!");
    }
}











void MyInitialization::initWeb(AsyncWebServer &server)
{
  fileRequestQueue = xQueueCreate(20, sizeof(char[256]));
  // Initialize the semaphore with a maximum count of 5
  fileSemaphore = xSemaphoreCreateCounting(2, 2);
  if (fileSemaphore == NULL)
  {
    Serial.println("Failed to create file semaphore!");
    return;
  }

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    File file = SD.open("/webpage/Home.html");
    if (!file || file.isDirectory()) {
      request->send(404, "text/plain", "File not found");
      return;
    }
    request->send(file, "/webpage/Home.html", "text/html");
    file.close(); });

  
  
  server.on("/savetosd", HTTP_POST, [](AsyncWebServerRequest *request){
        request->send(200);
    }, handleFileUpload);
  
  
  server.on("/download", HTTP_GET, [](AsyncWebServerRequest *request){
        if (request->hasParam("filename")) {
            String filename = request->getParam("filename")->value();
            String filepath = filename;
            if (SD.exists(filepath)) {
                request->send(SD, filepath, "text/csv");
            } else {
                request->send(404, "text/plain", "File not found");
            }
        } else {
            request->send(400, "text/plain", "Bad Request");
        }
    });


  server.onNotFound([](AsyncWebServerRequest *request)
                    { serveStaticFile(request); });

  AsyncElegantOTA.begin(&server);
  server.begin();
}
