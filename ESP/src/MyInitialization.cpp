#include "MyInitialization.h"


void MyInitialization::initAP() {
  const char *ssid = "SPECTRO";
  const char *password = "123456789";
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
}

void serveStaticFile(AsyncWebServerRequest *request) {
  String path = request->url();  // Get requested URL path
  Serial.println(path);
  // Adjust path if needed (e.g., strip query parameters)

  // Open requested file from SD card
  File file = SD.open("/webpages" + path, "r");  // Adjust base directory as needed

  if (file) {
    // Get file size
    size_t fileSize = file.size();

    // Set content type based on file extension or type
    String contentType = getContentType(path);

    // Send HTTP response with file content
    request->send(SD, path, contentType, false);  // `false` to indicate not closing the file

    file.close();  // Close file after sending
  } else {
    // File not found
    request->send(404, "text/plain", "File not found");
  }
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
  return "text/plain";  // Default to plain text if type is unknown
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
  
 // Route to serve specific HTML file
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    File file = SD.open("/webpage/main.html");
    if (!file || file.isDirectory()){
      request->send(404, "text/plain", "File not found");
      return;
    }
    request->send(file, "/webpage/main.html", "text/html");
    file.close(); // Close the file after sending
  });


  // Route to serve static files from SD card
  server.onNotFound([](AsyncWebServerRequest *request){
    serveStaticFile(request);
  });


  AsyncElegantOTA.begin(&server);
  server.begin();
}
