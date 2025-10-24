Arduino Code
#include <SPI.h>
#include <MFRC522.h>
#include <DFRobotDFPlayerMini.h>

// RFID pins
#define RST_PIN 22
#define SS_PIN 21

// DFPlayer 1 pins (Speaker 1)
#define DF1_RX 16   // ESP32 RX → DFPlayer1 TX
#define DF1_TX 17   // ESP32 TX → DFPlayer1 RX

// DFPlayer 2 pins (Speaker 2)
#define DF2_RX 26   // ESP32 RX → DFPlayer2 TX
#define DF2_TX 27   // ESP32 TX → DFPlayer2 RX

MFRC522 mfrc522(SS_PIN, RST_PIN);
DFRobotDFPlayerMini df1;  // Speaker 1
DFRobotDFPlayerMini df2;  // Speaker 2

// Timing for announcements
unsigned long previousMillis = 0;
const unsigned long interval = 15000; // 15s

// ---------- Setup ----------
void setup() {
  Serial.begin(115200);

  // Fix SPI init for ESP32
  SPI.begin(18, 19, 23, SS_PIN);
  mfrc522.PCD_Init();
  Serial.println("RFID + Dual DFPlayer Test Started...");

  // DFPlayer 1 (Speaker 1)
  Serial2.begin(9600, SERIAL_8N1, DF1_RX, DF1_TX);
  if (!df1.begin(Serial2)) {
    Serial.println("DFPlayer 1 not found!");
    while (true);
  }
  df1.volume(25);
  Serial.println("DFPlayer 1 ready!");

  // DFPlayer 2 (Speaker 2)
  Serial1.begin(9600, SERIAL_8N1, DF2_RX, DF2_TX);
  if (!df2.begin(Serial1)) {
    Serial.println("DFPlayer 2 not found!");
    while (true);
  }
  df2.volume(25);
  Serial.println("DFPlayer 2 ready!");
}

// ---------- Loop ----------
void loop() {
  unsigned long currentMillis = millis();

  // ---------- 1. Periodic Announcements ----------
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    Serial.println("Playing announcements...");
    df1.play(2);  // Speaker 1 → 0002.mp3 "JSS1 has Maths"
    df2.play(3);  // Speaker 2 → 0003.mp3 "SS3 has Chemistry"
  }

  // ---------- 2. RFID Scanning ----------
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    String uidString = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      uidString += String(mfrc522.uid.uidByte[i], HEX);
    }
    uidString.toUpperCase();
    Serial.print("Card Scanned: MR KHALIFA DANKADAI(CVO) ");
    Serial.println(uidString);

    // Example: replace with your actual UID
    if (uidString == "MR KHALIFA DANKADAI(CVO)") {
      Serial.println("Attendance recorded: David Apiribo");
      df1.play(1);  // Greeting → 0001.mp3 on Speaker 1
    }

    mfrc522.PICC_HaltA();
  }
}
