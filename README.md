# IOT_PROJECT_RFID

IoT-based RFID Attendance System project using Arduino and AWS IoT Core.

## Overview
This project automates attendance tracking using RFID cards and IoT integration. It was developed as a collaborative effort by our team of four.

## Features
- Automated attendance logging with RFID cards  
- Real-time data storage using AWS IoT Core  
- Simple and scalable design for schools or offices  
- Easy to extend with cloud dashboards  

## Setup Instructions
1. Connect Arduino with the RFID sensor.  
2. Configure AWS IoT Core for data storage.  
3. Upload the Arduino sketch provided in this repository.  
4. Test with RFID cards to log attendance.  

## Security and Ports in AWS IoT

### Port 1883: The Unencrypted Door (Postcard Analogy)
- Default port for MQTT traffic.  
- Traffic is unencrypted, like sending a postcard.  
- **Risk:** On public WiFi, anyone with a sniffer can read JSON data (student names, UIDs, timestamps).  

### Port 8883: The Secure Door (Armored Truck Analogy)
- Port for MQTTS (MQTT over TLS).  
- Uses TLS encryption, same as HTTPS banking sites.  
- **Protection:** Even if intercepted, data is unreadable cryptographic gibberish.  

### What Actually Happens on Port 8883 (mTLS Handshake)
AWS IoT Core enforces **Mutual TLS (mTLS)** for secure connections:
1. **Server proves identity** → ESP32 checks AWS certificate against `amazonRootCA`.  
2. **Device proves identity** → ESP32 sends its `deviceCert`.  
3. **Cryptographic test** → AWS challenges ESP32; only the private `deviceKey` can solve it.  
4. **Secure tunnel opens** → Encrypted JSON payload flows safely to the cloud.  

This ensures only your physical ESP32 device can write data to the backend — industry standard for IoT security.

### Example JSON Payload
```json
{
  "student_id": "A1B2XXXXX",
  "course": "BCA",
  "semester": 6,
  "location": "----",
  "timestamp": 1741808653
}

## Team Members and Roles
- **Kapil Rawat** – AWS services integration, ESP32 programming (partial), wiring and contributor to the group report  
- **Saksham Tyagi** – Circuit design, wiring, testing of RFID module and contributor to the group report  
- **Devesh Pant** – Arduino programming, debugging, code optimization and contributor to the group report  
- **Sujal Kumar** – Cloud configuration, data logging, report preparation and contributor to the group report  
