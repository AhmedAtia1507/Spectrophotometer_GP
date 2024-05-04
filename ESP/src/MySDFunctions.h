#ifndef MY_SD_FUNCTIONS_H
#define MY_SD_FUNCTIONS_H

#include <ArduinoJson.h>
#include <SD.h>

bool writeToDatabase(const char *basePath, const DynamicJsonDocument &doc);
DynamicJsonDocument readFromDatabase(const char* filename);
bool SdWriteString(String &filename,String &content);
String createJsonString(String key, String value);
String createJsonString(String key, int value) ;
DynamicJsonDocument getFilesJson(const char *directory);
void ReadFromDBTask(const DynamicJsonDocument &doc);
String WriteAsCsv(const DynamicJsonDocument& doc, int numKeys);
String csvToJsonString(const String& csvLine);
bool deleteLineFromFile(String filename, String searchName);

//void handleread(const DynamicJsonDocument &doc)
//bool deleteLineFromFile(const char* filename, const char* searchName);

#endif  // MY_SD_FUNCTIONS_H
