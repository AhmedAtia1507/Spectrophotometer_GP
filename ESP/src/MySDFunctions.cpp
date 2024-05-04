#include "HandleMessage.h"
#include "MyInitialization.h"
#include "MySDFunctions.h"
#include <ArduinoJson.h>

// Define a global flag variable
volatile bool stopTaskFlag = false; //to stop the task from webpage
// Define a global flag variable for pausing
volatile bool pauseTaskFlag = false; //to pause the task from webpage
// Function to stop the task
void stopTask() {
    stopTaskFlag = true;
}
// Function to pause the task
void pauseTask() {
    pauseTaskFlag = true;
}

// Function to resume the task
void resumeTask() {
    pauseTaskFlag = false;
}




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

// DynamicJsonDocument getFilesJson(const char *directory) {
//     // Create a JSON document to store the file information
//     DynamicJsonDocument doc(3048);

//     // Open the directory
//     File dir = SD.open(directory);

//     // Check if the directory is open
//     if (!dir) {
//         Serial.println("Failed to open directory");
//         return doc; // Return an empty document
//     }

//     // Initialize a counter for the files
//     int count = 1;

//     // Iterate over the files in the directory
// while (true) {
//     File file = dir.openNextFile();
    
//     // Print the result of opening the next file
//     Serial.print("File opened: ");
//     Serial.println(file ? "success" : "failed");
    
//     if (!file) {
//         // If no more files can be opened, break out of the loop
//         break;
//     }

//     // Get the file name
//     String fileName = file.name();

//     // Remove the ".txt" extension from the file name
//     fileName.replace(".txt", "");

//     // Store the file name in the JSON document
//     doc["file" + String(count++)] = fileName;

//     // Close the file
//     file.close();
// }

//     // Close the directory
//     dir.close();

//     // Add the total number of files to the JSON document
//     if (strcmp(directory, "/presets") == 0) {
//         doc["presetno"] = count - 1;
//     } else if (strcmp(directory, "/readings") == 0) {
//         doc["readingsno"] = count - 1;
//     }
//     Serial.println(count);

//     // Return the JSON document
//     return doc;
// }


// Function to handle sending file names in chunks
void sendFileNamesTask(void *parameter) {
    String directory = *((String *)parameter);

    // Open the directory
    File dir = SD.open(directory);

    // Check if the directory is open
    if (!dir) {
        Serial.println("Failed to open directory");
        vTaskDelete(NULL);
    }

    // Initialize a counter for the files
    int count = 1;
    String fileNamesJSON = "{"; // Start JSON object

    // Iterate over the files in the directory
    bool allFilesProcessed = false;
while (!allFilesProcessed) {
        
for (int i = 0; i <15; i++) {
    File file = dir.openNextFile();
        // Check if a file can be opened
        if (!file) {
           allFilesProcessed = true;         
            // If no more files can be opened, break out of the loop
            break;
        }

        // Get the file name
        String fileName = file.name();

        // Remove the ".txt" extension from the file name
        fileName.replace(".txt", "");

        // Add the file name to the JSON object
        fileNamesJSON += "\"file" + String(count++) + "\": \"" + fileName + "\",";

        // Close the file
        file.close();
      
}

  // Remove the trailing comma
        fileNamesJSON.remove(fileNamesJSON.length() - 1);

        // Add the total number of files to the JSON object
        if(directory=="/readings"){
        fileNamesJSON += ",\"readingsno\": " + String(count - 1)+ "}"+"\n";        
         }
        else if(directory=="/presets"){
        fileNamesJSON += ",\"presetno\": " + String(count - 1)+ "}"+"\n";        
        }
    
    
    // Notify all clients with the JSON object
     //Serial.println(fileNamesJSON);
    notifyClients(fileNamesJSON);
    fileNamesJSON = "{";
    count=1;
    }

    // Close the directory
    dir.close();

    
    // Delete the task when done
    vTaskDelete(NULL);
}

// Function to get file names in JSON format
DynamicJsonDocument getFilesJson(const char *directory) {
    // Create a JSON document to store the file information
    DynamicJsonDocument doc(3048);

    // Create a task to send file names
    xTaskCreatePinnedToCore(
        sendFileNamesTask,        // Task function
        "sendFileNamesTask",     // Task name
        4096,                    // Stack size (bytes)
        (void *)new String(directory),  // Parameter to pass to the task
        1,                       // Task priority
        NULL,                    // Task handle (not used here)
        0                        // Core (0 or 1, depending on your setup)
    );

    // Return the empty JSON document
    return doc;
}


TaskHandle_t readTask;

void handlereadTask(void *pvParameters){
    DynamicJsonDocument doc = *((DynamicJsonDocument *)pvParameters);
    String selectthis = doc["loadthis"].as<String>();
    String path = "/readings/" + selectthis + ".txt";
    Serial.print(path + "\n");
    String jsonString;

    // Open the file for reading
    File file = SD.open(path);
    if (!file) {
        Serial.println("Failed to open file for reading");
    }

    // Read the file in chunks of 50 lines
    while (file.available()) {
        // Check if the pause flag is set
        while (pauseTaskFlag) {
            vTaskDelay(pdMS_TO_TICKS(120)); // Delay to reduce CPU load
        }

        if (stopTaskFlag) {
            stopTaskFlag = false;
            // Break out of the loop to stop the task
            break;
        }

        // Read 50 lines from the file
        String linesToSend;
        for (int i = 0; i <500 && file.available(); i++) {
            String line = file.readStringUntil('\n');
            line.trim();
            linesToSend += line + "\n";
        }

        // Send the chunk of lines to the clients
        notifyClients(linesToSend);

        // Delay or yield to allow other tasks to run
        vTaskDelay(pdMS_TO_TICKS(80)); // Example delay of 80 ms
    }

    // Send a message when finished to tell the webpage that loading reading is finished
    DynamicJsonDocument lastmessage(1024);
    lastmessage["isFirst"] = "last";
    lastmessage["readings"] = "";
    lastmessage["time"] = "";
    String message = "";
    serializeJson(lastmessage, message);
    notifyClients(message);

    // Close the file
    file.close();
    stopTaskFlag = false;
    pauseTaskFlag = false;
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



String jsonToCsv(const DynamicJsonDocument& doc, int numKeys) {
    String csv = "";

    // Iterate over the keys in the JSON document
    for (int i = 0; i < numKeys; i++) {
        // Get the value as a string
        const char* value = doc[i].as<const char*>();
        // Append the value to the CSV string
        csv += value;

        // If it's not the last key, add a comma
        if (i < numKeys - 1) {
            csv += ",";
        }
    }

    return csv;
}


// void handlereadTask(void *pvParameters){
//  DynamicJsonDocument doc = *((DynamicJsonDocument *)pvParameters);
//  String selectthis = doc["loadthis"].as<String>();
//  String path="";
//  path = "/readings/" + selectthis + ".txt";
// Serial.print(path+"\n");
// String jsonString;
//     // Open the file for reading
//     File file = SD.open(path);
//     if (!file) {
//         Serial.println("Failed to open file for reading");
//     }
//     // Read the file line by line
//     while (file.available()) {
//         // Check if the pause flag is set
//         while (pauseTaskFlag) {
//             vTaskDelay(pdMS_TO_TICKS(120)); // Delay to reduce CPU load
//         }
//         if (stopTaskFlag) {
//             stopTaskFlag = false;
//             // Break out of the loop to stop the task
//             break;
//         }

//         Serial.println("open file for reading");
//         // Read a line from the file
//         String line = file.readStringUntil('\n');
//         line.trim();
//         notifyClients(line);
//         // Delay or yield to allow other tasks to run
//         vTaskDelay(pdMS_TO_TICKS(80)); // Example delay of 80 ms

//     }
//     //send a message when finished to tell the webpage that loading reading is finished
//     DynamicJsonDocument lastmessage(1024);
//     lastmessage["isFirst"]="last";
//     lastmessage["readings"]="";
//     lastmessage["time"]="";
//     String message="";
//     serializeJson(lastmessage, message);
//     notifyClients(message);
//     // Close the file
//     file.close();
//     stopTaskFlag=false;
//     pauseTaskFlag=false;
//     vTaskDelete(NULL);
// }


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


