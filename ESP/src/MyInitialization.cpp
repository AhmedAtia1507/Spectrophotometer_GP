#include "MyInitialization.h"


void MyInitialization::initAP() {
  const char *ssid = "SPECTRO";
  const char *password = "123456789";
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
}

String getContentType(String filename) {
  if (filename.endsWith(".html")) return "text/html";
  else if (filename.endsWith(".css")) return "text/css";
  else if (filename.endsWith(".js")) return "application/javascript";
  else if (filename.endsWith(".png")) return "image/png";
  else if (filename.endsWith(".jpg") || filename.endsWith(".jpeg")) return "image/jpeg";
  else if (filename.endsWith(".gif")) return "image/gif";
  else if (filename.endsWith(".ico")) return "image/x-icon";
  else if (filename.endsWith(".xml")) return "text/xml";
  else if (filename.endsWith(".pdf")) return "application/pdf";
  else if (filename.endsWith(".zip")) return "application/zip";
  else if (filename.endsWith(".json")) return "application/json";
  else if (filename.endsWith(".svg")) return "image/svg+xml";
  else if (filename.endsWith(".mp3")) return "audio/mpeg";
  else if (filename.endsWith(".ttf")) return "font/ttf";
  else if (filename.endsWith(".woff2")) return "font/woff2";  // Add this line for WOFF2 font files

  return "text/plain";  // Default to plain text if type is unknown
}



struct FileRequest {
  AsyncWebServerRequest *request;
  String path;
};

QueueHandle_t fileRequestQueue;

void serveFileTask(void *parameter) {
  FileRequest fileRequest;

  while (true) {
    // Check if the queue handle is null and exit the task if it is
    if (fileRequestQueue == NULL) {
      Serial.println("File request queue is NULL, ending task.");
      vTaskDelete(NULL);  // Delete the current task
    }

    // Wait for a file request from the queue
    if (xQueueReceive(fileRequestQueue, &fileRequest, portMAX_DELAY) == pdPASS) {
      // Open requested file from SD card
      Serial.println("/webpage" + fileRequest.path);
      File file = SD.open("/webpage" + fileRequest.path, "r");  // Adjust base directory as needed

      if (file) {
        // Get file size
        size_t fileSize = file.size();
        Serial.println(fileSize);

        // Set content type based on file extension or type
        String contentType = getContentType(fileRequest.path);
        Serial.println(contentType);

        // Buffer size for reading chunks
        const size_t bufferSize = 1024;
        uint8_t buffer[bufferSize];

        AsyncWebServerResponse *response = fileRequest.request->beginChunkedResponse(contentType, [file, bufferSize, buffer](uint8_t *chunkBuffer, size_t maxLen, size_t index) mutable -> size_t {
          if (!file.available()) {
            file.close();
            return 0;
          }

          size_t bytesRead = file.read(buffer, min(bufferSize, maxLen));
          memcpy(chunkBuffer, buffer, bytesRead);
          return bytesRead;
        });

        // Add cache control headers
       // response->addHeader("Cache-Control", "max-age=31536000, public");
        
        response->addHeader("Cache-Control", "no-cache, no-store, must-revalidate");
        response->addHeader("Pragma", "no-cache");
        response->addHeader("Expires", "0");

        // Send the response
        fileRequest.request->send(response);
      } else {
        // File not found
        fileRequest.request->send(404, "text/plain", "File not found");
      }
    }
  }
}

void serveStaticFile(AsyncWebServerRequest *request) {
  if (fileRequestQueue == NULL) {
    request->send(500, "text/plain", "Server is not ready, please try again later.");
    return;
  }

  FileRequest fileRequest;
  fileRequest.request = request;
  fileRequest.path = request->url();


  // Send the file request to the queue
  if (xQueueSend(fileRequestQueue, &fileRequest, portMAX_DELAY) != pdPASS) {
    request->send(500, "text/plain", "Server is busy, please try again later.");
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
  // Create a queue to handle file requests
  fileRequestQueue = xQueueCreate(20, sizeof(FileRequest));
  if (fileRequestQueue == NULL) {
    Serial.println("Failed to create file request queue!");
    return;
  } else {
    Serial.println("File request queue created successfully.");
  }

  // Create a task to serve files
  BaseType_t taskCreated = xTaskCreate(serveFileTask, "serveFileTask", 8192, NULL, 1, NULL);
  if (taskCreated != pdPASS) {
    Serial.println("Failed to create file serving task!");
    return;
  } else {
    Serial.println("File serving task created successfully.");
  }

 // Route to serve specific HTML file
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    File file = SD.open("/webpage/Home.html");
    if (!file || file.isDirectory()){
      request->send(404, "text/plain", "File not found");
      return;
    }
    request->send(file, "/webpage/Home.html", "text/html");
    file.close(); // Close the file after sending
  });


// Route to serve static files from SD card
  server.onNotFound([](AsyncWebServerRequest *request){
    serveStaticFile(request);
  });

  
  AsyncElegantOTA.begin(&server);
  server.begin();
}
