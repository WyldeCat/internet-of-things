#include <SoftwareSerial.h>
#include <string.h>
#include "ESP8266.h"

SoftwareSerial esp8266Serial = SoftwareSerial(10, 11);
ESP8266 wifi = ESP8266(esp8266Serial);

char *str = "Hello world! Can you read me? \n";
int len,stat,count;

void setup()
{
  Serial.begin(9600);

  // ESP8266
  esp8266Serial.begin(9600);
  wifi.begin();
  wifi.setTimeout(1000);

  len = sizeof(char)*strlen(str);
  
  // setBaudrate
  Serial.print("setBaudrate: ");
  wifi.setBaudrate(9600);
  
  /****************************************/
  /******       TCP/IP commands      ******/
  /****************************************/

  // connect
  Serial.print("connect: ");
  Serial.println(getStatus(wifi.connect(ESP8266_PROTOCOL_TCP, IPAddress(172,30,1,21), 4001)));

  int tmp=0;
  char *label = "power-tmp";
  Serial.println(getStatus(wifi.send(tmp)));
  Serial.println(getStatus(wifi.send(tmp)));
  Serial.println(getStatus(wifi.send(tmp)));
  Serial.println(getStatus(wifi.send(strlen(label))));
  Serial.println(getStatus(wifi.send(label)));
  // close
  /*Serial.print("close: ");
   Serial.println(getStatus(wifi.close()));*/
}

void loop()
{
  /****************************************/
  /******       TCP/IP commands      ******/
  /****************************************/
  // read data
  int length;
  if ((length = wifi.available()) > 0) 
  {
    wifi.read((char*)&stat,2);
  }
  count++;
  if(count==30000)
  {
    Serial.print("Status : ");
    Serial.println(stat);
    count=0;
  }
}

String getStatus(bool status)
{
  if (status)
    return "OK";

  return "KO";
}

String getStatus(ESP8266CommandStatus status)
{
  switch (status) {
  case ESP8266_COMMAND_INVALID:
    return "INVALID";
    break;

  case ESP8266_COMMAND_TIMEOUT:
    return "TIMEOUT";
    break;

  case ESP8266_COMMAND_OK:
    return "OK";
    break;

  case ESP8266_COMMAND_NO_CHANGE:
    return "NO CHANGE";
    break;

  case ESP8266_COMMAND_ERROR:
    return "ERROR";
    break;

  case ESP8266_COMMAND_NO_LINK:
    return "NO LINK";
    break;

  case ESP8266_COMMAND_TOO_LONG:
    return "TOO LONG";
    break;

  case ESP8266_COMMAND_FAIL:
    return "FAIL";
    break;

  default:
    return "UNKNOWN COMMAND STATUS";
    break;
  }
}

String getRole(ESP8266Role role)
{
  switch (role) {
  case ESP8266_ROLE_CLIENT:
    return "CLIENT";
    break;

  case ESP8266_ROLE_SERVER:
    return "SERVER";
    break;

  default:
    return "UNKNOWN ROLE";
    break;
  }
}

String getProtocol(ESP8266Protocol protocol)
{
  switch (protocol) {
  case ESP8266_PROTOCOL_TCP:
    return "TCP";
    break;

  case ESP8266_PROTOCOL_UDP:
    return "UDP";
    break;

  default:
    return "UNKNOWN PROTOCOL";
    break;
  }
}



