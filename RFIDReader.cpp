#include "RfID.h"   //Name

// Constructor: we use initializer list to initialize the rfid object with the ss and rst pins
RFIDReader::RFIDReader(byte ss, byte rst) : rfid(ss, rst) {
  ssPin = ss;
  rstPin = rst;
}

// begin(): must call this in setup()
void RFIDReader::begin() {
  SPI.begin();           // Start the SPI bus (hardware). This configures SPI pins, clocks, etc.
  rfid.PCD_Init();       // Initialize the MFRC522 hardware (reset, configure registers, etc.)
  delay(50);             // Short delay to let the chip settle / stabilize
  // The delay is a blocking wait; 50 ms is small but could be an issue if you have time-sensitive tasks.
}

// Returns true if a new card is present and has been read into internal buffer
bool RFIDReader::isCardPresent() {
  // PICC_IsNewCardPresent() checks if there’s a new card in range
  // PICC_ReadCardSerial() attempts to read the UID into internal state (returns true if successful)
  return rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial();
}

// Reads the UID from the internal state of the rfid object and returns a hex string
String RFIDReader::readUID() {
  String uidStr = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    // For each byte in UID, convert it to hex. If < 0x10, prepend a '0' for two-digit formatting.
    if (rfid.uid.uidByte[i] < 0x10) {
      uidStr += "0";
    }
    uidStr += String(rfid.uid.uidByte[i], HEX);
  }
  uidStr.toUpperCase();    // Convert letters to upper-case (A–F)
  rfid.PICC_HaltA();       // Command the chip to halt further readings (good manners)
  return uidStr;
}
