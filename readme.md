# 🌟 LED Control with Unity & ESP8266

## 🚀 About the Project  
This project aims to enable **WiFi-based LED control** using **Unity** and **ESP8266**! 🎮💡  

Currently, it is **not fully functional** (and has a few bugs 🤦‍♂️), but it serves as a **prototype**. We can connect to the ESP8266 and change LED colors via Unity. 🖥️📡✨  

## Language Options 🌍
- [Türkçe (Readme)](readme.tr.md)
- [English (Readme)](readme.md)

## 📂 Project Structure  

```
/LedControlProject
    /Autumnoon_UnityApp   -> Unity project (not uploaded due to large file size)
    /ESP8266_Firmware     -> ESP8266 code
    /assets               -> Images and GIFs
```

### 🎮 Autumnoon_UnityApp  
This folder contains the **Unity application**. Through the app, we can connect to the ESP8266 and control LEDs. It includes features like color selection, connection handling, and a basic UI.  

However, **due to the large file size, the Unity project is not uploaded at the moment.** If you wish to access the Unity project, please contact me.

### 🔧 ESP8266_Firmware  
This folder contains **firmware for the ESP8266**. Each file serves a different purpose:

- **`main.ino`** → The main file that defines the core functionality of ESP8266. 📜  
- **`wifiunitycontrol.h`** → Manages the WiFi connection between Unity and ESP. 📡  
- **`ledanimationscontrol.h`** → Handles LED animations. 🌈✨  
- **`lauraanimationlibrary.h`** → A custom library for LED effects. 🏗️  

### 🎨 User Interface  
Here are some GIFs showcasing the connection and main screens:  

<div align="center">
  <table style="margin: auto;">
    <tr>
      <td><img src="assets/gif/connect_screen.gif" alt="Bağlantı Ekranı" width="300"></td>
      <td style="width: 150px;"></td> 
      <td><img src="assets/gif/home_screen.gif" alt="Ana Ekran" width="300"></td>
    </tr>
  </table>
</div>

### 📌 Additional Images  

<div align="center">
    <img src="assets/img/animasyonekranı.png" alt="Animation Screen" width="417.5" style="margin-right: 10px;">
    <img src="assets/img/kayıtekranı.png" alt="Registration Screen" width="383.3" style="margin-right: 10px;">
    <img src="assets/img/setupekranı.png" alt="Setup Screen" width="399.1">
</div>

## ⚠️ Current Status  
✅ We can connect to the ESP8266.  
❌ Not stable—connection issues occur sometimes.  
❌ Needs code improvements and debugging.  

## 📂 Autumnoon_UnityApp Download Notes  
Due to the large file size, the Unity project is not currently uploaded. If you want to access **Autumnoon_UnityApp**, please contact me.