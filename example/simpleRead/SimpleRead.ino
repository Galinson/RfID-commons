#include <RFIDReader.h>        // Include your custom library header file

// Create an instance of RFIDReader using SDA pin 10 and RST pin 9
// (You can change these if wired differently)
RFIDReader rfid(10, 9);

void setup() {
  Serial.begin(9600);          // Start serial communication at 9600 baud for output
  rfid.begin();                // Initialize the RFID hardware (starts SPI + MFRC522 setup)
  Serial.println("Place your RFID card near the reader...");  // User instruction
}

void loop() {
  if (rfid.isCardPresent()) {  // Check if an RFID tag is detected
    String uid = rfid.readUID();  // Read its unique ID
    Serial.print("Card UID: ");   // Print label
    Serial.println(uid);          // Print the UID in hexadecimal format
    delay(1000);                  // Wait 1 second before scanning again (avoids spam)
  }
}
