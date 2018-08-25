#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN  10    // D4 2
#define RST_PIN 9   // D1 16

MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;

byte i;
byte newUid[] = {0xDE, 0xAD, 0xBE, 0xEF};

void setup() {
  Serial.begin(115200);
  SPI.begin();
  rfid.PCD_Init();

  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent()) {
    return;
  }
  if (!rfid.PICC_ReadCardSerial()) {
    return;
  }
  Serial.print(F("Card UID:"));
  for ( i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(rfid.uid.uidByte[i], DEC);
  }
  Serial.println();
}
