void ObjectTagChecker() {  
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  
  Serial.print("Size of Array: ");
  Serial.println((sizeof(songUIDs)/2));

  for (int i = 0; i < (sizeof(instrumentUIDs)/2); i++) {  // UNIVERSAL MIDI, DONT NEED CHANGE MIDI NUMBER - ONLY FOR THE TRIGGIN OF CLIPS BELOW!
    if (content.substring(1) == instrumentUIDs[i]) {       
        Serial.print("Instr array Index: ");
        Serial.println(i);
//        noteOn(midiChannel1, i, 127);      //channel, note, velocity
//        noteOn(midiChannel1, i, 0);        //channel, note, velocity
//        MidiUSB.flush();  
        controlChange(midiChannel1, ModWheelccNumber, i); // (Channel, CC number, CC value)
        MidiUSB.flush();                   
    } 
  }
  
  for (int i = 0; i < (sizeof(songUIDs)/2); i++) {
    if (content.substring(1) == songUIDs[i]) {        
        Serial.print("Song array Index: ");
        Serial.println(i);
        noteOn(midiChannel4, i, 127);      //channel, note, velocity
        noteOn(midiChannel4, i, 0);        //channel, note, velocity
        MidiUSB.flush();         
    } 
  }
    
  for (int i = 0; i < (sizeof(diceUIDs)/2); i++) {
    if (content.substring(1) == diceUIDs[i]) {        
        Serial.print("Dice array Index: ");
        Serial.println(i);
        noteOn(midiChannel5, i, 127);      //channel, note, velocity
        noteOn(midiChannel5, i, 0);        //channel, note, velocity
        MidiUSB.flush();         
    } 
  }

  
}
