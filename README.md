# 🚨 Smart Bike Safety System

A **Smart Bike Safety System** for motor bikes using a **dual-microcontroller architecture**.  
The system detects theft attempts, abnormal movement, crash events, and **rider alcohol consumption**, sends **real-time alerts with GPS location** to the owner via **GSM**, and can **remotely disable the engine** for enhanced safety and security.

## 📌 Project Overview

Motor bike theft, unsafe riding, and delayed accident response remain major challenges.  
This project presents a **smart embedded safety and anti-theft solution** using **ESP32-based controllers**, inertial sensing, alcohol detection, GPS tracking, and GSM communication.

The system is divided into:

- **Master Unit (ESP32)** – Handles GPS tracking, GSM communication, crash detection, theft response, and engine cutoff.  
- **Slave Unit (ESP32-C3 Mini)** – Dedicated to rider safety monitoring, including alcohol detection and environmental sensing.

This modular design improves **reliability, power efficiency, fault isolation, and scalability**.

## ⚙️ System Functionality & Working

The Smart Bike Safety System operates using a **distributed dual-controller architecture** to ensure reliable monitoring and fast response. The **ESP32 Master unit**, powered directly from the bike battery, acts as the central control node responsible for decision-making, communication, and engine control. It interfaces with a **SIM900A GSM module** for SMS alerts, a **NEO-M8N GPS module** for real-time location tracking, a **5V relay** for engine cutoff, and an **MPU6050 inertial sensor** for detecting crash events and abnormal vehicle motion.

A secondary **ESP32-C3 Mini Slave unit**, powered by a rechargeable 5V battery, focuses on **rider safety monitoring**. It continuously measures alcohol concentration using the **MQ-3 alcohol sensor** and environmental conditions using the **DHT22 temperature and humidity sensor**. The Slave unit communicates safety status data wirelessly to the Master using **ESP-NOW**, enabling low-latency and power-efficient data transfer without relying on external networks.

During operation, the system continuously evaluates inputs from both controllers. If **alcohol consumption exceeds a predefined threshold**, a **crash is detected**, or **unauthorized movement** is identified, the Master unit immediately retrieves GPS coordinates and sends an **SMS alert via GSM** to the registered user. In critical scenarios, the system activates the **engine cutoff relay**, preventing the bike from being started or continuing operation. This integrated approach ensures **theft prevention, rider safety, and rapid incident notification** in a single embedded solution.

## 🎯 Objectives

- Detect unauthorized movement or theft attempts  
- Detect crash events using inertial sensing  
- Detect rider alcohol consumption before or during riding  
- Send real-time SMS alerts with GPS location  
- Remotely disable the bike engine when unsafe conditions are detected  
- Implement a low-cost, embedded IoT-based safety system  

## 🧠 System Architecture
            ┌────────────────────────────┐
            │        ESP32 MASTER        │
            │─────────────────────────── │
            │ • GSM (SIM900A)            │
            │ • GPS (NEO-M8N)            │
            │ • MPU6050 (Crash Detection)│
            │ • Engine Cutoff Relay      │
            │ • Alert & Control Logic    │
            └───────────▲────────────────┘
                        │ ESP-NOW
            ┌───────────┴────────────────┐
            │       ESP32-C3 MINI SLAVE  │
            │────────────────────────────│
            │ • MQ-3 (Alcohol Detection) │
            │ • DHT22 (Temp & Humidity)  │
            │ • Rider Safety Monitoring  │
            └────────────────────────────┘
            


## 🔧 Hardware Components

### 🔹 Master Unit (ESP32)

| Component | Description |
|---------|------------|
| ESP32 | Main controller |
| SIM900A GSM Module | SMS alert communication |
| NEO-M8N GPS Module | Real-time location tracking |
| MPU6050 | Crash and abnormal motion detection |
| 5V Relay Module | Engine cutoff control |
| Power Source | Motor bike 12V battery (regulated) |

### 🔹 Slave Unit (ESP32-C3 Mini)

| Component | Description |
|---------|------------|
| ESP32-C3 Mini | Secondary controller |
| MQ-3 Alcohol Sensor | Rider alcohol detection |
| DHT22 | Temperature & humidity monitoring |
| Power Source | 5V rechargeable battery |

## 🧭 Schematic

![Schematic](https://github.com/HR-Hari/Smart-Bike-Safety-System/blob/c28a9280bdd922c1ce59415980f616e76a79e5f7/Images/Schematic%20Diagram.PNG)

## 🖼 PCB & Enclosure Design

### 🔹 Master Unit PCB Design
<table>
  <tr>
    <td>
      <img src="https://github.com/HR-Hari/Smart-Bike-Safety-System/blob/c28a9280bdd922c1ce59415980f616e76a79e5f7/Images/Master%20PCB.PNG" 
           alt="Master PCB" width="400"/>
    </td>
    <td>
      <img src="https://github.com/HR-Hari/Smart-Bike-Safety-System/blob/c28a9280bdd922c1ce59415980f616e76a79e5f7/Images/Master%203D%20view.PNG" 
           alt="Master 3D view" width="400"/>
    </td>
  </tr>
</table>


### 🔹 Slave Unit PCB Design

<table>
  <tr>
    <td>
      <img src="https://github.com/HR-Hari/Smart-Bike-Safety-System/blob/c28a9280bdd922c1ce59415980f616e76a79e5f7/Images/Slave%20PCB.PNG" 
           alt="Slave PCB" width="400"/>
    </td>
    <td>
      <img src="https://github.com/HR-Hari/Smart-Bike-Safety-System/blob/c28a9280bdd922c1ce59415980f616e76a79e5f7/Images/Slave%203D%20view.PNG" 
           alt="Slave 3D view" width="400"/>
    </td>
  </tr>
</table>

### 📥 Master & Slave Enclosure / Casing
### 🔹 Master Unit Casing
![Schematic](Images/Master-Casing.png)
### 🔹 Slave Unit Casing
![Schematic](Images/Slave-Casing.png)

## ⚙️ Software & Technologies

- **Programming Language**: C / C++
- **IDE**: Arduino IDE
- **Wireless Communication**:
  - ESP-NOW (ESP32 ↔ ESP32-C3)
- **Serial Communication**:
  - UART (ESP32 ↔ GSM)
  - UART (ESP32 ↔ GPS)
- **Core Concepts**:
  - Embedded Systems
  - IoT-based Vehicle Safety
  - Sensor Interfacing
  - Real-time Event Detection
  - Power Management

## 🚀 Key Features

- 🔐 Theft detection through abnormal motion analysis  
- 🚑 Crash detection using MPU6050  
- 🍺 Alcohol detection using MQ-3 sensor  
- 🌡️ Environmental monitoring using DHT22  
- 📍 GPS-based real-time location sharing  
- 📩 SMS alerts via GSM (SIM900A)  
- 🔌 Engine immobilization using relay  
- 🔋 Dual power supply for uninterrupted operation  

## 📂 Project Structure

## 🧪 Testing & Validation

- Unauthorized movement and theft detection  
- Crash detection sensitivity tuning  
- Alcohol threshold calibration  
- GSM SMS delivery reliability  
- GPS fix accuracy and response time  
- Engine cutoff activation timing  

System validated under real motor bike operating conditions.

## 📈 Future Enhancements

- Mobile application integration  
- Cloud-based real-time tracking dashboard  
- Rider authentication using BLE or RFID  
- Geofencing alerts  
- AI-based rider behavior analysis  
