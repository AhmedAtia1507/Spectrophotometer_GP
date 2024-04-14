#ifndef MY_SD_FUNCTIONS_H
#define MY_SD_FUNCTIONS_H

#include <ArduinoJson.h>
#include <SD.h>

bool writeToDatabase(const char *basePath, const DynamicJsonDocument &doc);
DynamicJsonDocument readFromDatabase(const char* filename);
//bool writeToDatabase2(const char *basePath, String &message,const DynamicJsonDocument &doc);
DynamicJsonDocument getFilesJson(const char *directory);
void readFromDatabase2(const DynamicJsonDocument &doc);
//void handleread(const DynamicJsonDocument &doc)
//bool deleteLineFromFile(const char* filename, const char* searchName);

#endif  // MY_SD_FUNCTIONS_H
