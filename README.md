# Dual Driver Drowsiness Detection and Alert System

Driver fatigue is one of the leading causes of road accidents worldwide. Long driving hours, lack of sleep, and monotonous road conditions can significantly reduce a driver's alertness, increasing the risk of collisions. Traditional safety systems often react only after an accident has begun, whereas an intelligent driver monitoring system can help prevent accidents before they occur.

This project presents a **Dual Driver Drowsiness Detection and Alert System** built using a **Raspberry Pi 5**, **OpenCV**, **Computer Vision**, and **Smart Wearable Glasses** equipped with **Infrared (IR) Eye Sensors**. 

---

# Objectives

- Detect driver drowsiness in real time.
- Prevent accidents caused by driver fatigue.
- Implement two independent detection methods.
- Integrate Computer Vision and Wearable Sensor technologies.
- Establish Wi-Fi communication between wearable devices and Raspberry Pi.
- Generate instant audio and visual alerts.
- Log driver activity for future analysis.
- Build a scalable platform for future AI-assisted transportation systems.

---

# 🏗 System Architecture

```
                          Driver

                ┌─────────┴─────────┐
                │                   │

        Camera Monitoring      Smart Glasses

                │                   │

       OpenCV + MediaPipe      IR Eye Sensor

                │                   │

         Raspberry Pi 5 (Main Controller)

                │

        Decision Making Algorithm

                │

      ┌─────────┼─────────┐

   Buzzer      LED     Notifications

                │

          Data Logging

                │

     Cloud Dashboard (Future)
```

---

# Hardware Components

## Main Processing Unit

- Raspberry Pi 5 (8 GB Recommended)
- 32 GB MicroSD Card
- Raspberry Pi Power Supply

---

## Vision-Based Detection

- Raspberry Pi Camera Module v3 or USB Webcam

Functions:
- Face Detection
- Eye Detection
- Facial Landmark Detection
- Blink Monitoring
- Eye Aspect Ratio (EAR) Calculation
- Yawning Detection
- Head Pose Estimation

---

## Wearable Detection

- Smart Glasses Frame
- IR LED
- IR Receiver 
- ESP32 Wi-Fi Module
- Rechargeable Battery
- Voltage Regulator
- Power Switch

Functions:
- Eye Blink Detection
- Eye Closure Detection
- Blink Duration Measurement
- Wireless Data Transmission

---

## Alert System
- Piezo Buzzer
- High Brightness LED
- Speaker (Optional)
  
---

## Communication

- ESP32 Wi-Fi
- Raspberry Pi Wi-Fi
- Router or Mobile Hotspot

Supported Protocols

- MQTT
- HTTP REST API
- WebSocket

---

# 💻 Software Requirements

## Operating System

- Raspberry Pi OS

## Programming Language

- Python 3

## Libraries

- OpenCV
- MediaPipe
- NumPy
- SciPy
- Flask
- MQTT (Paho MQTT)

## Development Tools

- VS Code
- Thonny IDE
- Git
- GitHub

---

# 👁 Method 1 – Camera-Based Detection (OpenCV)

The camera continuously monitors the driver's face and extracts facial landmarks using MediaPipe or OpenCV. The Eye Aspect Ratio (EAR) is calculated from the detected eye landmarks to determine whether the driver's eyes are open or closed.

### Workflow

```
Camera

↓

Capture Video

↓

Face Detection

↓

Facial Landmark Detection

↓

Eye Detection

↓

Calculate Eye Aspect Ratio (EAR)

↓

EAR > Threshold ?

├── Yes → Continue Monitoring

└── No

      ↓

Start Eye Closure Timer

      ↓

Eyes Closed > 2 Seconds ?

├── No → Continue Monitoring

└── Yes

      ↓

Driver Drowsy

      ↓

Activate Alarm

      ↓

Store Event Log

      ↓

Send Notification
```

### Parameters Monitored

- Eye Aspect Ratio (EAR)
- Blink Rate
- Eye Closure Duration
- Face Orientation
- Yawning Detection (Optional)
- Head Tilt (Optional)

---

# 👓 Method 2 – Smart Wearable Glasses

The wearable glasses use infrared sensors to monitor eye movements without requiring a camera. An IR LED emits infrared light toward the eye, while the IR receiver measures the reflected light intensity. The reflection changes depending on whether the eye is open or closed.

The ESP32 processes these readings and transmits the blink information wirelessly to the Raspberry Pi over Wi-Fi.

### Workflow

```
IR LED

↓

Infrared Reflection

↓

IR Receiver

↓

ESP32

↓

Calculate Blink Duration

↓

Wi-Fi Transmission

↓

Raspberry Pi

↓

Analyze Eye Status

↓

Drowsiness Detected?

├── No → Continue Monitoring

└── Yes

      ↓

Activate Alarm

      ↓

Store Event Log
```

### Parameters Monitored

- Blink Duration
- Eye Closure Time
- Blink Frequency
- Sensor Signal Strength

---

# Decision Making Algorithm

The Raspberry Pi acts as the central decision-making unit.

Both detection systems operate independently and can also work together for improved reliability.

### Camera Data

- Face Detected
- Eyes Open
- Eyes Closed
- Blink Rate
- Head Position
- Yawning

### Smart Glasses Data

- Blink Duration
- Eye Closure Time
- Blink Frequency
- IR Signal Level

### Decision Logic

```
IF

Eye Closure > 2 Seconds

AND

Blink Frequency Below Threshold

↓

High Risk

↓

Activate Alarm

↓

Store Event

↓

Send Notification
```

### Fail-Safe Logic

```
Camera Failure

↓

Automatically Switch

↓

Wearable Detection Only
```

```
Wearable Failure

↓

Automatically Switch

↓

Camera Detection Only
```

This redundancy ensures continuous monitoring even if one subsystem fails.

---

# 📡 Wi-Fi Communication

The ESP32 communicates wirelessly with the Raspberry Pi using Wi-Fi.

Possible communication methods include:

### MQTT

```
ESP32

↓

Publish Sensor Data

↓

MQTT Broker

↓

Raspberry Pi Subscriber

↓

Process Data
```

Advantages

- Lightweight
- Fast
- Reliable
- Suitable for IoT Applications

---

### HTTP REST API

```
ESP32

↓

HTTP POST

↓

Flask Server

↓

Raspberry Pi
```

Suitable for smaller projects and simple communication.

---

# Alert System

The system generates alerts based on the severity of driver fatigue.

### Level 1

- Yellow LED
- Soft Warning Tone

### Level 2

- Flashing LED
- Loud Buzzer

### Level 3

- Voice Alert

Example:

```
Warning!

Driver fatigue detected.

Please stop the vehicle and take a break.
```

Future enhancements include:

- SMS Alerts
- GPS Location Sharing
- Emergency Contact Notification
