WiFiClientSecure secureClient;
PubSubClient mqttClient(secureClient);

void syncTime() {
  Serial.print("Syncing time via NTP");
  configTime(0, 0, "pool.ntp.org", "time.nist.gov");
  time_t now = time(nullptr);
  while (now < 1609459200) {
    delay(500);
    Serial.print(".");
    now = time(nullptr);
  }
  Serial.println("\nTime synchronized!");
}

void connectAWS() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected.");

  syncTime();

  secureClient.setCACert(amazonRootCA);
  secureClient.setCertificate(deviceCert);
  secureClient.setPrivateKey(deviceKey);

  mqttClient.setServer(aws_endpoint, aws_port);
  Serial.print("Connecting to AWS IoT Core");
  
  while (!mqttClient.connected()) {
    Serial.print(".");
    if (mqttClient.connect(device_id)) {
      Serial.println("\nConnected to AWS IoT Core!");
    } else {
      Serial.print("\nFailed! Error code: ");
      Serial.println(mqttClient.state());
      delay(5000);
    }
  }
}

// Keeps the connection alive
void checkAWSConnection() {
  if (!mqttClient.connected()) {
    connectAWS();
  }
  mqttClient.loop();
}

// Packages the data and fires it to the cloud
void processAttendance(String scannedUid) {
  int studentIndex = -1;
  
  for (int i = 0; i < totalStudents; i++) {
    if (studentDatabase[i].uid == scannedUid) {
      studentIndex = i;
      break;
    }
  }

  if (studentIndex == -1) {
    Serial.println("Unregistered card scanned! Access Denied.");
    return; 
  }

  StaticJsonDocument<256> doc; 
  doc["student_id"] = studentDatabase[studentIndex].uid;
  doc["name"]       = studentDatabase[studentIndex].name;
  doc["course"]     = studentDatabase[studentIndex].course;
  doc["semester"]   = studentDatabase[studentIndex].semester;
  doc["location"]   = "GGSIPU_Lab_1";
  doc["timestamp"]  = time(nullptr); 
  
  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer);
  
  if (mqttClient.publish(mqtt_topic, jsonBuffer)) {
    Serial.print("Successfully published to AWS: ");
    Serial.println(jsonBuffer);
  } else {
    Serial.println("Failed to publish message to AWS.");
  }
}
