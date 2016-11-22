#include <SoftwareSerial.h>
#include <string.h>
#include "ESP8266.h"

SoftwareSerial esp8266Serial = SoftwareSerial(10, 11);
ESP8266 wifi = ESP8266(esp8266Serial);
int echoPin = 12;
int trigPin = 13;

char *str = "Hello world! Can you read me? \n";
int len;

void setup()
{
  Serial.begin(9600);

  
  // ESP8266
  esp8266Serial.begin(9600);
  wifi.begin();
  wifi.setTimeout(1000);

  len = sizeof(char)*strlen(str);
  
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  
  // setBaudrate
  Serial.print("setBaudrate: ");
  wifi.setBaudrate(9600);
  
  /****************************************/
  /******       TCP/IP commands      ******/
  /****************************************/

  // connect
  Serial.print("connect: ");
  Serial.println(getStatus(wifi.connect(ESP8266_PROTOCOL_TCP, IPAddress(172,30,1,21), 4001)));
 
  int tmp=1;
  Serial.println(getStatus(wifi.send(tmp)));
  tmp = 100;
  Serial.println(getStatus(wifi.send(tmp)));
  tmp = 5;
  Serial.println(getStatus(wifi.send(tmp)));
  char *label = "Door";
  int len = strlen(label);
  Serial.println(getStatus(wifi.send(len)));
  Serial.println(getStatus(wifi.send(label)));
  Serial.println(sizeof(float));
  // close
  /*Serial.print("close: ");
   Serial.println(getStatus(wifi.close()));*/
}

void loop()
{
  /****************************************/
  /******       TCP/IP commands      ******/
  /****************************************/

  float duration,distance;
  double check;
  
  digitalWrite(trigPin,HIGH);
  digitalWrite(trigPin,LOW);
  
  duration = pulseIn(echoPin,HIGH);
  distance = ((float)(340*duration)/10000)/2;
  
  Serial.println(distance);
  Serial.println(getStatus(wifi.send(distance)));
  
  delay(500);
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



