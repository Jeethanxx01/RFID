
# RFID

RFID Attendance System is designed to create a paperless, efficient, and eco-friendly method for tracking attendance and monitoring various other activities. Leveraging RFID technology and a smart card pre-coded with user information, this system aims to reduce time consumption and enhance efficiency. Key components of the system include RFID modules, LCD displays, LEDs, and buzzers. Data acquisition and visualization are facilitated using PLX-DAQ in Microsoft Excel.
## Key Features

- Eco-Friendly: Eliminates the need for paper, contributing to a greener environment.
- Efficient: Reduces time consumption and enhances operational efficiency.
- RFID Technology: Utilizes RFID modules and pre-coded smart cards for accurate attendance recording.
- Data Visualization: Employs PLX-DAQ for real-time data monitoring and visualization in Microsoft Excel.
- Versatile Applications: Suitable for attendance tracking, entry and exit monitoring, membership tracking, vehicle tracking, inventory management, and more.
## Components

- Arduino Uno: The main microcontroller to control and coordinate all components.
- RFID Modules: For scanning RFID cards and recording data.
- Smart Cards: Pre-coded with user information for identification.
- LCD Display: To display attendance and other relevant information.
- LEDs: To provide visual indicators for system status.
- Buzzers: For auditory alerts and notifications.
- PLX-DAQ: Tool used for data acquisition and visualization in Microsoft Excel.
- Breadboard: For creating and testing circuit connections.
- Potentiometer: For adjusting the contrast of the LCD display.
- Jumper Wires: For making electrical connections between components on the breadboard and Arduino.


## Connections

1. LCD Connections:

- RS (LCD Pin 4) to Arduino Pin 3
- E (LCD Pin 6) to Arduino Pin 2
- DB4 (LCD Pin 11) to Arduino A0 (Pin 14)
- DB5 (LCD Pin 12) to Arduino A1 (Pin 15)
- DB6 (LCD Pin 13) to Arduino A2 (Pin 16)
- DB7 (LCD Pin 14) to Arduino A3 (Pin 17)
- VSS (LCD Pin 1) to GND
- VDD (LCD Pin 2) to 5V
- V0 (LCD Pin 3) to a potentiometer (for contrast control)
- RW (LCD Pin 5) to GND
- A (LCD Pin 15) to 5V (Backlight Anode)
- K (LCD Pin 16) to GND (Backlight Cathode)

2. RFID Connections:

- VCC to 3.3V (some modules use 5V, check your module specs)
- GND to GND
- RST to Pin 9
- SDA to Pin 10
- SCK to Pin 13
- MOSI to Pin 11
- MISO to Pin 12

3. LED and Buzzer Connections:

- Red LED: Connect anode (longer leg) to Pin 5 (with a current-limiting resistor in series) and cathode (shorter leg) to GND
- Green LED: Connect anode to Pin 6 (with a current-limiting resistor in series) and cathode to GND
- Yellow LED: Connect anode to Pin 7 (with a current-limiting resistor in series) and cathode to GND
- Buzzer: Connect positive lead to Pin 4 and negative lead to GND


4. Power Supply
LCD, RFID Reader, LEDs, and Buzzer: Ensure you provide the necessary power (typically 5V and GND) to each component. This usually involves connecting the VCC pins to the 5V pin on the Arduino and GND pins to the GND pin on the Arduino.


## Screenshots

![connections](https://github.com/Jeethanxx01/RFID/blob/main/images/connections.png)

![plx](https://github.com/Jeethanxx01/RFID/blob/main/images/plx.png)


## How It Works

- Card Scanning: Users present their pre-coded smart card to the RFID module.
- Data Recording: The system scans the card, retrieves the encoded information, and records the attendance.
- Display: Attendance data and other relevant information are displayed on the LCD screen.
- Data Acquisition: PLX-DAQ captures the data and visualizes it in Microsoft Excel for real-time monitoring and analysis.
## Applications

- Attendance Tracking: Efficiently records and monitors attendance.
- Entry and Exit Monitoring: Tracks entry and exit of individuals.
- Membership Tracking: Manages membership details and status.
- Vehicle Tracking: Monitors vehicle movements and access.
- Inventory Management: Keeps track of inventory levels and status.
- Customer Service Enhancement: Improves visibility and distribution in various industries.