#ifndef MY_SD_FUNCTIONS_H
#define MY_SD_FUNCTIONS_H

#include <ArduinoJson.h>
#include <SD.h>
bool SdWriteString(String &filename,String &content);
bool deleteLineFromFile(String filename, String searchName);


//void handleread(const DynamicJsonDocument &doc)
//bool deleteLineFromFile(const char* filename, const char* searchName);

#endif  // MY_SD_FUNCTIONS_H
