# 🌟 Led Control with Unity & ESP8266

## 🚀 Proje Hakkında
Bu proje, **Unity** ve **ESP8266** kullanarak WiFi üzerinden LED kontrolü sağlamayı amaçlıyor! 🎮💡

Şu an **tam olarak çalışmıyor** (hatta birkaç hata var 🤦‍♂️), ancak bir **prototip** olarak düşünülebilir. ESP8266'ya bağlanarak LED'lerin rengini değiştirebiliyoruz ve Unity üzerinden kontrol edebiliyoruz. 🖥️📡✨

## Dil Seçenekleri 🌍
- [Türkçe (Readme)](readme.tr.md)
- [English (Readme)](readme.md)

## 📂 Proje Yapısı

```
/LedControlProject
    /Autumnoon_UnityApp   -> Unity projesi (yüklenmedi, boyut çok büyük)
    /ESP8266_Firmware     -> ESP8266 kodları
    /assets               -> Görseller ve GIF'ler
```

### 🎮 Autumnoon_UnityApp
Bu klasör, **Unity uygulamamızı** içeriyor. Uygulama aracılığıyla ESP8266'ya bağlanıp LED'leri kontrol edebiliyoruz. Renk seçimi, bağlantı işlemleri ve temel UI burada bulunuyor. Ancak, **Unity projesinin dosya boyutu çok büyük olduğu için şu an bu dosya yüklenememektedir.** Eğer Unity projesini edinmek isterseniz, benimle iletişime geçebilirsiniz.



### 🔧 ESP8266_Firmware
Bu klasör, **ESP8266 için yazılmış firmware** dosyalarını içeriyor. Burada, her dosyanın farklı bir görevi var:

- **`main.ino`** → ESP8266'nın temel çalışma mantığını içeren ana dosya. 📜
- **`wifiunitycontrol.h`** → Unity ile ESP arasındaki WiFi bağlantısını yönetiyor. 📡
- **`ledanimationscontrol.h`** → LED animasyonlarını kontrol eden kodları içeriyor. 🌈✨
- **`lauraanimationlibrary.h`** → LED efektleri için yazılmış özel bir kütüphane. 🏗️

### 🎨 Kullanıcı Arayüzü
Bağlantı ekranı ve ana ekranın nasıl göründüğüne dair bazı GIF'ler aşağıda:

<div align="center">
  <table style="margin: auto;">
    <tr>
      <td><img src="assets/gif/connect_screen.gif" alt="Bağlantı Ekranı" width="300"></td>
      <td style="width: 150px;"></td> 
      <td><img src="assets/gif/home_screen.gif" alt="Ana Ekran" width="300"></td>
    </tr>
  </table>
</div>



### 📌 Diğer Görseller

<div align="center">
    <img src="assets/img/animasyonekranı.png" alt="Animasyon Ekranı" width="417,5" style="margin-right: 10px;">
    <img src="assets/img/kayıtekranı.png" alt="Kayıt Ekranı" width="383,3" style="margin-right: 10px;">
    <img src="assets/img/setupekranı.png" alt="Kurulum Ekranı" width="399,1">
</div>

## ⚠️ Şu Anki Durum
✅ ESP8266'ya bağlanabiliyoruz.  
❌ Stabil değil, bazen bağlantı sorunları yaşanıyor.  
❌ Kodların iyileştirilmesi ve hata ayıklama yapılması gerekiyor.  

## 📂 Autumnoon_UnityApp Yükleme Notları

Unity projesi büyük dosya boyutları nedeniyle şu an yüklenememektedir. Eğer **Autumnoon_UnityApp**'i edinmek isterseniz, lütfen benimle iletişime geçin.
