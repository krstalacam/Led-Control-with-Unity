#ifndef lauraanimationlibrary_h
#define lauraanimationlibrary_h

#include <Arduino.h>
#include <FastLED.h>

///////////////////////////////////////////////////////////////////////////////////
void ledssetup();
void animationsettersI(uint8_t _LedRow, CHSV Color);
void animationsettersanimationI(String AnimationName, uint8_t _LedRow, CHSV Colors[6]);
void animationselect();
void changeLEDOrder();
void LedIntervalShow();
void animationshow();
///////////////////////////Effects/////////////////////////////////////////////
void Wave();
void SolidColor();
void Blink();
void ColorWipe( );
void Rainbow();
void RainbowCycle();
void TheaterChase( );
void TheaterChaseRainbow();

///////////////////////////////////////////////////////////////////////////////////
#endif

///////////////////////////////////////////////////////////////////////////////////

#define RED (uint32_t)0xFF0000
#define GREEN (uint32_t)0x00FF00
#define BLUE (uint32_t)0x0000FF
#define WHITE (uint32_t)0xFFFFFF
#define BLACK (uint32_t)0x000000
#define YELLOW (uint32_t)0xFFFF00
#define CYAN (uint32_t)0x00FFFF
#define MAGENTA (uint32_t)0xFF00FF
#define PURPLE (uint32_t)0x400080
#define ORANGE (uint32_t)0xFF3000
#define PINK (uint32_t)0xFF1493
#define GRAY (uint32_t)0x101010
#define ULTRAWHITE (uint32_t)0xFFFFFFFF
#define DIM(c) (uint32_t)((c >> 2) & 0x3f3f3f3f)   // color at 25% intensity
#define DARK(c) (uint32_t)((c >> 4) & 0x0f0f0f0f)  // color at  6% intensity

///////////////////////////////////////////////////////////////////////////////////
#define DATA_PIN D4
#define COLOR_ORDER GRB
#define CHIPSET WS2812B
#define BRIGHTNESS 200
CRGB leds[90];  // yani en fazla 90/3 = 30 tane üçgene izin veriyor
CRGB templeds[90];    // Geçici dizi
CHSV ColorPalette[16];

int numleds = 9;
///////////////////////////////////////////////////////////////////////////////////
bool ledState = false;
int ledlist[90];  // burasini sonra ayarla en fazla kac ucgen olacaksa onu 6 ile carp ve buraya yaz // su an kullanilmiyor

String effects[] = {
  "SolidColor",
  "Blink",
  "ColorWipe",
  "Rainbow",
  "RainbowCycle",
  "TheaterChase",
  "TheaterChaseRainbow",
  "Scanner",
  "Fade",
  "RunningLights",
  "Twinkle",
  "TwinkleRandom",
  "Sparkle",
  "SnowSparkle",
  "DotBeat",
  "Fire",
  "MeteorRain",
  "Fireworks",
  "FireworksRandom",
  "FireFlicker",
  "FireFlickerSoft",
  "FireFlickerIntense",
  "HalloweenEyes",
  "CylonBounce",
  "NewKITT",
  "TwinkleFox",
  "TwinkleCat",
  "RunningFox"
};
///////////////////////////Constructors////////////////////////////////////////////
class LedInformation {
public:
  CHSV Color = CHSV(200, 255, 255);  // tek led için
  uint16_t Count = 256;              //  tek led için

  CHSV startcolor = CHSV(100, 255, 255);  // tek led için
};

class LedAnimationInformation {
public:
  String AnimationName;
  CHSV Colors[6];    

};
//////////////////////////////Objects///////////////////////////////////////////////
LedInformation ledI[90];
LedAnimationInformation ledanimationI[90];
uint8_t LedRow = 100;
uint8_t LedInterval = 1;
uint8_t DelayTime = 100; //0 ile 255 arasinda yaptik ama duruma gore degisebilir ayarlarsin onu 

//bool isnoanimation; // animasyon mu yoksa solid color yani renk degisme modu mu onu gosterir

///////////////////////////////////////////////////////////////////////////////////
void ledssetup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, numleds);

  FastLED.clear();
  FastLED.setBrightness(20);
  leds[5] = CHSV(100, 155, 255);

  FastLED.show();
}
////////////////////////Set Setters Now//////////////////////////////////////////////
void animationsettersI(uint8_t _ledrow, CHSV color) {
  ledI[_ledrow].Color = color;
  ledI[_ledrow].Count = 0;

 
}
void animationsettersanimationI(String animationName, uint8_t _ledrow, CHSV colors[6]) {
  ledanimationI[_ledrow].AnimationName = animationName;
    for (int i = 0; i < 6 ; i++) ledanimationI[_ledrow].Colors[i] = colors[i];

}

void animationselect() {
 // Serial.println(LedRow);
 //Serial.println(ledI[LedRow].AnimationName);
     SolidColor();

EVERY_N_MILLIS(DelayTime) {
  if (ledI[LedRow].Count > 255){
    if (ledanimationI[LedRow].AnimationName == "Wave") Wave();
    else if (ledanimationI[LedRow].AnimationName == effects[2]) ColorWipe();
    else if (ledanimationI[LedRow].AnimationName == effects[3]) Rainbow();
    else if (ledanimationI[LedRow].AnimationName == effects[4]) RainbowCycle();
    else if (ledanimationI[LedRow].AnimationName == effects[5]) TheaterChase();
 }
}
   
}

void changeLEDOrder() {  //bunu kullanmiyorum ama belki ayna efekti falan yaparsan kullanirsin diye silmedim
  CRGB temp[numleds];    // Geçici dizi
  // Leds dizisini geçici diziye kopyala

  for (int i = 0; i < numleds / LedInterval ; i++) {
    temp[i] = leds[ledlist[i]];
  }

  // Geçici diziyi leds dizisine kopyala
  for (int i = 0; i < numleds / LedInterval ; i++) {
    leds[i] = temp[i];
  }
}
void LedIntervalShow() {     //bunu kullanmiyorum bu fonksiyon fastled show yerine kullanilarak ledlerin sirasini degistiriyor mesela 3 er 3 er ya da 1 er 1 er seklinde
  //bu kod ise yariyor ama unutma ki animasyonun fonksiyonunda da döngüyü LedInterval degıskenine bölerek bu fonksıyona yardımcı olmalısın yoksa sıkıntı olur
 for (int i = 0; i < numleds ; i++) {
    templeds[i] =  rgb2hsv_approximate(leds[i]);
  } 
   if (LedInterval > 1){
   for (int i = 0; i < numleds / LedInterval ; i++) { 
      for (int j = 0; j < LedInterval ; j++) {  
            leds[(i*LedInterval)+j] = templeds[i];
          }
    }
  }
   FastLED.show(); 
}

void ChangeColorToSolidColor(uint8_t colorSize) {
  // numleds = 18
  int groupNumleds = numleds/3; // 6
   //ledI[LedRow].Count = 0; // bu kod sanirim olmali kontrol et UYARI SON
  //for (int i = 0; i < 6 ; i++)  ColorPalette[i] = ledanimationI[LedRow].Colors[0] ;
  if(colorSize==2){
    for (int i = 0; i < 16 ; i++) { // ColorPaletteCount = 16
       CHSV color = blend(ledanimationI[LedRow].Colors[0], ledanimationI[LedRow].Colors[5], i*255/15); 
       ColorPalette[i] = color;

      }
      
  }
  else{
    for (int i = 0; i < 5 ; i++) { // ColorPaletteCount = 16
      // CHSV color = blend(ledanimationI[LedRow].Colors[0], ledanimationI[LedRow].Colors[1], i*255/(groupNumleds-1)); 
        for (int j = 0; j < 3 ; j++) { // ColorPaletteCount = 16
          CHSV color = blend(ledanimationI[LedRow].Colors[i], ledanimationI[LedRow].Colors[i+1], j*255/3); 
          ColorPalette[i*3+j] = color;
       }

      }
        ColorPalette[15] = ledanimationI[LedRow].Colors[5];
       
  }

  for (int i = 0; i < groupNumleds ; i++) {
    int mapingvalue = map(i, 0, groupNumleds-1, 0, 15);
    for (int j = 0; j < 3 ; j++)  animationsettersI((i*3)+j, ColorPalette[mapingvalue] );
  }

}
void SolidColor() {
  for (int i = 0; i < numleds ; i++) {
    //if (i == LedRow) animationstatus = true;

    if (ledI[i].Count > 255) continue;
    if (ledI[i].Count == 0) ledI[i].startcolor = rgb2hsv_approximate(leds[i]);

    CHSV color = blend(ledI[i].startcolor, ledI[i].Color, ledI[i].Count);
    leds[i] = color;
    ledI[i].Count++;
    //if (i == LedRow)  animationstatus = false;
    //Serial.print("Animation Name: ");
    //Serial.println(ledI[LedRow].AnimationName);
  }
   FastLED.show();
}

void Blink() {
  EVERY_N_MILLIS(2000) {

    if (ledState) {
      for (int i = 0; i < numleds / LedInterval; i++) {
        leds[i] = CRGB(random8() / 2, random8(), random8() / 2);
      }
      ledState = false;
    } else {

     for (int i = 0; i < numleds / LedInterval ; i++) {
        leds[i] = CRGB::Black;
      }
      ledState = true;
    }
  }
  LedIntervalShow(); 
}

void ColorWipe() {
  for (int i = 0; i < numleds / LedInterval ; i++) {
    leds[i] = ledI[LedRow].Color;
  LedIntervalShow(); 
    delay(50);
  }
}

void Rainbow() {
  Serial.println("rainbow");

  uint8_t hue = 0;

  for (int i = 0; i < numleds / LedInterval ; i++) {
    leds[i] = CHSV(hue, 255, 255);  // Hue, Saturation, Value (Parlaklık) değerleri kullanılarak renk oluşturuluyor
    hue += 256 / numleds;
  }

  LedIntervalShow(); 
  delay(50);
  Serial.println("delay");
}
void RainbowCycle() {
  static uint8_t hue = 0;

  for (int i = 0; i < numleds / LedInterval ; i++) {
    leds[i] = CHSV(hue + (i * 255 / numleds), 255, 255);  // Hue, Saturation, Value (Parlaklık) değerleri kullanılarak renk oluşturuluyor
  }

  LedIntervalShow(); 
  delay(50);



  hue += 4;  // Renk döngüsünün hızını ayarlamak için bu değeri değiştirebilirsiniz
}

void TheaterChase( ) {
  for (int j = 0; j < 10; j++) {
    for (int q = 0; q < 3; q++) {
      for (int i = 0; i < numleds; i = i + 3) {
        leds[i + q] = ledI[LedRow].Color;;
      }
    LedIntervalShow(); 

      delay(50);

      for (int i = 0; i < numleds; i = i + 3) {
        leds[i + q] = CRGB::Black;
      }
    }
  }
}

void TheaterChaseRainbow() {    // Burada 3 er 3 er olsun diye fazladan for eklemisim sanirim  efekti test ederken  bunu duzeltirsin
  int rainbowStep = 256 / numleds / LedInterval;
  int hue = 0;

  for (int j = 0; j < 256; j += rainbowStep) {
    for (int q = 0; q < 3; q++) {
      for (int i = 0; i < numleds / LedInterval; i = i + 3) {
        leds[i + q] = CHSV((hue + j) % 256, 255, 255);
      }
    LedIntervalShow(); 
      delay(50);


      for (int i = 0; i < numleds / LedInterval; i = i + 3) {
        leds[i + q] = CRGB::Black;
      }
    }
  }

  hue += 1;  // Renk kayması hızını ayarlamak için bu değeri değiştirebilirsiniz
}
//////////////////////Effects//////////////////////
int artis=0;

void Wave(){

 int oran = 255/(18-1); // 15

  if (artis == 18) {  //18 olmasiyla numleds in alakasi yok bu bir sabit
    templeds[numleds] = leds[0];
  for (int i = 0; i < numleds; i++) templeds[i] = leds[i]; 

    Serial.println("beginhareket");
  }

  if(artis == 18) artis = 0;

  for (int j = 0 ; j < numleds; j++) {
    CRGB color = blend(templeds[j], templeds[j+1], artis*oran); 
    leds[j]= color;
    
  }
  artis++;
  FastLED.show();

}
