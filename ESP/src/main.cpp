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
// Define your I2C settings
#define I2C_ADDRESS 0x48  // Replace with your I2C device address
#define DATA_SIZE 4       // 4 bytes float
File fsUploadFile;
unsigned long startTime;
const size_t bufferSize = 1024;
char fileBuffer[bufferSize];
String content;
// Setting the ESP as an Access Point
// access point credentials
const char *ssid = "SPECTRO";
const char *password = "123456789";
void initAP()
{
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password); // connections 5
}

AsyncWebServer server(80); // Create AsyncWebServer object on port 80
AsyncWebSocket ws("/ws");  // Create a WebSocket object
// Initialize UART communication with STM32
// Define UART pins

// Initialize SPIFFS
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
// Variable to store I2C data

void listDir(fs::FS &fs, const char * dirname, uint8_t levels){
  Serial.printf("Listing directory: %s\n", dirname);

  File root = fs.open(dirname);
  if(!root){
    Serial.println("Failed to open directory");
    return;
  }
  if(!root.isDirectory()){
    Serial.println("Not a directory");
    return;
  }

  File file = root.openNextFile();
  while(file){
    if(file.isDirectory()){
      Serial.print("  DIR : ");
      Serial.println(file.name());
      if(levels){
        listDir(fs, file.name(), levels -1);
      }
    } else {
      Serial.print("  FILE: ");
      Serial.print(file.name());
      Serial.print("  SIZE: ");
      Serial.println(file.size());
    }
    file = root.openNextFile();
  }
}

void createDir(fs::FS &fs, const char * path){
  Serial.printf("Creating Dir: %s\n", path);
  if(fs.mkdir(path)){
    Serial.println("Dir created");
  } else {
    Serial.println("mkdir failed");
  }
}

void removeDir(fs::FS &fs, const char * path){
  Serial.printf("Removing Dir: %s\n", path);
  if(fs.rmdir(path)){
    Serial.println("Dir removed");
  } else {
    Serial.println("rmdir failed");
  }
}

String readFile(fs::FS &fs, const char *path) {
  Serial.printf("Reading file: %s\n", path);

  File file = fs.open(path);
  if (!file) {
    Serial.println("Failed to open file for reading");
    return "";
  }

  String fileContent = "";
  while (file.available()) {
    fileContent += (char)file.read();
  }
  file.close();

  return fileContent;
}

void writeFile(fs::FS &fs, const char * path, const char * message){
  Serial.printf("Writing file: %s\n", path);

  File file = fs.open(path, FILE_WRITE);
  if(!file){
    Serial.println("Failed to open file for writing");
    return;
  }
  if(file.print(message)){
    Serial.println("File written");
  } else {
    Serial.println("Write failed");
  }
  file.close();
}

void appendFile(fs::FS &fs, const char * path, const char * message){
  Serial.printf("Appending to file: %s\n", path);

  File file = fs.open(path, FILE_APPEND);
  if(!file){
    Serial.println("Failed to open file for appending");
    return;
  }
  if(file.print(message)){
      Serial.println("Message appended");
  } else {
    Serial.println("Append failed");
  }
  file.close();
}

void renameFile(fs::FS &fs, const char * path1, const char * path2){
  Serial.printf("Renaming file %s to %s\n", path1, path2);
  if (fs.rename(path1, path2)) {
    Serial.println("File renamed");
  } else {
    Serial.println("Rename failed");
  }
}

void deleteFile(fs::FS &fs, const char * path){
  Serial.printf("Deleting file: %s\n", path);
  if(fs.remove(path)){
    Serial.println("File deleted");
  } else {
    Serial.println("Delete failed");
  }
}

void testFileIO(fs::FS &fs, const char * path){
  File file = fs.open(path);
  static uint8_t buf[512];
  size_t len = 0;
  uint32_t start = millis();
  uint32_t end = start;
  if(file){
    len = file.size();
    size_t flen = len;
    start = millis();
    while(len){
      size_t toRead = len;
      if(toRead > 512){
        toRead = 512;
      }
      file.read(buf, toRead);
      len -= toRead;
    }
    end = millis() - start;
    Serial.printf("%u bytes read for %u ms\n", flen, end);
    file.close();
  } else {
    Serial.println("Failed to open file for reading");
  }


  file = fs.open(path, FILE_WRITE);
  if(!file){
    Serial.println("Failed to open file for writing");
    return;
  }

  size_t i;
  start = millis();
  for(i=0; i<2048; i++){
    file.write(buf, 512);
  }
  end = millis() - start;
  Serial.printf("%u bytes written for %u ms\n", 2048 * 512, end);
  file.close();
}

// Function to read data from I2C
void readI2CData() {
    Wire.requestFrom(I2C_ADDRESS, DATA_SIZE);
    if (Wire.available()>=4)
    {
      int16_t i2cData = Wire.read();
       String i2cDataString = String(i2cData);
      ws.textAll(i2cDataString);
      Serial.println(i2cDataString);
    }   
    
    delay(100);
}

void sendSTM(const String &input)
{
  Serial2.println(input);
  delay(100);
}
 String receiveResponse() {
  String response = "";
  int timeout = 2000;  // Set the timeout value in milliseconds

  // Wait for data to be available or until the timeout is reached
  int startTime = millis();
  while (Serial2.available() == 0 && millis() - startTime < timeout) {
    delay(1);
  }

  // If data is available, read the response
  while (Serial2.available() > 0) {
    char c = Serial2.read();
    response += c;
  }

  return response;
}
void readSTM()
{
  int startTime = millis();
  while (Serial2.available() == 0 && millis() - startTime < 2000)
  {
    delay(1);
  }
  while (Serial2.available() > 0)
  {
    char receivedChar = Serial2.read();
    float sensorReading = receivedChar - '0';
    // Create a JSON message with the sensor reading
    DynamicJsonDocument doc(1024); // buffer
    doc["reading"] = sensorReading;
    // Serialize the JSON document to a string
    String jsonString;
    serializeJson(doc, jsonString);
    // Send the message to all WebSocket clients
    ws.textAll(jsonString.c_str());
  }
}
String sendCMD(const String &input)
{
  // Send the command to the STM32 via UART
  Serial2.println(input);
  Serial.println(input);
  Serial.println("sent command");
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
// Flag to indicate when to perform the scan
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
    else if (doc.containsKey("username"))
    {
      if (doc["username"].as<String>()=="nabil" && doc["password"].as<String>()=="123"){
        notifyClients("rightpass");
        Serial.println("Success");
      }else{notifyClients("wrongpass");}
    }
    else if (strcmp((char*)data, "command1\n") == 0 ||
             strcmp((char*)data, "command2\n") == 0 ||
             strcmp((char*)data, "command3\n") == 0 ||
             strcmp((char*)data, "command4\n") == 0 ||
             strcmp((char*)data, "command5\n") == 0 ||
             strcmp((char*)data, "command6\n") == 0) {
      sendCMD((char*)data);
      readSTM();
      
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
          sendSTM(String(wavelengthValue));
          delay(100);
          String scanData = String("{\"wavelength\":") + String(wavelengthValue);
          delay(100);
          scanData = scanData + String(",\"intensitySample\":") + sendCMD("sample");
          delay(100);
          scanData = scanData +  String(",\"intensity0\":") + sendCMD("reference") + String("}");
        
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
      else if (command == "sd")
      {
         content=readFile(SD, "/foo.txt");
         notifyClients(content);

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
void sdinit(){
  if(!SD.begin(5)){
    Serial.println("Card Mount Failed");
    return;
  }
  uint8_t cardType = SD.cardType();

  if(cardType == CARD_NONE){
    Serial.println("No SD card attached");
    return;
  }

  Serial.print("SD Card Type: ");
  if(cardType == CARD_MMC){
    Serial.println("MMC");
  } else if(cardType == CARD_SD){
    Serial.println("SDSC");
  } else if(cardType == CARD_SDHC){
    Serial.println("SDHC");
  } else {
    Serial.println("UNKNOWN");
  }

  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);

}


void sendFileToClient(AsyncWebSocketClient *client) {
  // Replace "file.txt" with the path to your file on the SD card
  File file = SD.open("/file.txt");
  
  if (!file) {
    Serial.println("Failed to open file");
    return;
  }

  while (file.available()) {
    size_t bytesRead = file.readBytes(fileBuffer, sizeof(fileBuffer));
    client->binary(fileBuffer, bytesRead);
  }

  file.close();

  // Notify the client that the file transfer is complete
  client->text("fileSent");
}

void setup()
{
    Wire.begin(); // GPIO21 for SDA and GPIO22 for SCL

  // Serial port for debugging purposes
  Serial.begin(115200);
  Serial2.begin(115200);
  // Initialize access point and SPIFFS
  initSPIFFS();
  initAP();
  initWebSocket();
  sdinit();
  /*
 listDir(SD, "/", 0);
  createDir(SD, "/mydir");
  listDir(SD, "/", 0);
  removeDir(SD, "/mydir");
  listDir(SD, "/", 2);
  writeFile(SD, "/hello.txt", "Hello ");
  appendFile(SD, "/hello.txt", "World!\n");
  readFile(SD, "/hello.txt");
  deleteFile(SD, "/foo.txt");
  renameFile(SD, "/hello.txt", "/foo.txt");
  readFile(SD, "/foo.txt");
  testFileIO(SD, "/test.txt");
  */
Serial.printf("Total space: %lluMB\n", SD.totalBytes() / (1024 * 1024));
Serial.printf("Used space: %lluMB\n", SD.usedBytes() / (1024 * 1024));
   
   
  server.on("/upload", HTTP_POST, [](AsyncWebServerRequest *request){
    request->send(200);
  },[](AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final){
    if (!index) {
      Serial.printf("Receiving file: %s\n", filename.c_str());
      fsUploadFile = SD.open("/" + filename, FILE_WRITE);
      startTime = millis();
    }
    if (fsUploadFile) {
      fsUploadFile.write(data, len);
    }
    if (final) {
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

  AsyncElegantOTA.begin(&server);    // Start ElegantOTA
  // Start the server
  server.begin();
}

void loop()
{
  // Check for new WebSocket messages
  ws.cleanupClients();

  delay(1000); // Delay before sending the next command
}