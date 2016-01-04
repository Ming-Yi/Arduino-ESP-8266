#include <SoftwareSerial.h>

SoftwareSerial esp8266(8,9);

String SID = "AP名稱";
String PWD = "AP密碼";

/*
 * EX : http://127.0.0.1/wifiweb/receive.php?value=5
 *     String IP = "127.0.0.1";
 *    String Path = "wifiweb/receive.php?value="
 */
String IP = "IP位址";
String Path = "php檔案?GET參數";

void setup() {
    Serial.begin(9600); 
    esp8266.begin(115200);
    wifi_init();
}

void loop()
{
	int Val = int(random(0,1023));
	uploadData(Val);
}

void wifi_init(){
  sendCommand("AT+RST",2000); 
  sendCommand("AT+CWMODE=1",1000); 
  sendCommand("AT+CWJAP=\""+SID+"\",\""+PWD+"\"",3000);
  sendCommand("AT+CIPMUX=0",1000); 
}

void sendCommand(String command, const int timeout)
{
    String response = "";
    Serial.println('>'+command);
    esp8266.println(command);
    long int time = millis();   
    while( (time+timeout) > millis())
    {
	    while(esp8266.available())
	    {    
	      response = esp8266.readString();
	    }  
    }    
    Serial.println(response);
}

void uploadData(int value)
{
	// 建立 TCP 連接
	String cmd = "AT+CIPSTART=\"TCP\",\""+IP+"\",80";
	esp8266.println(cmd);
	Serial.println(cmd);

	// 錯誤回傳
	if(esp8266.find("Error")){
		Serial.println("AT+CIPSTART error");
		return;
	}

  	// 準備要GET的字串
    // HTTP/1.1
  	String getstr = "GET /"+Path+String(value)+" HTTP/1.1\r\nHost:"+IP+"\r\n\r\n";

    // HTTP/1.0
    //String getstr = "GET /"+Path+String(value)+" HTTP/1.0\r\n\r\n\r\n";

	// 發送指定長度的數據
	cmd = "AT+CIPSEND="+String(getstr.length());
	esp8266.println(cmd);
	//Serial.println("length: "+cmd);
	delay(1000);

  	// 長度的數據傳送成功，會返回 ">"，然後開始傳輸通訊埠數據
	if(esp8266.find(">")){
		Serial.println("> "+getstr);
	}
	else{
		// 關閉連線
		esp8266.println("AT+CIPCLOSE");
		Serial.println("AT+CIPCLOSE  connection closed!\r\n\r\n");
		delay(2000);
		return;
	} 
	esp8266.println(getstr);
	delay(2000);
}