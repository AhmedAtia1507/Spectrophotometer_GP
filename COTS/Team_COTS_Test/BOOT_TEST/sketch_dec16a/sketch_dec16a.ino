#include <SPIFFS.h>
#define BOOT0_PIN   4
#define BOOT1_PIN   15
unsigned char de7k = 0;
void setup() {
  Serial2.begin(9600);
  Serial.begin(115200);
  pinMode(BOOT1_PIN, OUTPUT);
  pinMode(BOOT0_PIN, OUTPUT);
  pinMode(2, OUTPUT);
  digitalWrite(BOOT0_PIN, HIGH);
  digitalWrite(BOOT1_PIN, LOW);
  
  delay(100);

  Serial2.write(0x7F);

  while(Serial2.available() == 0);
  de7k = Serial2.read();
  if(de7k == 0x79)
  {
    digitalWrite(2, HIGH);
  }
  //if(!SPIFFS.begin()){
  //  Serial.println("An error occurred while mounting SPIFFS");
  //  return;
  //}
//
  //File file = SPIFFS.open("/output.bin", "r");
  ////if(!file){
  ////  Serial.println("Failed to open file for reading");
  ////  return;
  ////}
//
  //while(file.available()){
  //  Serial2.write(file.read());
  //}
//
  //file.close();
//
  //digitalWrite(BOOT0_PIN, LOW);
  //digitalWrite(BOOT1_PIN, LOW);
}

void loop() {
  Serial.println(de7k);
  delay(5000);
}