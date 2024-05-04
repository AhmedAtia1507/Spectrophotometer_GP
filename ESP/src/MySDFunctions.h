#ifndef MY_SD_FUNCTIONS_H
#define MY_SD_FUNCTIONS_H

#include <ArduinoJson.h>
#include <SD.h>

bool writeToDatabase(const char *basePath, const DynamicJsonDocument &doc);
DynamicJsonDocument readFromDatabase(const char* filename);
bool CsvWriteToSd(String &filename,String &content);
DynamicJsonDocument getFilesJson(const char *directory);
void readFromDatabase2(const DynamicJsonDocument &doc);
String jsonToCsv(const DynamicJsonDocument& doc, int numKeys);
String csvToJsonString(const String& csvLine);

//void handleread(const DynamicJsonDocument &doc)
//bool deleteLineFromFile(const char* filename, const char* searchName);

#endif  // MY_SD_FUNCTIONS_H
