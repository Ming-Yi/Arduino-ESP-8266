# Arduino-ESP-8266
使用 Arduino 結合 ESP-8266 建立 WiFi 連線，並且建立一個 HTTP 的 GET Request .   

# 檔案說明:
## Arduino 資料夾
- Arduino_ESP-8266.ino > Arduino + ESP-8266 程式碼

### AT-Test 資料夾

- ESP-8266_AT_Test > ESP-8266 指令測試  

## Php 資料夾
- receive.php > 上傳資料的接收檔
- highchart.html > 利用圖表呈現資料
- database.php > 向資料庫撈取資料傳給網頁
- createtable.php > 快速建立資料庫及資料表

# Version:
1.0.0

#注意事項:
使用Arduino的序列埠監控視窗，記得把右下的下拉選單改成 NL & CR 才能正常使用ESP-8266 .