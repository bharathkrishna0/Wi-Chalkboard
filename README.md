
# 🧠 Wi-Chalkboard – A Zero-Hardware Offline Message Board Using ESP32-C3

**Wi-Chalkboard** is a minimalist, zero-component project that turns your ESP32-C3 board into a **wireless digital chalkboard** — no sensors, no displays, no internet. Just power it on, and anyone nearby can connect to it over Wi-Fi and leave a message via their browser!

---



## 🚀 Features

- 📡 Creates its own **Wi-Fi hotspot** — no router or internet needed
- 📝 Hosts a **webpage where users can submit messages**
- 🧠 Stores and displays the latest messages in a scrollable board
- 🔐 Optional: "Admin" page to clear messages or reboot
- 💾 Messages stored in RAM or flash (adjustable)
- 🌙 Optional: Auto-reset board every 24 hours

---

## 🛠️ What You Need

- ✅ 1 × **ESP32-C3 dev board** (no external components)
- ✅ 1 × USB cable and serial monitor for debugging (optional)
- 📱 Any smartphone or laptop to connect and post messages

---

## 📦 File Structure

```

Wi-Chalkboard/
├── WiChalkboard.ino         # Main Arduino sketch
├── web\_page.h               # Embedded HTML/JS for message board
├── data/                    # (Optional) For SPIFFS if serving web files
├── README.md                # You're here!

````

---

## 🔧 How It Works

1. ESP32-C3 boots and starts a Wi-Fi Access Point (`WiChalk`).
2. A built-in web server serves the message submission page.
3. Any device that connects will land on a captive-portal-style interface.
4. Users type a message → ESP32 saves it → all messages shown on board.
5. [Optional] Admin tools allow clearing/resetting board manually or on schedule.

---

## 📄 Example Use Cases

- 🏫 Offline classroom message board
- 🎉 Event check-in shoutouts
- 🏠 PG/hostel common area feedback wall
- 🌐 IoT guestbook for your room/lab

---

## 🧠 Code Preview

```cpp
WiFi.softAP("WiChalk", "wipassword");
server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
});
server.on("/submit", HTTP_POST, handleFormSubmit);
````

(Full code in `WiChalkboard.ino` and `web_page.h`)

---

## 🎥 1-Minute Project Demo (For Seeed Submission)

> *"This is Wi-Chalkboard – a zero-hardware digital message board built using just ESP32-C3. It creates its own Wi-Fi, hosts a mini website, and lets anyone nearby leave a message right from their phone. Perfect for fests, classrooms, or dorms – no sensors, no cloud, no extras — just code and creativity!"*

---

## ✅ Future Add-ons (Optional)

* ✨ WebSocket real-time updates
* 🌐 Connect to internet and sync logs to Supabase
* 🔊 Add Grove speaker for audio alerts (for Seeed bonus points!)
* 🔒 Add user authentication

---

## 🧑‍💻 Author

Made by Bharath Krishna, for the Seeed Interactive Signage Contest.
ESP32 magic, zero wires, 100% local.

---

