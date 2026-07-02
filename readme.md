ABOUT PORTS 

1. Port 1883: The Unencrypted Door (The Postcard)
Port 1883 is the default, standard port for MQTT traffic. If you were building a local smart home project on a Raspberry Pi, you might use this.
The Problem: Traffic sent over Port 1883 is completely unencrypted. It is like sending a postcard through the mail.
The Risk: If your ESP32 used Port 1883 on a public college WiFi network, anyone with a network sniffer could read your JSON data in plain text. They would see exact student names, UIDs, and timestamps floating through the air.
2. Port 8883: The Secure Door (The Armored Truck)
Port 8883 is the designated port for MQTTS (MQTT over TLS). The "S" stands for Secure. This port applies the exact same heavy-duty encryption (TLS) that your web browser uses when you log into your bank's website via HTTPS.
The Solution: When data goes through Port 8883, it is scrambled into unreadable cryptographic gibberish.
The Protection: Even if someone intercepts your ESP32's WiFi signal, they cannot read the student data. They will just see a meaningless stream of locked data.
3. What Actually Happens on Port 8883 (The mTLS Handshake)
AWS IoT Core operates on a "Zero Trust" model, meaning it assumes everything trying to connect is a threat. It refuses to even open Port 1883. It only accepts connections on 8883, and it demands Mutual TLS (mTLS).
When your ESP32 knocks on AWS's Port 8883, a strict, split-second security check occurs before any data is allowed through:
The Server Proves Its Identity: AWS sends its ID card down to the ESP32. Your ESP32 checks this against the amazonRootCA you pasted into your code. This ensures a hacker hasn't hijacked your DNS to route your data to a fake server.
The Device Proves Its Identity: AWS then demands your device's ID. Your ESP32 sends up the deviceCert.
The Cryptographic Test: Anyone could copy a public certificate. So, AWS sends a complex math puzzle to the ESP32. The ESP32 can only solve this puzzle if it possesses the hidden deviceKey (the Private Key).
The Tunnel Opens: Once the ESP32 solves the puzzle, AWS is satisfied. A secure, encrypted tunnel is opened on Port 8883, and your JSON payload is allowed to flow into the cloud.
When architecting secure cloud infrastructure, locking down edge devices with mTLS over Port 8883 is the industry standard. It ensures that only your specific, physical hardware can write data to your backend.


JSON PAYLOAD IN AWS WILL LOOK LIKE THIS ON SCANNING:-

{
  "student_id": "A1B2XXXXX",
  "course": "BCA",
  "semester": 6,
  "location": "----",
  "timestamp": 1741808653
}
