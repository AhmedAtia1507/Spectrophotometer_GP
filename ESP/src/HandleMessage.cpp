#include "HandleMessage.h"
#include "MyInitialization.h"
#include "MySDFunctions.h"
//
const unsigned long interval = 600000; // 10 minutes in milliseconds works as a session for the control page
unsigned long previousMillis;
bool loginflag = false; // to check if the user logged in before accessing the control page
bool StopScan = false;
void startCountdown()
{
  // Call this function to start the countdown
  previousMillis = millis(); // Initialize the timer when starting to count
}

void checkCountdown()
{
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval)
  {
    // Time has passed, reset the timer and update loginFlag
    previousMillis = currentMillis;
    loginflag = false;
  }
}

// Define a task handle
TaskHandle_t cmdTask;
// Function to handle sending commands to STM32
void sendCMDTask(void *parameter)
{
  DynamicJsonDocument *doc = (DynamicJsonDocument *)parameter;
  String input = (*doc)["input"].as<String>();
  String response = "";

  // Send the command to the STM32 via UART if UART is connected
  Serial2.println(input);
  Serial.println(input);
  
  int startTime = millis();
  while (Serial2.available() && millis() - startTime < 2000)
{
response = Serial2.readStringUntil('\n');
Serial.println("Response received: " + response);
}
  // Store the response in the task parameters
  (*doc)["response"] = response;

  // Delete the task when done
  vTaskDelete(NULL);
}

// Function to send a command to STM32 and get the response
String sendCMD(const String &input)
{
  // Create a JSON document to store the input and response
  DynamicJsonDocument *doc = new DynamicJsonDocument(1024);
  (*doc)["input"] = input;

  // Create the task to send the command
  xTaskCreatePinnedToCore(
      sendCMDTask,    // Task function
      "sendCMDTask",  // Task name
      4096,           // Stack size (bytes)
      (void *)doc,    // Parameter to pass to the task
      1,              // Task priority
      &cmdTask,       // Task handle
      1               // Core (0 or 1, depending on your setup)
  );

  // Wait for the task to complete
  while (eTaskGetState(cmdTask) != eDeleted) {
    vTaskDelay(pdMS_TO_TICKS(1)); // Delay to yield to the task
  }

  // Get the response and clean up
  String response = (*doc)["response"].as<String>();
  delete doc;

  // Return the response string
  return response;
}

void handleSB(const DynamicJsonDocument &doc)
{
  String tempArr[] = {"get-UV", "get-VI", "get-WL"};
  String resArr[] = {"UV", "VI", "WL"};
  DynamicJsonDocument SBDATA(256);
  for (size_t i = 0; i < 2; i++)
  {
    Serial2.println(tempArr[i]);
    int startTime = millis();
    while (Serial2.available() == 0 && millis() - startTime < 2000)
    {
      delay(1);
    }
    String response = Serial2.readStringUntil('\n');
    SBDATA[resArr[i]] = response;
  }

  String jsonString;
  serializeJson(SBDATA, jsonString);
  notifyClients(jsonString);
  Serial.println("State Bar data sent");
}

void sendLoginSuccessNotification()
{
  DynamicJsonDocument pass(1024);
  pass["username"] = true;
  pass["password"] = true;
  String jsonString;
  loginflag = true;
  startCountdown();
  serializeJson(pass, jsonString);
  notifyClients(jsonString);
  Serial.println(jsonString);
}

void sendLoginFailureNotification()
{
  DynamicJsonDocument pass(1024);
  pass["username"] = false;
  pass["password"] = false;
  String jsonString;
  serializeJson(pass, jsonString);
  notifyClients(jsonString);
}

void sendFlagStatus()
{
  DynamicJsonDocument object(29);
  object["flag"] = loginflag;
  checkCountdown();
  String jsonString;
  serializeJson(object, jsonString);
  notifyClients(jsonString);
}

void handleLampStatus(const String &lampType)
{
  String command = String("get-" + lampType);
  String status = sendCMD(command);
  // String status = "on";
  String jsonString;
  DynamicJsonDocument object(50);
  String condition = lampType + "stutus";
  Serial.print(condition);
  object[condition] = status;
  serializeJson(object, jsonString);
  notifyClients(jsonString);
}

void handleLampControl(const String &lampType, bool turnOn)
{
  String command = turnOn ? "set-" + lampType + "-on" : "set-" + lampType + "-off";
  String status = sendCMD(command);
  delay(80);
  handleLampStatus(lampType);
}

// void handleShowPresets(const char *directory)
// {
//   getFilesJson(directory);
//   //   String jsonString;
//   //  serializeJson(result, jsonString);
//   // notifyClients(jsonString);
// }

void handleLoadPreset(const DynamicJsonDocument &doc)
{
  String selectthis = doc["loadthis"].as<String>();
  String path = "";
  DynamicJsonDocument preset(1024);
  if (doc["Dictionary"] == "readings")
  {
    // path = "/readings/" + selectthis + ".csv";
    ReadFromDBTask(doc);
  }

  else if (doc["Dictionary"] == "presets")
  {
    path = "/presets/" + selectthis + ".txt";
    String jsonString;
    preset = readFromDatabase(path.c_str());
    preset["loaded"] = "loaded";
    serializeJson(preset, jsonString);
    notifyClients(jsonString);
  }
}

void handleSupplyStatus()
{
  String stutus = sendCMD("get-voltages");
  // String stutus="12 2 2 2 13";
  DynamicJsonDocument object(1024);
  object["supplystutus"] = "good";
  object["voltages"] = stutus;
  String jsonString;
  serializeJson(object, jsonString);
  notifyClients(jsonString);
}

void loadtime()
{
  String response = sendCMD("get-time");
  // String response = "1/13/2024 13:32:12\n";
  DynamicJsonDocument object(200);
  object["currenttime"] = response;
  String jsonString;
  serializeJson(object, jsonString);
  notifyClients(jsonString);
}

/**
 * @brief saves the time to the stm
 *
 * @param doc the json document containing the time to be saved
 */
void savetime(const DynamicJsonDocument &doc)
{
  String command = doc["updatetime"].as<String>();
  Serial.print(command);
  String respnse = sendCMD("set-time-" + command);
  // String respnse = "success";
  DynamicJsonDocument object(29);
  object["timeupdated"] = respnse;
  String jsonString;
  serializeJson(object, jsonString);
  notifyClients(jsonString);
}
void sendsteps()
{
  String command = "get-motors-steps";
  String response = sendCMD(command);
  // String response = "30-40-50-1100\n";
  DynamicJsonDocument object(60);
  object["motorssteps"] = response;
  String jsonString;
  serializeJson(object, jsonString);
  notifyClients(jsonString);
}
void getlampmoter()
{
  String command = "get-lamp-moter-position";
  String response = sendCMD(command);
  // String response = "VI Lamp";
  // Serial.print(response);
  DynamicJsonDocument object(60);
  object["currenlamp"] = response;
  String jsonString;
  serializeJson(object, jsonString);
  notifyClients(jsonString);
}
void ToggleLampMotor(const DynamicJsonDocument &doc)
{
  String setto = doc["Lampmotortoggle"].as<String>();
  String command = "set-lamp-moter-" + setto;
  String response = sendCMD(command);
  // String response = "moved";
  DynamicJsonDocument object(90);
  object["motermoved"] = response;
  String jsonString;
  serializeJson(object, jsonString);
  notifyClients(jsonString);
}
void handleGoHome(const DynamicJsonDocument &doc)
{
  String motortype = doc["type"].as<String>(); // like set-lamp-moter-home
  String command = motortype;
  String response = sendCMD(command);
  delay(80);
  String wavelength = sendCMD("get-current-wav");
  // String response = "0";
  // String wavelength = "878";
  DynamicJsonDocument object(90);
  object["gohome"] = "gone";
  object["step"] = response;
  object["type"] = motortype;
  object["wavelength"] = wavelength;
  String jsonString;
  serializeJson(object, jsonString);
  notifyClients(jsonString);
}

void handleSavestep(const DynamicJsonDocument &doc)
{
  String correctstep = doc["savethis"].as<String>();
  String correctwave = doc["wavelength"].as<String>();
  String response = sendCMD(correctstep);
  delay(80);
  String wavelength = sendCMD(correctwave);
  // String response = "saved";
  // String wavelength = "878";
  DynamicJsonDocument object(90);
  object["stepsaved"] = response;
  String jsonString;
  serializeJson(object, jsonString);
  notifyClients(jsonString);
}
void handlemovestep(const DynamicJsonDocument &doc)
{
  String correctstep = doc["movemoter"].as<String>(); // like set-gratingmoter-to-WL-100
  String response = sendCMD(correctstep);
  // String response = "moved";
  DynamicJsonDocument object(90);
  object["motermoved"] = response;
  String jsonString;
  serializeJson(object, jsonString);
  notifyClients(jsonString);
  delay(80);
  sendsteps();
}
void handelreaddetecor()
{
  String response = sendCMD("get-det-readings");
  // String response = "12-122-22-260-17-18";
  DynamicJsonDocument object(90);
  object["detreadings"] = response;
  String jsonString;
  serializeJson(object, jsonString);
  notifyClients(jsonString);
}
void handlenewgain(const DynamicJsonDocument &doc)
{
  String newgain = doc["newgain"].as<String>();
  String gainType = doc["gaintype"].as<String>();
  String command = "set-" + gainType + "-newgain-to-" + newgain;
  String response = sendCMD(command);
  // String response = "applied";
  if (response == "applied")
  {
    delay(80);
    handelreaddetecor();
  }
  // else{handlenewgain(doc);}
}

void handleDirectCommand(const DynamicJsonDocument &doc)
{
  String command = doc["DirectCommand"].as<String>();
  String response = sendCMD(command);
  // String response=command;
  DynamicJsonDocument object(90);
  object["DirectResponse"] = response;
  String jsonString;
  serializeJson(object, jsonString);
  notifyClients(jsonString);
}

/**------------------------------------------------------------------------
 *                           SCAN TASK
 *------------------------------------------------------------------------**/
TaskHandle_t scanTask;
// TASK
void handleScanTask(void *pvParameters)
{
  DynamicJsonDocument doc = *((DynamicJsonDocument *)pvParameters);

  String command = doc["command"].as<String>();
  String startInput = doc["startInput"].as<String>();
  String stopInput = doc["stopInput"].as<String>();
  String stepInput = doc["stepInput"].as<String>();
  String lampmode = doc["lampmode"].as<String>();
  
  float current = (stopInput.toInt() - startInput.toInt()) / stepInput.toInt();
  int j = 1; // represent the current iteration
  bool scanning = true;
  DynamicJsonDocument scanData(256);

  if (command == "Scan")
  {
    String scancmd = command + " "+lampmode+" "+ startInput + " " + stopInput + " " + stepInput;
    Serial.println(scancmd);
    Serial2.println(scancmd);

    // float x[]={250, 251, 252, 253, 254, 255, 256, 257, 258, 259, 260, 261, 262, 263, 264, 265, 266, 267, 268, 269, 270, 271, 272, 273, 274, 275, 276, 277, 278, 279, 280, 281, 282, 283, 284, 285, 286, 287, 288, 289, 290, 291, 292, 293, 294, 295, 296, 297, 298, 299, 300};
    // float y[]={0.79345, 0.75808, 0.72395, 0.69756, 0.67347, 0.65129, 0.62944, 0.60936, 0.59192, 0.58464, 0.56991, 0.556, 0.53878, 0.50347, 0.48214, 0.46173, 0.44379, 0.42682, 0.41183, 0.39886, 0.38637, 0.37066, 0.3595, 0.35018, 0.34142, 0.33042, 0.32363, 0.32548, 0.40237, 0.39305, 0.28955, 0.26148, 0.24206, 0.23069, 0.22278, 0.22248, 0.28155, 0.32932, 0.24429, 0.25164, 0.22734, 0.1903, 0.18143, 0.17317, 0.1626, 0.15239, 0.14342, 0.13418, 0.12678, 0.11987};

    // for (int i = startInput.toInt(); i <= stopInput.toInt(); i += stepInput.toInt())
    for (int i = stopInput.toInt(); i >= startInput.toInt(); i -= stepInput.toInt())
    {
      vTaskDelay(pdMS_TO_TICKS(100));
        if (StopScan) {
            StopScan = false;
            // Break out of the loop to stop the task
            break;
        }

      int startTime = millis();
      while (Serial2.available() == 0 && millis() - startTime < 2000)
      {
        delay(1);
      }
      // String response = Serial2.readStringUntil('\n');
    // Generate random numbers in the range 1 to 1000
    int num1 = rand() % 1000 + 1;
    int num2 = rand() % 1000 + 1;
    int num3 = rand() % 1000 + 1;
      
       // Create the response string
    String response = "23/3||1:30 ";
    response += String(num1) + " " + String(num2) + " " + String(num3);
    Serial.println(response); // debug

      // Split the response into components
      int space1 = response.indexOf(' ');
      int space2 = response.indexOf(' ', space1 + 1);
      int space3 = response.indexOf(' ', space2 + 1);

      String Time = response.substring(0, space1);
//      String wavelength = response.substring(space1 + 1, space2);
      String wavelength= String(i);
      String reference = response.substring(space2 + 1, space3);
      String sample = response.substring(space3 + 1);
      if (scanning)
      {
        float ratio= 0 ;
        if(j-1 != 0){        // first iteration make ratio = 0
        ratio = 100 / current * (j-1);
        }
        scanData["current"] = ratio; // to help display the % progress
      }
   
      scanData["currentTime"] = Time;
      scanData["wavelength"] = wavelength;
      scanData["intensityReference"] = reference.toFloat();
      scanData["intensitySample"] = sample.toFloat();
      scanData["scanning"] = scanning;

      j++;
      
      if (startInput==stopInput)
      {
        scanData["current"] = 100; // to help display the % progress
      }
      
      String jsonString;
      serializeJson(scanData, jsonString);
      notifyClients(jsonString);
      Serial.println("Scan data sent");
    }
  }
  Serial.println("last");

  vTaskDelete(NULL); // delete the task when done
}

void handleScan(const DynamicJsonDocument &doc)
{
  DynamicJsonDocument *docCopy = new DynamicJsonDocument(doc.capacity());
  *docCopy = doc;
  xTaskCreatePinnedToCore(
      handleScanTask,  // Task function
      "ScanTask",      // Task name
      8192,            // Stack size (bytes)
      (void *)docCopy, // Parameter to pass to the task
      1,               // Task priority
      &scanTask,       // Task handle
      0);              // Core (0 or 1, depending on your setup)
}

/**========================================================================
 *                           STATE BAR
 *========================================================================**/

void handleifelse(const DynamicJsonDocument &doc)
{
  // to handle login
  if (doc.containsKey("username"))
  {
    if (doc["username"].as<String>() == "esp32" && doc["password"].as<String>() == "123")
    {
      sendLoginSuccessNotification();
    }
    else
    {
      sendLoginFailureNotification();
    }
  }
  // check if logged in
  else if (doc.containsKey("flag"))
  {
    sendFlagStatus();
  }
  // lamps check
  else if (doc.containsKey("uvlampstutus"))
  {
    handleLampStatus("uv");
  }
  else if (doc.containsKey("vilampstutus"))
  {
    handleLampStatus("vi");
  }
  else if (doc.containsKey("turnuvon"))
  {
    handleLampControl("uv", true);
  }
  else if (doc.containsKey("turnuvoff"))
  {
    handleLampControl("uv", false);
  }
  else if (doc.containsKey("turnvion"))
  {
    handleLampControl("vi", true);
  }
  else if (doc.containsKey("turnvioff"))
  {
    handleLampControl("vi", false);
  }
  else if (doc.containsKey("savepreset"))
  {
    String filename = doc["name"].as<String>() + " === " + doc["time"].as<String>() + ".txt";
    String bath = "/presetsDB.txt";
    writeToDatabase("/presets/", doc);
    SdWriteString(bath, filename); // save the name of the file into database
  }
  else if (doc.containsKey("deletepresets"))
  {
    SD.remove("/presets/" + doc["name"].as<String>() + ".txt"); // delete the file itself
    String LineToDelete = doc["name"].as<String>() + ".txt";
    deleteLineFromFile("/presetsDB.txt", LineToDelete); // delete its name from the DB
  }
  else if (doc.containsKey("showpresets"))
  {
    // handleShowPresets("/presets");                              //old version
    getFilesJson("/presets"); // like list dictionary function and send it to web
  }
  else if (doc.containsKey("loadthis"))
  {
    handleLoadPreset(doc);
  }
  else if (doc.containsKey("supplystutus"))
  {
    handleSupplyStatus();
  }
  else if (doc.containsKey("loadtime"))
  {
    loadtime();
  }
  else if (doc.containsKey("updatetime"))
  {
    savetime(doc);
  }
  else if (doc.containsKey("motors"))
  {
    sendsteps();
  }
  else if (doc.containsKey("lampmotor"))
  {
    getlampmoter();
  }
  else if (doc.containsKey("Lampmotortoggle"))
  {
    ToggleLampMotor(doc);
    delay(80);
    getlampmoter();
  }
  else if (doc.containsKey("gohome"))
  {
    handleGoHome(doc);
  }
  else if (doc.containsKey("savethis"))
  {
    handleSavestep(doc);
  }
  else if (doc.containsKey("movemoter"))
  {
    handlemovestep(doc);
    delay(80);
    sendsteps();
  }
  else if (doc.containsKey("newgain"))
  {
    handlenewgain(doc);
  }
  else if (doc.containsKey("senddetector"))
  {
    handelreaddetecor();
  }
  else if (doc.containsKey("isFirst"))
  {
    Serial.print("saved");
    // writeToDatabase("/readings/", doc); //old version
    WriteAsCsv(doc, 8);
    String filename = doc["SampleID"].as<String>() + " === " + doc["time"].as<String>() + ".csv";
    String bath = "/readingsDB.txt";
    if (doc["isFirst"].as<String>() == "true")
    {
      SdWriteString(bath, filename); // save the name of the file into database
    }
  }
  else if (doc.containsKey("showreadings"))
  {
    // handleShowPresets("/readings");       //old version
    getFilesJson("/readings");
  }
  else if (doc.containsKey("deletereadings"))
  {
    SD.remove("/readings/" + doc["name"].as<String>() + ".csv");
    String LineToDelete = doc["name"].as<String>() + ".csv";
    deleteLineFromFile("/ReadingsDB.txt", LineToDelete);
  }
  else if (doc.containsKey("DirectCommand"))
  {
    handleDirectCommand(doc);
  }

  else if (doc["command"] == "Scan")
  {
    Serial.println("command is scan");
    handleScan(doc);
  }
  else if (doc["command"] == "ScanStop")
  {
    Serial.println("command is ScanStop");
    StopScan=true;
    String response= sendCMD("stop-scan");
  }
  
  else if (doc["command"] == "StateBar")
  {
    handleSB(doc);
  }

  else
  {
    notifyClients("Unknown command");
  }
}
