# 🎫 RFID Attendance System

[![Arduino](https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=Arduino&logoColor=white)](https://www.arduino.cc/)
[![RFID](https://img.shields.io/badge/RFID-000000?style=for-the-badge&logo=RFID&logoColor=white)](https://en.wikipedia.org/wiki/Radio-frequency_identification)
[![Excel](https://img.shields.io/badge/Microsoft_Excel-217346?style=for-the-badge&logo=microsoft-excel&logoColor=white)](https://www.microsoft.com/en-us/microsoft-365/excel)

<div align="center">
  <img src="https://github.com/Jeethanxx01/RFID/blob/main/images/connections.png" alt="System Connections" width="600"/>
</div>

## 📋 Table of Contents
- [Overview](#overview)
- [Key Features](#key-features)
- [Components](#components)
- [Hardware Setup](#hardware-setup)
- [How It Works](#how-it-works)
- [Applications](#applications)
- [Screenshots](#screenshots)

## 📝 Overview

The RFID Attendance System is a modern, paperless solution designed for efficient attendance tracking and activity monitoring. By leveraging RFID technology and pre-coded smart cards, this system significantly reduces time consumption while enhancing operational efficiency. The system integrates RFID modules, LCD displays, LEDs, and buzzers, with data visualization capabilities through PLX-DAQ in Microsoft Excel.

## ✨ Key Features

- 🌱 **Eco-Friendly**: Eliminates paper usage, contributing to environmental sustainability
- ⚡ **Efficient**: Reduces time consumption and enhances operational efficiency
- 🎯 **RFID Technology**: Utilizes advanced RFID modules and pre-coded smart cards
- 📊 **Data Visualization**: Real-time monitoring and visualization through PLX-DAQ
- 🔄 **Versatile Applications**: Supports multiple use cases from attendance to inventory management

## 🔧 Components

| Component | Description |
|-----------|-------------|
| Arduino Uno | Main microcontroller for system control |
| RFID Modules | Card scanning and data recording |
| Smart Cards | Pre-coded user identification |
| LCD Display | Information display interface |
| LEDs | Visual status indicators |
| Buzzers | Auditory alerts |
| PLX-DAQ | Data acquisition and Excel integration |
| Breadboard | Circuit connection platform |
| Potentiometer | LCD contrast control |
| Jumper Wires | Component interconnection |

## 🔌 Hardware Setup

### 1. LCD Connections
| LCD Pin | Arduino Pin |
|---------|-------------|
| RS (Pin 4) | Pin 3 |
| E (Pin 6) | Pin 2 |
| DB4 (Pin 11) | A0 (Pin 14) |
| DB5 (Pin 12) | A1 (Pin 15) |
| DB6 (Pin 13) | A2 (Pin 16) |
| DB7 (Pin 14) | A3 (Pin 17) |
| VSS (Pin 1) | GND |
| VDD (Pin 2) | 5V |
| V0 (Pin 3) | Potentiometer |
| RW (Pin 5) | GND |
| A (Pin 15) | 5V |
| K (Pin 16) | GND |

### 2. RFID Connections
| RFID Pin | Arduino Pin |
|----------|-------------|
| VCC | 3.3V/5V |
| GND | GND |
| RST | Pin 9 |
| SDA | Pin 10 |
| SCK | Pin 13 |
| MOSI | Pin 11 |
| MISO | Pin 12 |

### 3. LED and Buzzer Setup
- **Red LED**: Anode → Pin 5 (with resistor) | Cathode → GND
- **Green LED**: Anode → Pin 6 (with resistor) | Cathode → GND
- **Yellow LED**: Anode → Pin 7 (with resistor) | Cathode → GND
- **Buzzer**: Positive → Pin 4 | Negative → GND

## 🔄 How It Works

1. **Card Scanning**: Users present their smart card to the RFID module
2. **Data Recording**: System scans and processes card information
3. **Display**: Information shown on LCD screen
4. **Data Acquisition**: PLX-DAQ captures and visualizes data in Excel

## 🎯 Applications

- 📊 **Attendance Tracking**: Automated attendance recording
- 🚪 **Entry/Exit Monitoring**: Track individual movements
- 👥 **Membership Management**: Handle membership details
- 🚗 **Vehicle Tracking**: Monitor vehicle access
- 📦 **Inventory Management**: Track inventory status
- 🏢 **Customer Service**: Enhance service visibility

## 📸 Screenshots

<div align="center">
  <img src="https://github.com/Jeethanxx01/RFID/blob/main/images/connections.png" alt="System Connections" width="600"/>
  <img src="https://github.com/Jeethanxx01/RFID/blob/main/images/plx.png" alt="PLX-DAQ Interface" width="600"/>
</div>

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.