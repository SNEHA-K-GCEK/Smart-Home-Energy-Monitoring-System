# Phase 11 Hardware Circuit Connections

This document tracks the electrical pin distribution mapping used to connect the physical measurement and feedback peripherals to the core ESP32 microchip node.

## ESP32 Interconnect Architecture Matrix

| Peripheral Component | Pinout Line | ESP32 Target Node Pin |
| :--- | :--- | :--- |
| *ACS712 Current Sensor* | VCC | 5V |
| | GND | GND |
| | OUT | GPIO34 (Analog ADC1_CH6) |
| *Warning Status LED* | Anode (+) | GPIO26 (Digital Output) |
| | Cathode (-) | GND (Via 220Ω Resistor) |
| *Audio Buzzer Alarm* | Positive (+) | GPIO27 (Digital Output) |
| | Negative (-) | GND |
| *I2C OLED Display* | VCC | 3.3V |
| | GND | GND |
| | SDA | GPIO21 (I2C Data) |
| | SCL | GPIO22 (I2C Clock) |