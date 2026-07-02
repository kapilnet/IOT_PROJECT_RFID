#define SS_PIN 5
#define RST_PIN 22
MFRC522 mfrc522(SS_PIN, RST_PIN);

// Wakes up the RFID reader
void initRFID() {
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("RFID Reader Initialized.");
}

// Scans for a card and returns the extracted UID as a String
String getScannedUID() {
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    return ""; // Return empty if no card is tapped
  }
  
  String cardUID = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if (mfrc522.uid.uidByte[i] < 0x10) cardUID += "0";
    cardUID += String(mfrc522.uid.uidByte[i], HEX);
  }
  
  cardUID.toUpperCase();
  mfrc522.PICC_HaltA(); // Stop reading the same card repeatedly
  
  return cardUID;
}
