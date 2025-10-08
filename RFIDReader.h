#ifndef RFIDREADER_H
#define RFIDREADER_H

#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>  // The standard RFID driver library

class RFIDReader {
  private:
    MFRC522 rfid;     // Instance of the RFID driver
    byte ssPin;       // Slave Select pin
    byte rstPin;      // Reset pin

  public:
    RFIDReader(byte ssPin, byte rstPin);  // Constructor
    void begin();                         // Initialize the reader
    bool isCardPresent();                 // Check if a card is detected
    String readUID();                     // Read card UID as string
};

#endif

