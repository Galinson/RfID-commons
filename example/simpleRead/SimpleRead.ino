#include <RFIDReader.h>

// Pins: SDA = 10, RST = 9 (change as needed)
RFIDReader rfid(10, 9);

void setup() {
  Serial.begin(9600);
  rfid.begin();
  Serial.println("Place your RFID card near the reader...");
}

void loop() {
  if (rfid.isCardPresent()) {
    String uid = rfid.readUID();
    Serial.print("Card UID: ");
    Serial.println(uid);
    delay(1000);
  }
}
