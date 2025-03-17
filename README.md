# ⚡ EMPOWERING SMART GRID FOR THE FUTURE OF URBAN CENTERS ⚡  

## 🚀 Introduction  
This project focuses on integrating **solar and [wind energy](https://github.com/AhmedBU21EECE0200026/Capstone-Project-EEE-2025-Empowering-Smart-Grid-for-the-future-of-Urban-Centers/tree/60d57e56dd55b29e9b9eb0c78ba2f4bee5c7e864/Capstione%20Project%20Final/Hardware/Wind%20turbine)** with **energy storage** and **automated power management** using **[Arduino Mega and ESP32](https://github.com/AhmedBU21EECE0200026/Capstone-Project-EEE-2025-Empowering-Smart-Grid-for-the-future-of-Urban-Centers/tree/8d3d2d9fe210ea2541f03b2ab503677cac95f9f9/Capstione%20Project%20Final/Code/Mega)**. It dynamically manages power flow between **renewable sources, battery storage, and loads** through **sensors, relays, and power converters**.  

### 🔹 Key Features:  
✅ **Real-time Monitoring & Control** via IoT (Blynk)  
✅ **Automated Power Flow Management** for efficiency  
✅ **Fault Detection & Protection Mechanism**  
✅ **Two-Way Power Flow** for grid integration  
✅ **[Sustainable & Scalable Smart Grid Model](https://github.com/AhmedBU21EECE0200026/Capstone-Project-EEE-2025-Empowering-Smart-Grid-for-the-future-of-Urban-Centers/tree/c1524018e90aeadde82a902a2782c8b8e8453be9/Capstone%20Project%20Introduction/Simulation)**  

Traditional power grids struggle with **renewable energy integration, real-time energy management, and reliability**. This project develops a **scalable smart grid** with **solar, wind, and battery storage**, reducing **fuel dependency and emissions** while leveraging **IoT for real-time monitoring and control**.  

---

## 🎯 Problem Statement  
⚡ **Challenges in Traditional Grids:**  
- Inefficiencies in **renewable energy integration**  
- Lack of **real-time consumption monitoring**  
- **Reliability issues** causing outages  

⚡ **Proposed Solution:**  
- **[Smart Grid Architecture](https://github.com/AhmedBU21EECE0200026/Capstone-Project-EEE-2025-Empowering-Smart-Grid-for-the-future-of-Urban-Centers/blob/8d3d2d9fe210ea2541f03b2ab503677cac95f9f9/Capstione%20Project%20Final/Hardware/Smart%20Grid/Main%20Circuit.jpeg)** integrating **solar, wind, and batteries**  
- **[IoT-Based Monitoring](https://github.com/AhmedBU21EECE0200026/Capstone-Project-EEE-2025-Empowering-Smart-Grid-for-the-future-of-Urban-Centers/blob/8d3d2d9fe210ea2541f03b2ab503677cac95f9f9/Capstione%20Project%20Final/Hardware/Smart%20Grid/Controller%20Circuit.jpeg)** for fault detection & remote control  
- **Optimized Energy Management & Control**  

---

## 🔬 Methodology  
The **smart grid system** integrates **solar, wind, and battery storage** with **automated control** to ensure **efficient energy distribution**.  

### 📌 System Overview:  
- **Capacity:** 🔆 **[50W Solar Panel](https://github.com/AhmedBU21EECE0200026/Capstone-Project-EEE-2025-Empowering-Smart-Grid-for-the-future-of-Urban-Centers/tree/8d3d2d9fe210ea2541f03b2ab503677cac95f9f9/Capstione%20Project%20Final/Hardware/Smart%20Grid)** | 🌬 **[50W Wind Turbine](https://github.com/AhmedBU21EECE0200026/Capstone-Project-EEE-2025-Empowering-Smart-Grid-for-the-future-of-Urban-Centers/tree/8d3d2d9fe210ea2541f03b2ab503677cac95f9f9/Capstione%20Project%20Final/Hardware/Wind%20turbine)**  
- **Storage:** 🔋 **12.8V / 12Ah Battery** | 🔌 **200W Inverter**  
- **Loads:** 🏭 Industrial | 🏡 Domestic | 🔧 Fault Detection  
- **Controllers:** 🖥 **Arduino Mega & ESP32**  

### 🔄 [Operation Workflow](https://github.com/AhmedBU21EECE0200026/Capstone-Project-EEE-2025-Empowering-Smart-Grid-for-the-future-of-Urban-Centers/blob/8d3d2d9fe210ea2541f03b2ab503677cac95f9f9/Capstione%20Project%20Final/Code/Flow%20Chart%20Smart%20Grid.jpeg):  
1. **Sensors** measure **voltage, current, temperature, wind speed, and light intensity**.  
2. **Relays & Power Converters** regulate power distribution.  
3. **ESP32 communicates with Blynk IoT** for real-time monitoring & control.  
4. **Energy flows between Solar, Wind, Battery & Loads** based on demand.  

---

## 🛠️ Tools & Technologies  
### 🖥️ **Hardware:**  
- **Controllers:** Arduino Mega, ESP32  
- **Sensors:** INA260 (Power), DHT22 (Temp), BH1750 (Light), Wind Speed Sensor  
- **Power Components:** Relays, Buck Converter (5A), 200W Inverter  
- **Communication Protocols:** UART, I2C, Wi-Fi  

### 🖥️ **Software & Tools:**  
- **Arduino IDE** – Programming  
- **Blynk** – IoT Dashboard  
- **Lucidchart, Fusion 360** – System Design  
- **I2C Scanner** – Address Verification  

---

## 🔧 Challenges & Solutions  

### ⚙️ Wind Turbine Issues & Fixes  
- **🔹 High BLDC Cost:** Replaced with rewound **DC motor (100W → 50W)**.  
- **🔹 Heavy Rotor & Low Output:** Switched to **lighter aluminum blades**.  
- **🔹 Bearing Damage:** Added **heat-resistant carrying cup**.  
- **🔹 High Gear Ratio Cost:** Optimized to **16:98 ratio** for affordability.  

### ⚡ Smart Grid Setup Fixes  
- **🔹 Relay Power Fluctuations:** Implemented **stable 5V battery supply**.  
- **🔹 Overloaded Buck Converter:** Upgraded from **2A to 5A** for reliable power.  

### 💾 [Code](https://github.com/AhmedBU21EECE0200026/Capstone-Project-EEE-2025-Empowering-Smart-Grid-for-the-future-of-Urban-Centers/tree/8d3d2d9fe210ea2541f03b2ab503677cac95f9f9/Capstione%20Project%20Final/Code) & Communication Fixes  
- **🔹 Pin Assignments:** Used **mapping diagrams & I2C expanders**.  
- **🔹 I2C Conflicts:** Resolved with **I2C scanner** for address verification.  
- **🔹 Code Optimization:** Used **modular functions & flowcharts** for clarity.  
- **🔹 Data Transmission:** Implemented **UART with timing control** for smooth communication.  

---

## 🎯 Conclusion  
The **smart grid system** successfully integrates **renewable energy sources** with **automated energy management** for **improved efficiency, stability, and sustainability**.  

### 🔑 Key Achievements:  
✅ **Hardware Implementation** – Real-world feasibility validated  
🌍 **IoT-Based Monitoring & Control** – Real-time energy management  
☀️🌬 **Optimized Renewable Energy Usage** – Efficient solar & wind integration  
🔋 **Enhanced Battery Storage** – Stable power transitions  
🔄 **Bidirectional Power Flow** – Energy reception & injection into the grid  
⚡ **Advanced Fault Detection & Load Management** – Improved grid resilience  

Compared to **traditional grids**, our **smart grid** offers **higher efficiency, lower emissions, reduced losses, and better fault recovery**, making it a **practical and scalable energy solution**. 🚀  

---

## 🚀 Future Work  
🔹 **AI & Machine Learning** – Automate power distribution & predict energy demand  
🔹 **Blockchain Integration** – Secure & transparent energy transactions  
🔹 **Vehicle-to-Grid (V2G) Support** – Enable EVs to exchange energy with the grid  
🔹 **Edge Computing** – Improve real-time data processing & decision-making  
🔹 **Cybersecurity Measures** – Protect grid from cyber threats  
🔹 **Scalability Testing** – Ensure large-scale deployment efficiency  

By integrating these advancements, the **smart grid can evolve into a fully autonomous, intelligent, and resilient energy network**, paving the way for **sustainable urban energy solutions**. 🌍⚡  

---

## 📌 How to Use  
### 🔹 **Setup & Installation**  
1. **Upload the Code:** Flash the firmware to **Arduino Mega & ESP32**.  
2. **Connect the Components:** Ensure all sensors, relays, and power modules are wired correctly.  
3. **Configure Blynk App:** Set up the dashboard for remote monitoring.  
4. **Power On:** Observe real-time data updates & automated switching.  

### 🔹 **Blynk IoT Dashboard Features**  
- **Monitor Power Flow** 🔋  
- **Control Relays Remotely** 🔄  
- **View Fault Alerts & Grid Status** ⚡  

---

## 🤝 Contributors  
- **A Ahmed**
- **S Siva Kumar**
- **Yaswanth M** 

---

## 📞 Contact  
📧 **aalfaqee@gitam.in**
📧 **sseepala@gitam.in**
📧 **ymunikri@gitam.in**
---

🔥 **Empowering the Future of Smart Grids – One Innovation at a Time!** 🔥  
