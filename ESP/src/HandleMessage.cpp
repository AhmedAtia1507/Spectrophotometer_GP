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
  Serial2.flush();
  Serial2.println(input);
  Serial.println(input);
  int startTime = millis();
  while (Serial2.available() && millis() - startTime < 30000)
  {
    vTaskDelay(pdMS_TO_TICKS(1));
  }
  response = Serial2.readStringUntil('\n');
  Serial.println("Response received: " + response);
    
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
      sendCMDTask,   // Task function
      "sendCMDTask", // Task name
      8192,          // Stack size (bytes)
      (void *)doc,   // Parameter to pass to the task
      1,             // Task priority
      &cmdTask,      // Task handle
      0              // Core (0 or 1, depending on your setup)
  );

  // Wait for the task to complete
  while (eTaskGetState(cmdTask) != eDeleted)
  {
    vTaskDelay(pdMS_TO_TICKS(10)); // Delay to yield to the task
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
 *                           SCAN TIME TASK
 *------------------------------------------------------------------------**/
TaskHandle_t scanTimeTask;
// TASK
void handleScanTimeTask(void *pvParameters)
{
  DynamicJsonDocument doc = *((DynamicJsonDocument *)pvParameters);

  String command = doc["command"].as<String>();
  String timeInterval = doc["timeInterval"].as<String>();
  String specificWL = doc["specificWL"].as<String>();
  String Time;
  String buffur;
  int j = 1; // represent the current iteration
  int Buffersize = 10;
  bool scanning = true;
  DynamicJsonDocument scanData(256);

  if (command == "scan-time")
  {
    String scancmd = "Scan-time " + specificWL + " " + timeInterval;
    Serial.println(scancmd);
    Serial2.println(scancmd);
    //Serial2.flush();
      while (Serial2.available() == 0)
      { 
        
        vTaskDelay(pdMS_TO_TICKS(1));
        if(StopScan==true){ StopScan=false; break;}
    
      }
       String response = Serial2.readStringUntil('\n');
       Serial.println(response);

       if(response == "Init-Finished" ){
      while (Serial2.available() == 0)
      {
        vTaskDelay(pdMS_TO_TICKS(1));
      }
        Time =Serial2.readStringUntil('\n');
        Serial2.flush();
while(!StopScan){
  

      int startTime = millis();
      while (Serial2.available() == 0 && millis() - startTime < 2000)
      {
       vTaskDelay(pdMS_TO_TICKS(1));
      }
       String response = Serial2.readStringUntil('\n');
       Serial.println(response);

      // Split the response into components
      float space1 = response.indexOf(' ');
      // float space2 = response.indexOf(' ', space1 + 1);

     String reference = response.substring(0, space1);
     String sample = response.substring(space1 + 1);


      scanData["currentTime"] = Time;
      scanData["timeInterval"] = timeInterval.toFloat();
      scanData["intensityReference"] = reference.toFloat();
      scanData["intensitySample"] = sample.toFloat();

      Buffersize--;
      String jsonString;
      serializeJson(scanData, jsonString);
      buffur+=jsonString+"\n";
      if(Buffersize==0){
        Buffersize = 10; //to reset the buffer size
        notifyClients(buffur);
        buffur = "";
      }
      Serial.println("Scan data sent");
    }
  }
  }
  if(Buffersize>0){
        Buffersize = 10; //to reset the buffer size
        notifyClients(buffur);
        buffur = "";
      }
  Serial.println("last");
  StopScan = false;

  vTaskDelete(NULL); // delete the task when done
}

void handleScanTime(const DynamicJsonDocument &doc)
{
  DynamicJsonDocument *docCopy = new DynamicJsonDocument(doc.capacity());
  *docCopy = doc;
  xTaskCreatePinnedToCore(
      handleScanTimeTask,  // Task function
      "ScanTimeTask",      // Task name
      8192,            // Stack size (bytes)
      (void *)docCopy, // Parameter to pass to the task
      1,               // Task priority
      &scanTimeTask,       // Task handle
      0);              // Core (0 or 1, depending on your setup)
}
/**------------------------------------------------------------------------
 *                           FIT LINE TASK
 *------------------------------------------------------------------------**/
TaskHandle_t fitLineTask;
// TASK
void handlefitLineTask(void *pvParameters)
{
  DynamicJsonDocument doc = *((DynamicJsonDocument *)pvParameters);

  String command = doc["command"].as<String>();
  String startInput = doc["startInput"].as<String>();
  String stopInput = doc["stopInput"].as<String>();
  String stepInput = doc["stepInput"].as<String>();
 DynamicJsonDocument scanData(256);
    String scancmd = command + " " + startInput ;
    Serial.println(scancmd);
    Serial2.println(scancmd);

      while (Serial2.available() == 0 )
      { 
        Serial.println("while looop");
        vTaskDelay(pdMS_TO_TICKS(20));
            if(StopScan==true){ StopScan=false; break;}
    
       
      }
       String response = Serial2.readStringUntil('\n');
       Serial.println(response);

       if(response == "Init-Finished" ){
      while (Serial2.available() == 0)
      {
        vTaskDelay(pdMS_TO_TICKS(20));
        
      }
       
      String response = Serial2.readStringUntil('\n');
      Serial2.flush();
      Serial.println(response);
    
   
      
      float space1 = response.indexOf(' ');

      // String wavelength = response.substring(0, space1);
     String reference = response.substring(0, space1);
      //String wavelength = String(i);
      String sample = response.substring(space1 + 1);



  
      scanData["intensityReference"] = reference.toFloat();
      scanData["intensitySample"] = sample.toFloat();
       String jsonString;
      serializeJson(scanData, jsonString);
              notifyClients(jsonString);

    }
  
  Serial.println("last");

  vTaskDelete(NULL); // delete the task when done
}

void handlefitLine(const DynamicJsonDocument &doc)
{
  DynamicJsonDocument *docCopy = new DynamicJsonDocument(doc.capacity());
  *docCopy = doc;
  xTaskCreatePinnedToCore(
      handlefitLineTask,  // Task function
      "fitLineTask",      // Task name
      8192,            // Stack size (bytes)
      (void *)docCopy, // Parameter to pass to the task
      1,               // Task priority
      &fitLineTask,       // Task handle
      0);              // Core (0 or 1, depending on your setup)
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
  String Time;
  String buffur;
  float current = (stopInput.toFloat() - startInput.toFloat()) / stepInput.toFloat();
  int j = 1; // represent the current iteration
  int Buffersize = 10;
  bool scanning = true;
  DynamicJsonDocument scanData(256);

  if (command == "scan")
  {
    String scancmd = command + " " + lampmode + " " + startInput + " " + stopInput + " " + stepInput;
    int NumberOfReadings = (stopInput.toFloat() - startInput.toFloat()) / stepInput.toFloat()  + 1;
    Serial.println("no of readings: "+String(NumberOfReadings)+"\n");
    
    Serial.println(scancmd);
    Serial2.println(scancmd);
    //Serial2.flush();
      while (Serial2.available() == 0)
      {     
      if(StopScan==true){ StopScan=false; break;}
      }
       String response = Serial2.readStringUntil('\n');
       Serial.println(response);

       if(response == "Init-Finished" ){
      while (Serial2.available() == 0)
      {
    
        vTaskDelay(pdMS_TO_TICKS(1));
        if(StopScan==true){ StopScan=false; break;}
    
      }
        Time =Serial2.readStringUntil('\n');
        Serial2.flush();
    for (NumberOfReadings ; NumberOfReadings > 0 ; NumberOfReadings--)
    {
      vTaskDelay(pdMS_TO_TICKS(5));
      
      if (StopScan)
      {
        StopScan = false;
        // Break out of the loop to stop the task
        break;
      }

      int startTime = millis();
      while (Serial2.available() == 0 && millis() - startTime < 2000)
      {
        delay(1);
      }
       String response = Serial2.readStringUntil('\n');
       Serial.println(response);
       
      // Generate random numbers in the range 1 to 1000
      // float num1 = rand() % 1000 + 1;
      // float num2 = rand() % 1000 + 1;
      // float num3 = rand() % 1000 + 1;

      // // Create the response string
      // String response = "23/3||1:30 ";
      // response += String(num1) + " " + String(num2) + " " + String(num3);
      // Serial.println(response); // debug

      // Split the response into components
      float space1 = response.indexOf(' ');
      float space2 = response.indexOf(' ', space1 + 1);

      // String wavelength = response.substring(0, space1);
     String wavelength = response.substring(0, space1);
     Serial.println(wavelength);
      //String wavelength = String(i);
      String reference = response.substring(space1 + 1, space2);
   //  Serial.println(reference);
      String sample = response.substring(space2+ 1);
     Serial.println(sample);
      if (scanning)
      {
        float ratio = 0;
        if (j - 1 != 0)
        { // first iteration make ratio = 0
          ratio = 100 / current * (j - 1);
          Serial.println(ratio);
        
        }
        if (NumberOfReadings==1){
          ratio = 100;
          //Serial.println(ratio);
        }
        scanData["current"] = ratio; // to help display the % progress
        
      }

      scanData["currentTime"] = Time;
      Serial.print(Time);
      scanData["wavelength"] = wavelength.toFloat();
      scanData["intensityReference"] = reference.toFloat();
      scanData["intensitySample"] = sample.toFloat();
      scanData["scanning"] = scanning;

      j++;

      if (startInput == stopInput)
      {
        scanData["current"] = 100; // to help display the % progress
      }
      Buffersize--;
      String jsonString;
      serializeJson(scanData, jsonString);
      buffur+=jsonString+"\n";
      if(Buffersize==0){
        Buffersize = 10; //to reset the buffer size
        notifyClients(buffur);
        buffur = "";
      }
      Serial.println("Scan data sent");
    }
  }
  }
  if(Buffersize>0){
        Buffersize = 10; //to reset the buffer size
        notifyClients(buffur);
        buffur = "";
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
  
  else if (doc.containsKey("deletepresets"))
  {
    SD.remove( doc["name"].as<String>()); // delete the file itself
    String LineToDelete = doc["name"].as<String>();
    deleteLineFromFile("/presetsDB.txt", LineToDelete); // delete its name from the DB
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
  
  else if (doc.containsKey("deletereadings"))
  {
    SD.remove(doc["name"].as<String>());
    String LineToDelete = doc["name"].as<String>();
    deleteLineFromFile("/ReadingsDB.txt", LineToDelete);
  }
  else if (doc.containsKey("DirectCommand"))
  {
    handleDirectCommand(doc);
  }

  else if (doc["command"] == "scan")
  {
    Serial.println("command is scan");
    handleScan(doc);
  }
  else if (doc["command"] == "scan-time")
  {
    Serial.println("command is scan-time");
    handleScanTime(doc);
  }
  else if (doc["command"] == "fitLine")
  {
    Serial.println("fitLine");
    handleScan(doc);


  }
  else if (doc["command"] == "ScanStop")
  {
    Serial.println("command is ScanStop");
    StopScan = true;
    String response = sendCMD("scan-stop");
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
