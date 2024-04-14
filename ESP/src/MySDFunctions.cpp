#include "HandleMessage.h"
#include "MyInitialization.h"
#include "MySDFunctions.h"

bool writeToDatabase(const char *basePath, const DynamicJsonDocument &doc) {
    String filename = String(basePath)+ doc["name"].as<String>()+" === " +doc["time"].as<String>()+ ".txt";
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
DynamicJsonDocument getFilesJson(const char *directory) {
    DynamicJsonDocument doc(2048);
    File dir = SD.open(directory);
    int count = 1;
    while (File file = dir.openNextFile()) {
        if (!file.isDirectory()) {
            String fileName = file.name();
            fileName.replace(".txt", "");
            doc["presets"] = "presets";
            doc["file" + String(count++)] = fileName;
            file.close();
        }
    }
    if (strcmp(directory, "/presets") == 0) {
        doc["presetno"] = count - 1;
    }
    else if (strcmp(directory, "/readings") == 0) {
        doc["readingsno"] = count - 1;
    }
    dir.close();
    return doc;
}


TaskHandle_t readTask;
void handlereadTask(void *pvParameters){
 DynamicJsonDocument doc = *((DynamicJsonDocument *)pvParameters);
 String selectthis = doc["loadthis"].as<String>();
 String path="";
 path = "/readings/" + selectthis + ".txt";
Serial.print(path+"\n");
String jsonString;
    // Open the file for reading
    File file = SD.open(path);
    if (!file) {
        Serial.println("Failed to open file for reading");
    }
    // Read the file line by line
    while (file.available()) {
        Serial.println("open file for reading");
        // Read a line from the file
        String line = file.readStringUntil('\n');
        line.trim();
        notifyClients(line);
        delay(100);

    }
    // Close the file
    file.close();
    vTaskDelete(NULL);
}

void handleread(const DynamicJsonDocument &doc) {
   Serial.print("ana fel taaaaaaask\n");
   DynamicJsonDocument *docCopy = new DynamicJsonDocument(doc.capacity());
    *docCopy = doc;
  
  xTaskCreatePinnedToCore(
      handlereadTask,       // Task function
      "readfromsd",         // Task name
      8192,                 // Stack size (bytes)
      (void *)docCopy,       // Parameter to pass to the task
      1,                    // Task priority
      &readTask,            // Task handle
      0);                   // Core (0 or 1, depending on your setup)
}
void readFromDatabase2(const DynamicJsonDocument &doc) { 
    handleread(doc);
    }


// bool writeToDatabase2(const char *basePath,String &message,const DynamicJsonDocument &doc) {
//     String filename = String(basePath)+ doc["name"].as<String>()+" === "+doc["time"].as<String>() + ".txt";
//     File file = SD.open(filename, FILE_APPEND);
//     if (file&&doc["isFirst"].as<String>()=="true") {
//         serializeJson(doc, file);
//         file.println();
//         file.close();
//         return true;
    
//     } 
//     else if(file&&doc["isFirst"].as<String>()=="false"){
//         String readings=doc["readings"].as<String>();
//         file.println(readings);
//         file.close();
//         return true;
    
//     }
    
//     else {
//         Serial.println("Error opening file");
//         return false;
//     }
// }




// JsonObject getFilesJson(const char* filename) {
//     // Create a JSON object to hold the names
//     DynamicJsonDocument doc(1024);
//     JsonObject files = doc.to<JsonObject>();

//     // Open the file for reading
//     File file = SD.open(filename);
    
//     if (!file) {
//         Serial.println("Failed to load presets");
//         return files; // Return an empty object if file opening failed
//     }
    
//     // Variable to hold the count of files
//     int fileNumber = 1;
    
//     // Read the file line by line
//     while (file.available()) {
//         // Read a line from the file
//         String line = file.readStringUntil('\n');
        
//         // Create a JSON document to hold the data from the line
//         DynamicJsonDocument lineDoc(1024);
        
//         // Deserialize the JSON data from the line
//         DeserializationError error = deserializeJson(lineDoc, line);
        
//         // Check if deserialization was successful and the line contains the "name" field
//         if (!error && lineDoc.containsKey("name")) {
//             // Extract the name value
//             String name = lineDoc["name"].as<String>();
//             String time = lineDoc["time"].as<String>();
//             // Construct the key for the file number
//             String key = "file" + String(fileNumber);
//             String key2 = "time" + String(fileNumber);
            
//             // Add the name to the files object with the key
//             files[key]=name;
//             files[key2]=time;
            
//             // Increment the file number
//             fileNumber++;
//         }
//     }
    
//     // Close the file
//     file.close();
//     if(filename=="/presets/presets.txt"){
//     // Add the count of files as a field to the files object
//     files["presetno"] = fileNumber - 1;
//     }
//     else if(filename=="/readings/readings.txt"){
//     // Add the count of files as a field to the files object
//     files["readingsno"] = fileNumber - 1;
//     }
//     // Return the JsonObject containing the files
//     return files;
// }

// bool deleteLineFromFile(const char* filename, const char* searchName) {
//     // Temporary file to hold modified content
//     File tempFile = SD.open("/presets/temp.txt", FILE_WRITE);
//     if (!tempFile) {
//         Serial.println("Failed to create temp file");
//         return false;
//     }

//     // Open the original file for reading
//     File file = SD.open(filename);
//     if (!file) {
//         Serial.println("Failed to open file for reading");
//         tempFile.close();
//         return false;
//     }

//     // Read the file line by line and copy to temp file except the line containing the specified name
//     while (file.available()) {
//         String line = file.readStringUntil('\n');
//         line.trim();
//         DynamicJsonDocument doc(1024);
//         DeserializationError error = deserializeJson(doc, line);

//         // Check if deserialization was successful and the line contains the specified name
//           if (!error && doc.containsKey("name") && doc["name"] == searchName||doc["name"].as<String>()+doc["time"].as<String>() == searchName) {
//            // Skip this line
//             continue;
//         }

//         // Write the line to the temp file
//         tempFile.println(line);
//     }

//     // Close both files
//     file.close();
//     tempFile.close();

//     // Remove the original file
//     SD.remove(filename);

//     // Rename the temp file to original filename
//     if (!SD.rename("/presets/temp.txt", filename)) {
//         Serial.println("Failed to rename temp file");
//         return false;
//     }

//     return true;
// }


