# IoT-Based Smart Water Tank Level Monitoring and Pump Automation System

An automated IoT water management system built using **ESP8266 NodeMCU**, **Arduino UNO**, and an **HC-SR04 Ultrasonic Sensor**. The system monitors real-time water levels, communicates via Machine-to-Machine (M2M) communication, automatically controls a water pump to prevent overflow or dry runs, and sends live alerts via the **Blynk IoT Dashboard**.

## Key Features
* **Real-Time Level Measurement:** Uses an HC-SR04 ultrasonic sensor to calculate water depth accurately without physical contact.
* **M2M Communication:** ESP8266 NodeMCU collects water-level telemetry and communicates status updates with an Arduino UNO controller.
* **Automated Pump Control:** Arduino UNO automatically switches the water pump **ON** when the water level drops below the minimum threshold and **OFF** once the tank reaches maximum capacity.
* **Cloud Monitoring & Alerts:** Integrated with the **Blynk IoT Dashboard** for live water-level visualization and instant high/low water alerts.

## Hardware & Software Components
* **Microcontrollers:** ESP8266 NodeMCU, Arduino UNO
* **Sensor:** HC-SR04 Ultrasonic Distance Sensor
* **Actuator:** 5V Single-Channel Relay Module & Water Pump
* **Software & Platforms:** Arduino IDE, Embedded C/C++, Blynk IoT Platform

## How It Works
1. The **HC-SR04 ultrasonic sensor** mounted at the top of the tank measures the distance to the water surface.
2. The **ESP8266 NodeMCU** processes the sensor readings into a water-level percentage and uploads the data to the **Blynk IoT Dashboard**.
3. Through **M2M communication**, the water-level state is shared with the **Arduino UNO**.
4. When the tank reaches a low threshold, the Arduino triggers the **relay module** to turn the pump **ON**.
5. Once the tank reaches full capacity, the Arduino cuts power to the relay to turn the pump **OFF**, preventing water wastage and overflow.

## Repository Structure
* `NodeMCU_Blynk_Monitor.ino` – Code for ultrasonic sensing and Blynk cloud integration *(upload your file here)*
* `Arduino_Pump_Control.ino` – Code for M2M reception and relay pump automation *(upload your file here)*
* `circuit_diagram.png` – Hardware wiring schematic *(optional)*

## Author
**Trusha Tanna**  
B.E. in Electronics and Communication Engineering | Government Engineering College, Bhavnagar  
* **Portfolio:** [View Live Portfolio](https://github.io)
* **Email:** trushatanna0208@gmail.com
