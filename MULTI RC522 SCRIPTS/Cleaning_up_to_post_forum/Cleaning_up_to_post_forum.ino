#include <SPI.h>
#include <MFRC522.h>

#define MFRC522_SPICLOCK SPI_CLOCK_DIV16    // MFRC522 accept upto 10MHz
#define NR_OF_READERS   2

byte RST_PINs[] = {5, 6};
byte ssPins[] = {2, 3};

MFRC522 mfrc522[NR_OF_READERS];   // Create MFRC522 instance.

// Init array that will store new NUID 
byte nuidPICC[4];


//Initialize.
void setup() {
  Serial.begin(9600); // Initialize serial communications with the PC
  //while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();        // Init SPI bus
  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    mfrc522[reader].PCD_Init(ssPins[reader], RST_PINs[reader]); // Init each MFRC522 card
//    Serial.print(F("Reader "));
//    Serial.print(reader);
//    Serial.print(F(": "));
    mfrc522[reader].PCD_DumpVersionToSerial();
  }
}



void loop() {
  Reader();  
}



void Reader(){
  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    //mfrc522[reader].PCD_SetAntennaGain(mfrc522[reader].RxGain_max); // I tried setting antenna read gain to max: No effect
    
    // Look for new cards
    if (mfrc522[reader].PICC_IsNewCardPresent() && mfrc522[reader].PICC_ReadCardSerial()) {

        // Simplifying: Only getting first byte for testing purposes
        nuidPICC[0] = mfrc522[reader].uid.uidByte[0];
        Serial.print("Reader No.");
        Serial.print(reader+1);  
        Serial.print(": ");  
        Serial.println(nuidPICC[0]);

      // Halt PICC
      mfrc522[reader].PICC_HaltA();
      // Stop encryption on PCD
      mfrc522[reader].PCD_StopCrypto1();
    } //if (mfrc522[reader].PICC_IsNewC
  } //for(uint8_t reader
}


//Helper routine to dump a byte array as hex values to Serial.
void dump_byte_array(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}


