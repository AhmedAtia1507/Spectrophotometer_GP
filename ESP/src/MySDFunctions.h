#ifndef MY_SD_FUNCTIONS_H
#define MY_SD_FUNCTIONS_H

#include <ArduinoJson.h>
#include <SD.h>

bool writeToDatabase(const char *basePath, const DynamicJsonDocument &doc);
DynamicJsonDocument readFromDatabase(const char *filename);
JsonObject getFilesJson(const char *directory);

#endif  // MY_SD_FUNCTIONS_H
