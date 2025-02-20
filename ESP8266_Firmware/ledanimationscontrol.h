#ifndef ledanimationscontrol_h
#define ledanimationscontrol_h

#include <Arduino.h>
#include "lauraanimationlibrary.h"



void animationsetup();
void animationloop();
void handleMacAddressnumleds();
void handleDataAnimation();
extern void serialRead();

#endif


// const char* macAddress,jsonString;
//DynamicJsonDocument doc(1024);
StaticJsonDocument<1024> doc;  // 1024 byte'lık bir yığın bellek ayırır
bool isClientConnected = true;
JsonArray jsonArray;
CHSV Colors[6] = {
  CHSV(0, 255, 255),   // Kırmızı
  CHSV(255, 255, 255),  // Sarı
  CHSV(255, 255, 255), // Yeşil
  CHSV(255, 255, 255), // Mavi
  CHSV(255, 255, 255),  // Mor
  CHSV(255, 255, 255)  // Mor
};   
void animationsetup() {
  WiFi.begin(savedSSID, savedPassword);

  if (boolsetup) {
    Serial.println("boolsetup");

    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.println("WiFi'ye bağlanıyor...");
      serialRead();
    }
    Serial.println("WiFi bağlantısı başarıyla gerçekleşti");
  }

  Serial.print("IP adresi: ");
  Serial.println(WiFi.localIP());

  Serial.print("Mac Address: ");
  Serial.println(WiFi.macAddress());
  server.on("/" + WiFi.macAddress(), handleDataAnimation);
  server.on("/mac", handleMacAddressnumleds);
  server.begin();  // İlk sunucuyu başlat
  Serial.println("ledanimationscontrol setup");
}

void animationloop() {
  server.handleClient();
}
void handleMacAddressnumleds() {
  String response = WiFi.macAddress() + "\n" + numleds;

  server.send(200, "text/plain", response);
}
void handleDataAnimation() {
  server.send(200, "text/html", "OK");
  String jsonString = server.arg("jsonString");                                    // Integer alanından veriyi alma
  if (server.arg("numleds").toInt() > 1) numleds = server.arg("numleds").toInt();  // Integer alanından veriyi alma

  if (numleds > 1) {
    //Serial.print("numleds: ");
    //Serial.println(numleds);
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, numleds);  // LED sayısını güncelleyin
  }

  if (jsonString.length() > 0) {
    // Veri geldiyse işlemleri burada yapabilirsiniz
    deserializeJson(doc, jsonString);

    jsonArray = doc.as<JsonArray>();
    for (int i = 0; i < jsonArray.size(); i++) {
      JsonObject obj = jsonArray[i];
      String AnimationName = obj["AnimationName"];
      LedRow = obj["LedRow"];            // kacinci led oldugu
      LedInterval = obj["LedInterval"];  // kac grup oldugu
      DelayTime = obj["DelayTime"];     // effect bekleme hızı

      JsonArray colors = doc[0]["Colors"].as<JsonArray>();

    if  (AnimationName == "SolidColor") {
        int hue = colors[0]["h"];
        int saturation = colors[0]["s"];
        int value = colors[0]["v"];

        Colors[0] = CHSV(hue, saturation, value);

        if (LedInterval == 3){
        LedRow = LedRow*3;            // kacinci led oldugu

          for (int j = 0; j < 3 ; j++)   
            animationsettersI(LedRow+j, Colors[0]);  
        }
        else{

          animationsettersI(LedRow, Colors[0]);  // O anki efektin olduğu constructor'ı değiştiriyor
        }
    }
    else if  (colors.size() == 0) {

      artis=18;
      animationsettersanimationI(AnimationName,LedRow,Colors);

    }
    else{
      
    if (colors.size() == 2) {     //burada eger 2 ise arasini doldurmasi seklinde yapmisiz ama unity de renkleri karistir yapinca sıkıntı olacak
      for (int j = 0; j < colors.size(); j++) {
            int hue = colors[j]["h"];
            int saturation = colors[j]["s"];
            int value = colors[j]["v"];

            Colors[j*5] = CHSV(hue, saturation, value);
        }
        for (int j = 1; j < 5; j++) {
            CHSV color = blend(Colors[0], Colors[5], j*51);

            Colors[j] = color;

        }
    }
    else {
      
      for (int j = 0; j < colors.size(); j++) {
        int hue = colors[j]["h"];
        int saturation = colors[j]["s"];
        int value = colors[j]["v"];

        Colors[j] = CHSV(hue, saturation, value);
        //ColorPalette[i] = CHSV(hue, saturation, value);
        
      }
    }
      animationsettersanimationI(AnimationName,LedRow,Colors);
      ChangeColorToSolidColor(colors.size());


   }
      artis=18;

  }
}
}
