/*
 * All the resources for this project: http://randomnerdtutorials.com/
 * Modified by Rui Santos
 * Created by FILIPEFLOP
 */
 
#include "MIDIUSB.h" 
#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

//MIDI SECTION
int midiChannel1 = 0;  
int midiChannel2 = 1;  
int midiChannel3 = 2;
int midiChannel4 = 3;  
int midiChannel5 = 4;
int midiChannel6 = 5;  
int midiChannel7 = 6;
 
byte note = 36; //* Lowest note to be used
byte cc = 1; //* Lowest MIDI CC to be used

int ModWheelccNumber = 1; // Mod Wheel is always ccNumber 1 and that is needed to change 'sel' within Ableton Sampler
int AftertouchNumber = 2;
int FootccNumber = 4;

int ccMute = 0;
int cc1 = 10;   // These are mapped to trigger 4x selection ranges in ableton sampler (0-127)
int cc2 = 50;
int cc3 = 90;


char* songUIDs[] = {"27 E9 74 F2", "37 08 75 F2", "47 49 76 F2", "57 ED 74 F2", "A7 0B 75 F2", "C7 E8 74 F2", "47 0B 75 F2", "27 EC 74 F2", "87 3F 7C F2", "27 AA 76 F2", "F7 49 76 F2", "A7 49 76 F2", "84 8A DD 1E"};
char* instrumentUIDs[] = {"E6 7A 78 89", "67 10 DB 2B", "54 8F DA 2B"};
char* diceUIDs[] = {"07 09 75 F2", "B7 19 7A F2", "E7 EC 74 F2", "27 1A 78 F2", "67 19 7A F2", "17 1A 7A F2"};
 
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();

}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  

  ObjectTagChecker();


  
  // Halt PICC
  mfrc522.PICC_HaltA();

  // Stop encryption on PCD
  mfrc522.PCD_StopCrypto1();  
} 
