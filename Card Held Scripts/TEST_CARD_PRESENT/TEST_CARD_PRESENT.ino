// Credit to "Chefslot" for the card present checker code: https://github.com/miguelbalboa/rfid/issues/188

#include "MIDIUSB.h"

// RFID Stuff
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9           // Configurable, see typical pin layout above
  #define SS_PIN          10          // Configurable, see typical pin layout above
  
  MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

  int midiChannel1 = 0;  

  
  //*****************************************************************************************//
  void setup() {
    Serial.begin(9600);                                           // Initialize serial communications with the PC
    SPI.begin();                                                  // Init SPI bus
    mfrc522.PCD_Init();                                              // Init MFRC522 card
  }
  uint8_t control = 0x00;
  
  //*****************************************************************************************//
  
  
  
  void loop() {
  
    // Look for new cards
    if ( !mfrc522.PICC_IsNewCardPresent()) {
      return;
    }
    if ( !mfrc522.PICC_ReadCardSerial()) {
      return;
    }

    bool result = true;
    uint8_t buf_len = 4;
  
    Serial.println("NewCard ");
          noteOn(midiChannel1, 2, 127); //channel, note, velocity
          noteOn(midiChannel1, 2, 0);        //channel, note, velocity
          MidiUSB.flush();         

    
    while (true) {
    while (true) {
      control = 0;
      for (int i = 0; i < 3; i++) {
        if (!mfrc522.PICC_IsNewCardPresent()) {
          if (mfrc522.PICC_ReadCardSerial()) {
            //Serial.print('a');
            control |= 0x16;
          }
          if (mfrc522.PICC_ReadCardSerial()) {
            //Serial.print('b');
            control |= 0x16;
          }
          //Serial.print('c');
          control += 0x1;
        }
        //Serial.print('d');
        control += 0x4;
      }
  
      Serial.println(control);
      if (control == 13 || control == 14) {
        //card is still there
      } else {
        break;
      }

      
    }
    Serial.println("CardRemoved");
          noteOn(midiChannel1, 3, 127); //channel, note, velocity
          noteOn(midiChannel1, 3, 0);        //channel, note, velocity
          MidiUSB.flush();   
    
    //delay(500); //change value if you want to read cards faster
  
    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
  }



//******************************************************************
// These are midi functions specifically for the Arduino Micro Pro
void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}
