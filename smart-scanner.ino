struct Student {
  String uid;
  String name;
  String course;
  int semester;
};

const int totalStudents = 4;
Student studentDatabase[totalStudents] = {
  {"A1B2C3D4", "Saksham Tyagi", "BCA", 6}, 
  {"F9E8D7C6", "Kapil Singh Rawat", "BCA", 6},
  {"9876QWER", "Sujal Kumar", "BTech", 4},
  {"XYZ12345", "Devesh Pant", "BTech", 4}
};

void publishAttendance(String scannedUid) {
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
    Serial.print("Data successfully AWS par bhej diya gaya: ");
    Serial.println(jsonBuffer);
  } else {
    Serial.println("AWS par message publish hone mein fail ho gaya.");
  }
}
