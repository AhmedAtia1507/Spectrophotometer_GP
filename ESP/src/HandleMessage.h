#ifndef HANDLE_MESSAGE_H
#define HANDLE_MESSAGE_H

#include <Arduino.h>
#include <ArduinoJson.h>

void startCountdown();
void checkCountdown();
String sendCMD(const String &input);
String getOutputStates();
void sendLoginSuccessNotification();
void sendLoginFailureNotification();
void sendFlagStatus();
void handleLampStatus(const String &lampType);
void handleLampControl(const String &lampType, bool turnOn);
void handleShowPresets();
void handleLoadPreset(const DynamicJsonDocument &doc);
void handleSupplyStatus();
void notifyClients(String state);
void savetime(const DynamicJsonDocument &doc);
void loadtime();
void sendsteps();
void handleGoHome(const DynamicJsonDocument &doc);
void handleSavestep(const DynamicJsonDocument &doc);
void handlemovestep(const DynamicJsonDocument &doc);
<<<<<<< HEAD
void handleScan(const DynamicJsonDocument &doc);
=======
void handleifelse(const DynamicJsonDocument &doc);
void handlenewgain(const DynamicJsonDocument &doc);
void handelreaddetecor();

>>>>>>> ce29d35dcdb2a919594f1b09dc8f87719c9909f9
#endif // HANDLE_MESSAGE_H
