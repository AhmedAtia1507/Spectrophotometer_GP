#include "HandleMessage.h"
#include "MyInitialization.h"
#include "MySDFunctions.h"

const unsigned long interval = 600000; // 10 minutes in milliseconds
unsigned long previousMillis;
bool loginflag = false; // to check if the user logged in before accessing the control page

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

String sendCMD(const String &input)
{

  
    // Send the command to the STM32 via UART
    Serial2.println(input);
    Serial.println(input);
    Serial.println("sent command");
    // Wait for a response from the STM32
    int startTime = millis();
    while (Serial2.available() == 0 && millis() - startTime < 2000)
    {
        delay(1);
    }
    // Read and return the response
    String response = Serial2.readStringUntil('\n');
    Serial.println(response);
    return response;
}

String outputSBar[3] = {"UV", "VI", "WL"};
String getOutputStates()
{
    Serial.print("WS received");
    DynamicJsonDocument doc(1024);
    JsonArray sbar = doc.createNestedArray("sbar");
    for (int i = 0; i < 3; i++)
    {
        JsonObject element = sbar.createNestedObject();
        element["output"] = outputSBar[i];
        element["state"] = sendCMD(outputSBar[i]);
    }
    // Serialize the JSON document to a string
    String jsonString;
    serializeJson(doc, jsonString);

    return jsonString;
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
    //String status = "on";
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
    String command = turnOn ?"set-"+ lampType + "-on" :"set-"+lampType + "-off";
    String status = sendCMD(command);
    handleLampStatus(lampType);
}

void handleShowPresets( const char *directory){
    DynamicJsonDocument result = getFilesJson(directory);
    String jsonString;
    serializeJson(result, jsonString);
    notifyClients(jsonString);
}

void handleLoadPreset(const DynamicJsonDocument &doc)
{
    String selectthis = doc["loadthis"].as<String>();
    String path="";
    DynamicJsonDocument preset(1024);
    if(doc["Dictionary"]=="readings"){
    path = "/readings/" + selectthis + ".txt";
    readFromDatabase2(doc);
    }

    else if(doc["Dictionary"]=="presets"){
    path = "/presets/" + selectthis + ".txt";
    
    preset = readFromDatabase(path.c_str());
  
    }
    String jsonString;
    
    if(doc["Dictionary"]=="presets"){
     preset["loaded"] = "loaded";
    serializeJson(preset, jsonString);
    notifyClients(jsonString);
   }
    
}

void handleSupplyStatus()
{
    String stutusp12 = sendCMD("get-voltage-p12");
    String stutusn12 = sendCMD("get-voltage-n12");
    String stutusp5 = sendCMD("get-voltage-p5");
    String stutusp33 = sendCMD("get-voltage-p33");
    String stutustwelve = sendCMD("get-voltage-twelve");
    DynamicJsonDocument object(1024);
    object["supplystutus"] = "good";
     object["p12"] = stutusp12;
     object["n12"] = stutusn12;
     object["p5"] = stutusp5;
     object["p33"] = stutusp33;
     object["twelve"] = stutustwelve;
    //object["p12"] = "+12.1\n";
    //object["n12"] = "-12.3\n";
    //object["p5"] = "4.3\n";
    //object["p33"] = "3.2\n";
    //object["twelve"] = "11\n";

    String jsonString;
    serializeJson(object, jsonString);
    notifyClients(jsonString);
}

void loadtime()
{
    String response = sendCMD("get-time");
    //String response = "1/13/2024 13:32:12\n";
    Serial.print(response);
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
    String respnse = sendCMD("set-time-"+command);
    //String respnse = "success";
    Serial.print(respnse);
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
    //String response = "30-40-50-1100\n";
    Serial.print(response);
    DynamicJsonDocument object(60);
    object["motorssteps"] = response;
    String jsonString;
    serializeJson(object, jsonString);
    notifyClients(jsonString);
}
void handleGoHome(const DynamicJsonDocument &doc)
{
    String motortype = doc["type"];
    Serial.print(motortype);
    String command = motortype ;
    String response = sendCMD(command);
    String wavelength = sendCMD("get-current-wav");
    //String response = "0";
    //String wavelength = "878";
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
    String correctstep = doc["savethis"];
    String correctwave = doc["wavelength"];
    String response = sendCMD(correctstep);
    String wavelength = sendCMD(correctwave);
    //String response = "saved";
    // String wavelength = "878";
    DynamicJsonDocument object(90);
    object["stepsaved"] = response;
    String jsonString;
    serializeJson(object, jsonString);
    notifyClients(jsonString);
}
void handlemovestep(const DynamicJsonDocument &doc)
{
    String correctstep = doc["movemoter"];
    String response = sendCMD(correctstep);
    //String response = "moved";
    DynamicJsonDocument object(90);
    object["motermoved"] = response;
    String jsonString;
    serializeJson(object, jsonString);
    notifyClients(jsonString);
    sendsteps();
}
void handelreaddetecor(){
    //String response = sendCMD("get-det-readings");
    String response = "12-122-22-260-17";
    DynamicJsonDocument object(90);
    object["detreadings"] = response;
    String jsonString;
    serializeJson(object, jsonString);
    notifyClients(jsonString);
}
void handlenewgain(const DynamicJsonDocument &doc)
{
    String newgain = doc["newgain"];
    //String response = sendCMD("set-newgain-"+newgain);
    String response = "applied";
    if(response=="applied"){
      handelreaddetecor();
    }
    //else{handlenewgain(doc);}
    }

/**------------------------------------------------------------------------
 *                           SCAN TASK
 *------------------------------------------------------------------------**/
TaskHandle_t scanTask;
// TASK
void handleScanTask(void *pvParameters) {
  DynamicJsonDocument doc = *((DynamicJsonDocument *)pvParameters);
 
  String command = doc["command"].as<String>();
  if (command == "Scan") {
    String startInput = doc["startInput"].as<String>();
    String stopInput = doc["stopInput"].as<String>();
    String stepInput = doc["stepInput"].as<String>();
    float current=(stopInput.toInt()-startInput.toInt())/stepInput.toInt();
    
    int j=1; //represent the current iteration
    Serial2.println(command + " " + startInput + " " + stopInput + " " + stepInput);
    bool scanning= true;
    for (int i = startInput.toInt(); i <= stopInput.toInt(); i += stepInput.toInt()) {
      delay(100);
        // int startTime = millis();
        // while (Serial2.available() == 0 && millis() - startTime < 2000) {
        //   delay(1);
        // }
        // String response = Serial2.readStringUntil('\n');
        String response ="23/3||1:30 200 10 10.5";
        Serial.println(response); // debug
       
        // Split the response into components
        int space1 = response.indexOf(' ');
        int space2 = response.indexOf(' ', space1 + 1);
        int space3 = response.indexOf(' ', space2 + 1);
 
        String Time = response.substring(0, space1);
        String wavelength = response.substring(space1 + 1, space2);
        String reference = response.substring(space2 + 1, space3);
        String sample = response.substring(space3 + 1);
        DynamicJsonDocument scanData(256);
        
        
        if(i==stopInput.toInt()||(i + stepInput.toInt() > stopInput.toInt())){
          scanning=false;
          scanData["current"]=100;
        }
        scanData["currentTime"] = Time;
        scanData["wavelength"] = i;
        scanData["intensityReference"] = reference.toFloat();
        scanData["intensitySample"] = sample.toFloat();
        scanData["scanning"]=scanning;
        if(scanning){
        float ratio =100/current*j;
        scanData["current"]=ratio;  //to help display the % progress
        }
        j++;

        
       
        String jsonString;
        serializeJson(scanData, jsonString);
        notifyClients(jsonString);
        Serial.println("Scan data sent");
    }
  }
  vTaskDelete(NULL); // delete the task when done
}
 
void handleScan(const DynamicJsonDocument &doc) {
    DynamicJsonDocument *docCopy = new DynamicJsonDocument(doc.capacity());
    *docCopy = doc;
  xTaskCreatePinnedToCore(
      handleScanTask,       // Task function
      "ScanTask",           // Task name
      8192,                 // Stack size (bytes)
      (void *)docCopy,         // Parameter to pass to the task
      1,                    // Task priority
      &scanTask,            // Task handle
      0);                   // Core (0 or 1, depending on your setup)
}



 
 void handleifelse(const DynamicJsonDocument &doc){
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
      writeToDatabase("/presets/", doc);
    }
    else if (doc.containsKey("deletepreset"))
    {
      SD.remove("/presets/" + doc["name"].as<String>() + ".txt");
    }
    else if (doc.containsKey("showpreset"))
    {
      handleShowPresets("/presets");
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
    else if (doc.containsKey("gohome"))
    {
      handleGoHome(doc);
    }
    else if (doc.containsKey("savethis")){
      handleSavestep(doc);
    }
    else if (doc.containsKey("movemoter"))
    {
      handlemovestep(doc);
    }
    else if (doc.containsKey("newgain")){
      handlenewgain(doc);
    }
    else if (doc.containsKey("senddetector")){
      handelreaddetecor();
    }
    else if(doc.containsKey("isFirst")){
      Serial.print("saved");
      writeToDatabase("/readings/",doc);
      
}
    else if(doc.containsKey("showreadings")){
      handleShowPresets("/readings");
    }
    else if (doc.containsKey("deletereading"))
    {
      SD.remove("/readings/" + doc["name"].as<String>() + ".txt");
    }
    
      

    else if (doc["command"]=="Scan")
    {
      Serial.println("command is scan");
      handleScan(doc);

    }

      else
      {
        notifyClients("Unknown command");
      }
  
 }
