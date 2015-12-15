#include <SoftwareSerial.h>

// 設定8,9 pin 為 Rx,Tx
SoftwareSerial esp8266(8,9);

String SID = "WiFi名稱";
String PWD = "WiFi密碼";

/*
 * EX : http://127.0.0.1/wifiweb/receive.php
 * 		String IP = "127.0.0.1";
 * 		String Path = "wifiweb/receive.php"
 */
String IP = "IP位址";
String Path = "要GET的php檔案名稱";

// 是否要上傳
boolean upload = false;
// 要上傳的數值
int Val = 0;

void setup() {
    Serial.begin(9600); 
    esp8266.begin(115200);  
    
    // fcuntion : ESP-8266初始化
    init_wifi();
}
void loop() {
	Val = int(random(0,20));

    while(Serial.available())
    {
        String input = Serial.readString();
        Serial.println(input);
        if (input == "o\r\n")
        {
            Serial.println("\n|---  Upload Start  ---|");
            upload = true;
        }
        else if (input == "x\r\n")
        {
			Serial.println("\n|---  Upload Stop  ---|");
			upload = false;
        }
        else if (input == "reset\r\n")
        { 
			init_wifi();
			upload = false;
        }
        else
        {
			if(!upload && input.substring(0,2) =="AT"){
				esp8266.println(input);
			}
        }
        input = "";  
    }

    // ESP8266回傳http狀態
	while(esp8266.available())
	{
		Serial.println(esp8266.readString());
	}

	// 是否上傳
	if(upload)
	{ 
		uploadData();
	}
}

//ESP-8266初始化
void init_wifi(){
	Serial.println("=======================================");
	Serial.println("|---  Esp8266 Setting  ---|\n");

	// reset 
	sendCommand("AT+RST",5000); 
   
    /*
   	* 設定ESP-8266模式
	* 1 : Station 模式
	* 2 : AP 模式
	* 3 : Station + AP
	*/
	sendCommand("AT+CWMODE=1",2000); 
	// 連線WiFi
	sendCommand("AT+CWJAP=\""+SID+"\",\""+PWD+"\"",5000);
	// 單通道連線
	sendCommand("AT+CIPMUX=0",2000); 

	Serial.println("\n|---  Setting Finish  ---|");
	Serial.println("=======================================");
	Serial.println(" Please Enter :");
	Serial.println("( 1 )  \" o \" ---> Upload data");
	Serial.println("( 2 )  \" x \" ---> Stop uploading data");
	Serial.println("( 3 )  \" reset \" ---> Reset esp8266");
	Serial.println("( 4 )  \" AT+Command \" ---> Control esp8266");
	Serial.println("======================================="); 
}

//上傳Val資料
void uploadData()
{
	// 建立 TCP 連接
	String cmd = "AT+CIPSTART=\"TCP\",\"";
	cmd += IP;
	cmd += "\",80";
	esp8266.println(cmd);
	delay(1000);

	// 錯誤回傳
	if(esp8266.find("Error")){
		Serial.println("AT+CIPSTART error");
		return;
	}

	// 準備要GET的字串
	String getStr = "GET /"+Path+"?value=";
	getStr += String(Val);
	getStr +=" HTTP/1.1\r\nHost:"+IP;
	getStr += "\r\n\r\n";

	// 發送指定長度的數據
	cmd = "AT+CIPSEND=";
	cmd += String(getStr.length());
	esp8266.println(cmd);

	// 返回 ">"，然後開始傳輸通訊埠數據
	if(esp8266.find(">")){
		esp8266.println(getStr);
	}
	else{
		// 關閉連線
		esp8266.println("AT+CIPCLOSE");
		Serial.println("AT+CIPCLOSE");
	} 
	delay(1000);
}

/* 
 * 向ESP-8266發送指令，有延遲功能
 * sendCommand(指令,延遲時間)
 */
void sendCommand(String command, const int timeout)
{
    String response = "";  
    esp8266.println(command);
    long int time = millis();   
    while( (time+timeout) > millis())
    {
		while(esp8266.available())
		{    
			response = esp8266.readString();
		}  
    }    
    Serial.print(response);
}