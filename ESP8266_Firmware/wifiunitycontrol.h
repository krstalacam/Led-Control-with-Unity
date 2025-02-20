#ifndef wifiunitycontrol_h
#define wifiunitycontrol_h

#include <Arduino.h>


void wifisetup();
void wifiloop();

void WifiConnectionStatus();
void wificonnect();
void handleData();
void handleWiFiList();
String getWiFiListJSON();
String readFile();
void saveToFile(const char* fileName, const char* data); // Parametreler düzeltilmiş burada


#endif
ESP8266WebServer server(80);

const char*  ssidFile = "/ssid.txt";
const char*  passwordFile = "/password.txt";
String savedSSID;
String savedPassword;
bool boolsetup;
/////////////////
const char* ssid = "empty"; //TurkTelekom_ZKXRW
const char* password = "empty"; //fakay1976
const char *APssid = "Laura"; // WiFi ağı adı
String status;

unsigned long connectStartTime; // Bağlantı deneme başlama zamanı
const unsigned long maxConnectTime = 15000; // 10 saniye

void wifisetup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  WiFi.mode(WIFI_AP); // NodeMCU, Access Point (AP) modunda çalışacak
  WiFi.softAP(APssid,"12345678");

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("Access Point IP adresi: ");
  Serial.println(myIP);
  //server.on("/mac", handleMacAddress); // WiFi listesini almak için yeni bir endpoint oluştur
  server.on("/wifilist", handleWiFiList); // WiFi listesini almak için yeni bir endpoint oluştur
  server.on("/send", handleData); // WiFi listesini almak için yeni bir endpoint oluştur
  server.on("/wifistatus", WifiConnectionStatus); 

  //server.begin(); // İlk sunucuyu başlat

  

}

void wifiloop() {
   server.handleClient();
  
/*
    if (wifiAPoff) {
      deneme = true;
      if (server.client()) {
          if (millis() - connectStartTime >= maxConnectTime) {
                Serial.println("WiFi'ye AP kapatildi. 10 saniye geçti.");

                //wifiserverclose();
                //server.stop();
           //WiFi.softAPdisconnect(false);

               //WiFi.mode(WIFI_STA); 
                wifiAPoff =false;
                Serial.println("WIFIapOK.");
              }
         }
    }
         */

}
void WifiConnectionStatus() {

    server.send(200, "text/plain", status);
}

void wificonnect(){
  digitalWrite(LED_BUILTIN, LOW);
        delay(400);    
  digitalWrite(LED_BUILTIN, HIGH);
 
  int attemptCount = 0;
  

  WiFi.disconnect(); // WiFi bağlantısını kapat
  WiFi.begin(ssid, password);

  connectStartTime = millis(); // Bağlantı deneme başlama zamanını kaydet

 while (WiFi.status() != WL_CONNECTED) {
    if (millis() - connectStartTime >= maxConnectTime) {
      Serial.println("WiFi'ye bağlanma başarısız. 10 saniye geçti.");
      status = "0";
      
      ssid = "empty"; 
      password = "empty"; 
      saveToFile(ssidFile, ssid);
      saveToFile(passwordFile, password);
            
      break;
    }

    delay(100);
    Serial.println("WiFi'ye bağlanıyor...");
    attemptCount++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("WiFi'ye başarıyla bağlandı.");
    // Burada diğer işlemleri yapabilirsiniz.
    status = "1";
    //delay(3000);
    Serial.print("attemptCount: ");
    Serial.println(attemptCount);
    Serial.print("millis(): ");
    Serial.println(millis()-connectStartTime);
    connectStartTime = millis(); // Bağlantı deneme başlama zamanını kaydet

    //wifiAPoff=true;

    saveToFile(ssidFile, ssid);
    saveToFile(passwordFile, password);

    WiFi.mode(WIFI_STA);

  }

  /*
   Serial.print("data: ");
   Serial.println(data);

    switch (data) {
    case 0:
    handleMacAddress();
      // Data 1 ise bu kod bloğu çalışır
      Serial.println("Data is 1");
      break;
    case 2:
    handleWiFiList();
      // Data 2 ise bu kod bloğu çalışır
      Serial.println("Data is 2");
      break;
    case 3:
      // Data 3 ise bu kod bloğu çalışır
      Serial.println("Data is 3");
      break;
   */
  }
    
void handleData() {
 // data = server.arg("data").toInt();  // Integer alanından veriyi 
  //data1 = server.arg("data1").toInt();  // Integer alanından veriyi 

  ssid = server.arg("ssid").c_str();  // String alanından veriyi alma ve const char* türüne çevirme
  password = server.arg("password").c_str();  // String alanından veriyi alma ve const char* türüne çevirme

  server.send(200, "text/html", "OK");  
  //Serial.print("data: ");
  //Serial.println(data);
  
  Serial.print("ssid: ");
  Serial.println(ssid);
  Serial.print("password: ");
  Serial.println(password);

  wificonnect();
  
}


void handleWiFiList(){
  String wifiList = getWiFiListJSON(); // Çevredeki WiFi ağlarının listesini JSON formatında al

  server.send(200, "application/json", wifiList); // JSON verisini Unity'e gönder
}

String getWiFiListJSON(){
  DynamicJsonDocument jsonDoc(2048); // JSON belgesi için bellek ayırmak

  // WiFi.scanNetworks () ile çevredeki WiFi ağlarını tespit edin
  int n = WiFi.scanNetworks();
  if(n>8)
     n=8;
  // JSON belgesine WiFi ağlarını ekleyin
  JsonArray wifiArray = jsonDoc.to<JsonArray>();
  for (int i = 0; i < n; i++)
  {
    JsonObject wifiObj = wifiArray.createNestedObject();
    wifiObj["ssid"] = WiFi.SSID(i);
  }

  // JSON verisini string olarak döndürün
  String jsonData;
  serializeJson(jsonDoc, jsonData);
  return jsonData;
}

String readFile(const char* fileName) {
  File file = SPIFFS.open(fileName, "r");
  if (!file) {
    Serial.println("Dosya açılamadı");
    return "";
  }

  String content = file.readString();
  file.close();
  return content;
}

void saveToFile(const char* fileName, const char* data) {
  File file = SPIFFS.open(fileName, "w");
  if (!file) {
    Serial.println("Dosya açılamadı");
    return;
  }

  file.print(data);
  file.close();
}









