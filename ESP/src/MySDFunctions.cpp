#include "MySDFunctions.h"

bool writeToDatabase(const char *basePath, const DynamicJsonDocument &doc) {
    String filename = String(basePath) + "/" + doc["name"].as<String>() + ".txt";
    File file = SD.open(filename, FILE_APPEND);
    if (file) {
        serializeJson(doc, file);
        file.println();
        file.close();
        return true;
    } else {
        Serial.println("Error opening file");
        return false;
    }
}

DynamicJsonDocument readFromDatabase(const char *filename) {
    DynamicJsonDocument doc(1024);
    File file = SD.open(filename);
    if (file) {
     
        if (deserializeJson(doc, file)) {
        } else {
            Serial.println("Failed to parse JSON from txt");
        }
        file.close();
    } else {
        Serial.println("Error opening file");
    }
    return doc;
}


JsonObject getFilesJson(const char *directory) {
    StaticJsonDocument<2048> doc;
    File dir = SD.open(directory);
    int count = 1;
    while (File file = dir.openNextFile()) {
        if (!file.isDirectory()) {
            String fileName = file.name();
            fileName.replace(".txt", "");
            doc["presets"] = "presets";
            doc["file" + String(count++)] = fileName;
        }
    }
    if (strcmp(directory, "/presets") == 0) {
        doc["presetsno"] = count - 1;
    }
    else if (strcmp(directory, "/readings") == 0) {
        doc["readingsno"] = count - 1;
    }
    dir.close();
    return doc.as<JsonObject>();
}
