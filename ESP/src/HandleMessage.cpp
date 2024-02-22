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
    String command = "snd" + lampType + "\n";
    // String status = sendCMD(command);
    String status = "on";
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
    String command = turnOn ? lampType + "on" : lampType + "off";
    handleLampStatus(lampType);
}

void handleShowPresets()
{
    const char *directory = "/presets";
    JsonObject result = getFilesJson(directory);
    String jsonString;
    serializeJson(result, jsonString);
    notifyClients(jsonString);
}

void handleLoadPreset(const DynamicJsonDocument &doc)
{
    String selectthis = doc["loadthis"].as<String>();
    String path = "/presets/" + selectthis + ".txt";
    Serial.print(path);
    String jsonString;
    DynamicJsonDocument preset = readFromDatabase(path.c_str());
    serializeJson(preset, jsonString);
    notifyClients(jsonString);
}

void handleSupplyStatus()
{
    // String stutusp12 = sendCMD((char *)"p12\n");
    // String stutusn12 = sendCMD((char *)"n12ff\n");
    // String stutusp5 = sendCMD((char *)"p5\n");
    // String stutusp33 = sendCMD((char *)"p33\n");
    // String stutustwelve = sendCMD((char *)"twelve\n");
    DynamicJsonDocument object(1024);
    object["supplystutus"] = "good";
    // object["p12"] = stutusp12;
    // object["n12"] = stutusn12;
    // object["p5"] = stutusp5;
    // object["p33"] = stutusp33;
    // object["twelve"] = stutustwelve;
    object["p12"] = "+12.1\n";
    object["n12"] = "-12.3\n";
    object["p5"] = "4.3\n";
    object["p33"] = "3.2\n";
    object["twelve"] = "11\n";

    String jsonString;
    serializeJson(object, jsonString);
    notifyClients(jsonString);
}

void loadtime()
{
    // String response = sendCMD("sndtime\n");
    String response = "1/13/2024 13:32:12\n";
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
    // String respnse = sendCMD("savedate "+command + "\n");
    String respnse = "success";
    Serial.print(respnse);
    DynamicJsonDocument object(29);
    object["timeupdated"] = respnse;
    String jsonString;
    serializeJson(object, jsonString);
    notifyClients(jsonString);
}
void sendsteps()
{
    String command = "sndmotorsteps\n";
    // String response = sendCMD(command);
    String response = "30-40-50-1100\n";
    Serial.print(response);
    DynamicJsonDocument object(60);
    object["motorssteps"] = response;
    String jsonString;
    serializeJson(object, jsonString);
    notifyClients(jsonString);
}
