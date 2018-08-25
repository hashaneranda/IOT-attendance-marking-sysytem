
/*
   RFID Attendence Managment System



        RFID Wire Connections
   |-----------|----------|--------|
   | RFID Pins | Node MCU | Arduino|
   |-----------|----------|--------|
   | RST       |   D1     |   16   |
   | SDA(SS)   |   D4     |    2   |
   | SCK       |   D5     |   14   |
   | MISO(SCL) |   D6     |   12   |
   | MOSI      |   D7     |   13   |
   |-------------------------------|

*/

#include <SPI.h>
#include <Wire.h>
#include <MFRC522.h>
#include <ESP8266WiFi.h>


#define SS_PIN  2    // D4
#define RST_PIN 16   // D1
#define No_Of_Card 4 // number of RFID cards
#define UID_Size 4   // UID lenght

#define Buzzer 15    // D8
#define BlueLed 0    // D2
#define GreenLed 4   // D3

const char* ssid     = "One country One Kbps.";      // SSID
const char* password = "Tangojuliet1996";    // Password

char host[] = "192.168.8.100"; // host my computer wifi adpter

const int httpPort = 80; // WiFiClient client;

MFRC522 RFID(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;
WiFiClient client;

byte id[No_Of_Card][UID_Size] = {
  {17, 01, 215, 43},
  {117, 170, 82, 171},
  {124, 013, 171, 137},
  {124, 13, 171, 137}
};

int x = 0;
int count[2] = {0, 0};

byte id_temp[3][3];

//String ID[3] = {"170121543", "124013171137", "11717082171"};
String ID = "170121543";


void setup() {
  Serial.begin(115200);
  SPI.begin();
  RFID.PCD_Init();

  pinMode(Buzzer, OUTPUT);
  pinMode(BlueLed, OUTPUT);
  pinMode(GreenLed, OUTPUT);

  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }

  //----------------------------------

  WiFi.begin(ssid, password);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  if (WiFi.status() == WL_CONNECTED) {
    digitalWrite(Buzzer, HIGH);
    digitalWrite(BlueLed, HIGH);
    delay(300);
    digitalWrite(Buzzer, LOW);
    //digitalWrite(BlueLed, LOW);
  }

  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (!RFID.PICC_IsNewCardPresent()) {
    return;
  }
  if (!RFID.PICC_ReadCardSerial()) {
    return;
  }

  for (int i = 0; i < 4; i++) {
    id_temp[0][i] = RFID.uid.uidByte[i];
    delay(50);
  }

  for (byte i = 0; i < No_Of_Card; i++) {
    if (id[i][0] == id_temp[0][0]) {
      Serial.print("Card UID :");
      digitalWrite(Buzzer, HIGH);
      for (int j = 0; j < RFID.uid.size; j++) {
        Serial.print(RFID.uid.uidByte[j], DEC);
      }
      x = i;
      Serial.println(" UID is Valid");
      digitalWrite(Buzzer, HIGH);
      digitalWrite(GreenLed, HIGH);
      digitalWrite(BlueLed, LOW);
      delay(150);
      digitalWrite(Buzzer, LOW);
      digitalWrite(GreenLed, LOW);
      digitalWrite(BlueLed, HIGH);
      sendRequest(x);

      RFID.PICC_HaltA();
      RFID.PCD_StopCrypto1();
      return;

    }
    else {
      Serial.println("UID is Invalid");
      //Serial.println("UID is Invalid");
      digitalWrite(Buzzer, HIGH);
      digitalWrite(GreenLed, HIGH);
      delay(350);
      digitalWrite(Buzzer, LOW);
      digitalWrite(GreenLed, LOW);
    }
  }

  RFID.PICC_HaltA();
  RFID.PCD_StopCrypto1();
}

void sendRequest(int n) {
  if (!client.connect(host, httpPort)) {
    Serial.println("Connection failed");
    return;
  }



  /*-----------------------*/
  // We now create a URI for the request
  String url = "/RFID/get.php?emp_id=";
  //url += ID[n];
  url += ID;
  url += "&allow=1";

  Serial.print("Requesting URL: ");
  Serial.println(url);

  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");

  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
}


