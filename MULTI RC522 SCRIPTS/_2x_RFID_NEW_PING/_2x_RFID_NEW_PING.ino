/**
 * --------------------------------------------------------------------------------------------------------------------
 * Example sketch/program showing how to read data from more than one PICC to serial.
 * --------------------------------------------------------------------------------------------------------------------
 * This is a MFRC522 library example; for further details and other examples see: https://github.com/miguelbalboa/rfid
 *
 * Example sketch/program showing how to read data from more than one PICC (that is: a RFID Tag or Card) using a
 * MFRC522 based RFID Reader on the Arduino SPI interface.
 *
 * Warning: This may not work! Multiple devices at one SPI are difficult and cause many trouble!! Engineering skill
 *          and knowledge are required!
 *
 * @license Released into the public domain.
 *
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS 1    SDA(SS)      ** custom, take a unused pin, only HIGH/LOW required **
 * SPI SS 2    SDA(SS)      ** custom, take a unused pin, only HIGH/LOW required **
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 *
 */


// MIDI Code Hacked from here https://github.com/silveirago/Build-your-MIDI-controller-Workshop (Gustavo Silveira)
#include "MIDIUSB.h"

#include <SPI.h>
#include <MFRC522.h>

#include <NewPing.h>

#define TRIGGER_PIN  6//12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     5//11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

//#define MFRC522_SPICLOCK SPI_CLOCK_DIV16     // MFRC522 accept upto 10MHz

#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_1_PIN        10         // Configurable, take a unused pin, only HIGH/LOW required, must be diffrent to SS 2
#define SS_2_PIN        8          // Configurable, take a unused pin, only HIGH/LOW required, must be diffrent to SS 1

#define NR_OF_READERS   2

byte ssPins[] = {SS_1_PIN, SS_2_PIN};


MFRC522 mfrc522[NR_OF_READERS];   // Create MFRC522 instance.


// Init array that will store new NUID 
byte nuidPICC[4];


//MIDI SECTION
int midiChannel1 = 1;
int midiChannel2 = 2;  
byte note = 36; //* Lowest note to be used
byte cc = 1; //* Lowest MIDI CC to be used

int ccNumber = 1; // Mod Wheel is always ccNumber 1 and that is needed to change 'sel' within Ableton Sampler
int cc1 = 10;   // These are mapped to trigger 4x selection ranges in ableton sampler (0-127)
int cc2 = 50;
int cc3 = 90;


//Initialize.
void setup() {

  Serial.begin(9600); // Initialize serial communications with the PC
  //Serial.begin(115200); // Initialize serial communications with the PC
    
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)

  SPI.begin();        // Init SPI bus

  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    mfrc522[reader].PCD_Init(ssPins[reader], RST_PIN); // Init each MFRC522 card
    Serial.print(F("Reader "));
    Serial.print(reader);
    Serial.print(F(": "));
    mfrc522[reader].PCD_DumpVersionToSerial();
  }
}



void loop() {
  LeftDice();
  Objects(); 
  //PING();   
}






//Helper routine to dump a byte array as hex values to Serial.
void dump_byte_array(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}



void LeftDice(){
  for (uint8_t reader = 0; reader < 1; reader++) {

    // Look for new cards
    if (mfrc522[0].PICC_IsNewCardPresent() && mfrc522[0].PICC_ReadCardSerial()) {
        nuidPICC[0] = mfrc522[0].uid.uidByte[0];
        Serial.print("Reader 1: ");        
        Serial.println(nuidPICC[0]);

      // Halt PICC
      mfrc522[reader].PICC_HaltA();
      // Stop encryption on PCD
      mfrc522[reader].PCD_StopCrypto1();
    } //if (mfrc522[reader].PICC_IsNewC
  } //for(uint8_t reader
}
//
//
//
void Objects(){
  for (uint8_t reader = 1; reader < 2; reader++) {

    // Look for new cards
    if (mfrc522[1].PICC_IsNewCardPresent() && mfrc522[1].PICC_ReadCardSerial()) {
        nuidPICC[0] = mfrc522[1].uid.uidByte[0];
        Serial.print("                   Reader 2: ");           
        Serial.println(nuidPICC[0]);



    if (nuidPICC[0] == 84) {        // ***** I CHANGED THIS SECTION ******   THE TIN
      Serial.println("TIN");
        controlChange(midiChannel2, ccNumber, cc1); // (Channel, CC number, CC value)
        MidiUSB.flush();         
    } 

    if (nuidPICC[0] == 230) {        // ***** I CHANGED THIS SECTION ******   THE CUP
      Serial.println("CUP");
        controlChange(midiChannel2, ccNumber, cc2); // (Channel, CC number, CC value)
        MidiUSB.flush();         
    } 

    if (nuidPICC[0] == 103) {        // ***** I CHANGED THIS SECTION ******   THE GLASS
      Serial.println("GLASS");
        controlChange(midiChannel2, ccNumber, cc3); // (Channel, CC number, CC value)
        MidiUSB.flush();         
    } 



      // Halt PICC
      mfrc522[reader].PICC_HaltA();
      // Stop encryption on PCD
      mfrc522[reader].PCD_StopCrypto1();
    } //if (mfrc522[reader].PICC_IsNewC
  } //for(uint8_t reader
}


void PING(){
  delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  Serial.print("Ping: ");
  Serial.print(sonar.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
  
        controlChange(midiChannel2, 2, sonar.ping_cm()); // (Channel, CC number, CC value)
        MidiUSB.flush();    


          
}



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
