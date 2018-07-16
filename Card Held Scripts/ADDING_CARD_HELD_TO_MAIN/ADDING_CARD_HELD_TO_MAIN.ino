// Credit to "Chefslot" for the card present checker code: https://github.com/miguelbalboa/rfid/issues/188

#include <NewPing.h>
#include "MIDIUSB.h"
#include <SPI.h>
#include <MFRC522.h>
  
#define RST_PIN         9           // Configurable, see typical pin layout above
#define SS_1_PIN        10         // Configurable, see typical pin layout above
#define NR_OF_READERS   1


#define TRIGGER_PIN   6//12 // Arduino pin tied to trigger pin on ping sensor.
#define ECHO_PIN      5//11 // Arduino pin tied to echo pin on ping sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
unsigned int pingSpeed = 50; // How frequently are we going to send out a ping (in milliseconds). 50ms would be 20 times a second.
unsigned long pingTimer;     // Holds the next ping time.

byte ssPins[] = {SS_1_PIN};

MFRC522 mfrc522[NR_OF_READERS];   // Create MFRC522 instance.

// Init array that will store new NUID 
byte nuidPICC[4];

//MIDI SECTION
int midiChannel1 = 0; 
int midiChannel2 = 1; 




//*****************************************************************************************//
void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  pingTimer = millis(); // Start now.
  
  // RFID Stuff
  SPI.begin();        // Init SPI bus
  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    mfrc522[reader].PCD_Init(ssPins[reader], RST_PIN); // Init each MFRC522 card
    Serial.print(F("Reader "));
    Serial.print(reader);
    Serial.print(F(": "));
    mfrc522[reader].PCD_DumpVersionToSerial();
  }  
}
uint8_t control = 0x00;

//*****************************************************************************************//



void loop() {
  
    
  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {

  echoTrigger();
  
    // Look for new cards
    if ( !mfrc522[reader].PICC_IsNewCardPresent()) {
      return;
    }
    if ( !mfrc522[reader].PICC_ReadCardSerial()) {
      return;
    }
  
    bool result = true;
    uint8_t buf_len = 4;
  
    Serial.println("NewCard ");

      nuidPICC[0] = mfrc522[0].uid.uidByte[0];
      Serial.print("                   Reader 2: ");           
      Serial.println(nuidPICC[0]);
  
    Instruments();
    
    
    while (true) {
      control = 0;
      for (int i = 0; i < 3; i++) {
        if (!mfrc522[reader].PICC_IsNewCardPresent()) {
          if (mfrc522[reader].PICC_ReadCardSerial()) {
            //Serial.print('a');
            control |= 0x16;
          }
          if (mfrc522[reader].PICC_ReadCardSerial()) {
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
        break; // If no card then exit loop
      }
    }
    Serial.println("CardRemoved");
          //echoTrigger();
    
          noteOn(midiChannel2, 3, 0);        // MOUSE UP FOR SIREN - TEST
          
          noteOn(midiChannel2, 14, 127); //channel, note, velocity
          noteOn(midiChannel2, 14, 0);        //channel, note, velocity
          MidiUSB.flush();   

          

         
    mfrc522[reader].PICC_HaltA();
    mfrc522[reader].PCD_StopCrypto1();
  }
  echoTrigger();
}
//*****************************************************************************************//a
 
