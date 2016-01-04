/*
 * --------指令測試--------
 * ---在序列監控視窗輸入---
 * AT     -> 測試回應
 * AT+RST   -> reset
 * AT+CWMODE? -> 查詢模式
 */


#include <SoftwareSerial.h>

SoftwareSerial esp8266(8,9);

void setup() {
    Serial.begin(9600); 
    esp8266.begin(115200);  
}

void loop() {
  if (esp8266.available() > 0) {
    String data = esp8266.readString();
    Serial.println(data);
  }

  if (Serial.available() > 0) { 
    String data = Serial.readString();
    esp8266.println(data);
  }
}
