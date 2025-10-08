#include "RFIDReader.h"

// Constructor: create an RFID object and remember the pin numbers
RFIDReader::RFIDReader(byte ss, byte rst) : rfid(ss, rst) {
  ssPin = ss;
  rstPin = rst;
}

// Initialize SPI and the RFID reader
void RFIDReader::begin() {
  SPI.begin();          // Start SPI bus
  rfid.PCD_Init();      // Initialize RFID reader
  delay(50);            // Small delay for stability
}

// Check if a new RFID card is present
bool RFIDReader::isCardPresent() {
  return rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial();
}

// Read and return UID as a human-readable string
String RFIDReader::readUID() {
  String uidStr = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    // Convert each byte of UID to two-digit hex
    uidStr += String(rfid.uid.uidByte[i] < 0x10 ? "0" : "");
    uidStr += String(rfid.uid.uidByte[i], HEX);
  }
  uidStr.toUpperCase(); // Make it pretty
  rfid.PICC_HaltA();    // Stop reading this card
  return uidStr;
}
