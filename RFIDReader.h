#ifndef RFIDREADER_H          // Prevents this file from being included multiple times during compilation
#define RFIDREADER_H

#include <Arduino.h>          // Gives access to Arduino core functions (Serial, delay, digitalWrite, etc.)
#include <SPI.h>              // Adds support for SPI communication (used by MFRC522)
#include <MFRC522.h>          // Includes the official RFID driver library for the MFRC522 module

// Define a class that wraps around the MFRC522 library for simpler use
class RFIDReader {
  private:
    MFRC522 rfid;             // Creates an instance of the MFRC522 driver (from the MFRC522 library)
    byte ssPin;               // Stores the Arduino pin connected to SDA (Slave Select / Chip Select)
    byte rstPin;              // Stores the Arduino pin connected to RST (Reset)

  public:
    // Constructor: called when creating an RFIDReader object, e.g. RFIDReader rfid(10, 9);
    RFIDReader(byte ssPin, byte rstPin);

    // Initializes SPI and the RFID hardware (called once in setup)
    void begin();

    // Checks if a card is detected near the reader and if it can be read
    bool isCardPresent();

    // Reads the card's UID (unique identifier) and returns it as a human-readable string
    String readUID();
};

#endif // Ends the include guard
