# Clock and Temperature Project

## Overview

This project uses a DS3231 Real-Time Clock (RTC) module to measure and display the current time on a 1306 OLED display. Additionally, it measures the temperature using an analog temperature sensor and maps the temperature value to control a 9g servo motor. If the measured temperature exceeds a defined threshold, an alarm is triggered, activating a series of connected LEDs.

## Features

- **Real-Time Clock**: Uses the DS3231 RTC to keep track of time.
- **Temperature Measurement**: Reads temperature data from an analog sensor.
- **OLED Display**: Displays current time and temperature readings.
- **Threshold Alarm**: Activates LEDs if the temperature exceeds a specified threshold.
- **User Adjustable Threshold**: The temperature threshold can be adjusted using a potentiometer.

## Hardware Requirements

- Arduino (any compatible board)
- DS3231 RTC module
- 1306 OLED display
- Analog temperature sensor
- 9g servo motor
- Potentiometer
- LEDs (for alarm indication)
- Jumper wires and breadboard

## Libraries Used

- `RTClib` for handling the RTC module.
- `Wire` for I2C communication.
- `U8glib` for controlling the OLED display.

## Installation

1. Clone this repository to your local machine:

   ```bash
   git clone https://github.com/yourusername/clock-and-temp-project.git
