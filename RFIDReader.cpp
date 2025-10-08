#include "RFIDReader.h"     // Include the header file that defines the RFIDReader class

// Constructor definition
// The colon syntax ( : rfid(ss, rst) ) calls the MFRC522 constructor before entering the body
RFIDReader::RFIDReader(byte ss, byte rst) : rfid(ss, rst) {
  ssPin = ss;               // Store which Arduino pin is connected to the RFID SDA (Chip Select)
  rstPin = rst;             // Store which Arduino pin is connected to the RFID RST
}

// Initialize SPI and the RFID module
void RFIDReader::begin() {
  SPI.begin();              // Starts the SPI bus (from <SPI.h>)
  rfid.PCD_Init();          // Initializes the MFRC522 reader chip (from <MFRC522.h>)
  delay(50);                // Short delay to stabilize communication
}

// Check if a new RFID card is present
bool RFIDReader::isCardPresent() {
  // The MFRC522 library provides two functions:
  // 1. PICC_IsNewCardPresent() checks if any card is near the reader
  // 2. PICC_ReadCardSerial() reads the card’s UID if present
  // The function returns true only if both succeed
  return rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial();
}

// Read the UID and return it as a string
String RFIDReader::readUID() {
  String uidStr = "";        // Create an empty string to store the UID
  for (byte i = 0; i < rfid.uid.size; i++) {      // Loop through each byte of the UID
    uidStr += String(rfid.uid.uidByte[i] < 0x10 ? "0" : "");  // Add a leading 0 if the byte is less than 0x10
    uidStr += String(rfid.uid.uidByte[i], HEX);   // Convert the byte to hexadecimal and append
  }
  uidStr.toUpperCase();      // Convert the entire string to uppercase for consistency
  rfid.PICC_HaltA();         // Stop communication with this card (from MFRC522 library)
  return uidStr;             // Return the UID string to the caller
}
