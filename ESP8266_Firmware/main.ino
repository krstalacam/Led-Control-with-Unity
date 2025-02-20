////////////////////////
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>  

////////////////////////
#include "wifiunitycontrol.h"
#include "ledanimationscontrol.h"
////////////////////////


void setup() {
Serial.begin(115200);
SPIFFS.begin(); // SPIFFS'i başlat
DataUpload(); // verileri yukleme

ledssetup();
//WiFi.setSleepMode(WIFI_MODEM_SLEEP); 
  WiFi.setSleepMode(WIFI_LIGHT_SLEEP); // Light Sleep modunu etkinleştir

  // SPIFFS'ten ssid ve password değerlerini oku
savedSSID = readFile(ssidFile);
savedPassword = readFile(passwordFile);
 Serial.print("savedSSID: ");
  Serial.println(savedSSID);
  Serial.print("savedPassword: ");
  Serial.println(savedPassword);
if (savedSSID == "empty" || savedSSID.length() == 0) {
 
    wifisetup();
}
else {
boolsetup = true;
}
  animationsetup();

FastLED.clear();
  FastLED.setBrightness(20);

  FastLED.show();
}


void loop() {
  
  animationselect();

if (savedSSID == "empty" || savedSSID.length() == 0)  
  wifiloop();
else                //burada neden böyle bir şey var bi kontrol et ikiside sadece server.handleclient kodunu çalıştırıyor
  animationloop();

  serialRead();
  
}
 void serialRead(){

if (Serial.available() > 0) { // Seri porttan veri geldi mi kontrol et
    char receivedChar = Serial.read(); // Veriyi oku
    if (receivedChar == 'a'){


    Serial.print("Received: ");
    Serial.println(receivedChar); // Veriyi seri port üzerinden yazdır
    saveToFile(ssidFile, "empty");
    saveToFile(passwordFile, "empty");
    ResetNodemcu();
    }
    else if (receivedChar == 'b'){

    Serial.print("Received: ");
    Serial.println(receivedChar); // Veriyi seri port üzerinden yazdır
    saveToFile(ssidFile, "TurkTelekom_TP36C2_2.4GHz");
    saveToFile(passwordFile, "VtwcWcqwhd7P");
    ResetNodemcu();

    }
 else if (receivedChar == 'c'){
    for (int i = 0; i < 16 ; i++) { // ColorPaletteCount = 16
    Serial.print("ColorPalette-");
    Serial.print(i);
    Serial.print("- : ");
    Serial.print( ColorPalette[i].h); // Veriyi seri port üzerinden yazdır
    Serial.print(", ");
    Serial.print( ColorPalette[i].s); // Veriyi seri port üzerinden yazdır
    Serial.print(", ");
    Serial.println( ColorPalette[i].v); // Veriyi seri port üzerinden yazdır
    }

  

    }
  }
}
void ResetNodemcu(){
  
  Serial.println("Resetleniyor..."); // Veriyi seri port üzerinden yazdır

  ESP.restart();

}
void DataUpload(){



}






