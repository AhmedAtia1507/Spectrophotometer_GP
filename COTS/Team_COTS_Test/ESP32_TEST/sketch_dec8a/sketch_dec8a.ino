#include <HardwareSerial.h>
#include <string.h>
#include <strings.h>

void SendCommand(unsigned char* command)
{
  if(command != NULL)
  {
    unsigned char i = 0;
    while(command[i] != '\0')
    {
      Serial2.write(command[i]);
      i++;
    }
    Serial2.write('\n');
  }
  else
  {

  }
}
  unsigned char de7k = 0;
unsigned char de7k_str[20];
unsigned char j = 0;

void readCommand(unsigned char* command)
{
  if(command != NULL)
  {
    while(1)
    {
      while(Serial2.available() == 0);
      char rx_char = Serial2.read();
      if(rx_char == '\n')
      {
        command[j] = '\0';
        j = 0;
        break;
      }
      else
      {
        command[j] = rx_char;
        j++;
      }
    }
    
  }
}
void setup() {
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, 16, 17);
  pinMode(2, OUTPUT);
}

void loop() {
  SendCommand((unsigned char*)"SET UV ON");
  while(Serial2.available() == 0);
  readCommand(de7k_str);
  if(!strcmp((const char*)de7k_str, "1"))
  {
    digitalWrite(2, HIGH);  
  }
  delay(1000);
  SendCommand((unsigned char*)"GET UV STATUS");
  while(Serial2.available() == 0);
  readCommand(de7k_str);
  if(!strcmp((const char*)de7k_str, "UV ON"))
  {
    digitalWrite(2, LOW);  
  }
  delay(1000);
  SendCommand((unsigned char*)"SET UV OFF");
  while(Serial2.available() == 0);
  readCommand(de7k_str);
  if(!strcmp((const char*)de7k_str, "1"))
  {
    digitalWrite(2, HIGH);  
  }
  delay(1000);
  SendCommand((unsigned char*)"GET UV STATUS");
  while(Serial2.available() == 0);
  readCommand(de7k_str);
  if(!strcmp((const char*)de7k_str, "UV OFF"))
  {
    digitalWrite(2, LOW);  
  }
  delay(1000);
  SendCommand((unsigned char*)"SET VIS ON");
  while(Serial2.available() == 0);
  readCommand(de7k_str);
  if(!strcmp((const char*)de7k_str, "1"))
  {
    digitalWrite(2, HIGH);  
  }
  delay(1000);
  SendCommand((unsigned char*)"GET VIS STATUS");
  while(Serial2.available() == 0);
  readCommand(de7k_str);
  if(!strcmp((const char*)de7k_str, "VIS ON"))
  {
    digitalWrite(2, LOW);  
  }
  delay(1000);
  SendCommand((unsigned char*)"SET VIS OFF");
  while(Serial2.available() == 0);
  readCommand(de7k_str);
  if(!strcmp((const char*)de7k_str, "1"))
  {
    digitalWrite(2, HIGH);  
  }
  delay(1000);
  SendCommand((unsigned char*)"GET VIS STATUS");
  while(Serial2.available() == 0);
  readCommand(de7k_str);
  if(!strcmp((const char*)de7k_str, "VIS OFF"))
  {
    digitalWrite(2, LOW);  
  }
  delay(1000);
  SendCommand((unsigned char*)"GET ABSORPTION");
  delay(500);
  SendCommand((unsigned char*)"17.23");
  delay(200);
  SendCommand((unsigned char*)"8.24");
  delay(200);
  SendCommand((unsigned char*)"1100");
  while(Serial2.available() == 0);
  readCommand(de7k_str);
  if(!strcmp((const char*)de7k_str, "RX DONE"))
  {
    digitalWrite(2, HIGH);  
  }
  delay(1000);
}
