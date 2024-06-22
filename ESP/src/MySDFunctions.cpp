#include "HandleMessage.h"
#include "MyInitialization.h"
#include "MySDFunctions.h"
#include <ArduinoJson.h>
//this function writes any string into a file name at any format
bool SdWriteString(String &filename,String &content) {
    File file = SD.open(filename, FILE_APPEND);
    if (file) {
        file.println(content);
        file.close();
        return true;
    } else {
        Serial.println("Error opening file");
        return false;
    }
}

bool deleteLineFromFile(String filename, String searchName) {
    // Temporary file to hold modified content
    File tempFile = SD.open("/temp.txt", FILE_WRITE);
    if (!tempFile) {
        Serial.println("Failed to create temp file");
        return false;
    }

    // Open the original file for reading
    File file = SD.open(filename);
    if (!file) {
        Serial.println("Failed to open file for reading");
        tempFile.close();
        return false;
    }

    // Read the file line by line and copy to temp file except the line containing the specified name
    while (file.available()) {
        String line = file.readStringUntil('\n');
        line.trim();
        // Check if deserialization was successful and the line contains the specified name
          if (line== searchName) {
           // Skip this line
            continue;
            }

        // Write the line to the temp file
        tempFile.println(line);
    }
    // Close both files
    file.close();
    tempFile.close();
    // Remove the original file
    SD.remove(filename);
    // Rename the temp file to original filename
    if (!SD.rename("/temp.txt", filename)) {
        Serial.println("Failed to rename temp file");
        return false;
    }
    return true;
}

