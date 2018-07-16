void Songs(){
  if (nuidPICC[0] == 39) {        // KELLY WATCH THE STARS
      noteOn(midiChannel1, 1, 127); //channel, note, velocity
      noteOn(midiChannel1, 1, 0);        //channel, note, velocity
      MidiUSB.flush();         
  } 
  
  if (nuidPICC[0] == 55) {        // DRIVE
      noteOn(midiChannel1, 2, 127); //channel, note, velocity
      noteOn(midiChannel1, 2, 0);        //channel, note, velocity
      MidiUSB.flush();         
  } 

  if (nuidPICC[0] == 71) {        // ACE OF SPADES
      noteOn(midiChannel1, 3, 127); //channel, note, velocity
      noteOn(midiChannel1, 3, 0);        //channel, note, velocity
      MidiUSB.flush();         
  } 

  if (nuidPICC[0] == 87) {        // COMPUTER PEOPLE
      noteOn(midiChannel1, 4, 127); //channel, note, velocity
      noteOn(midiChannel1, 4, 0);        //channel, note, velocity
      MidiUSB.flush();         
  } 

  if (nuidPICC[0] == 167) {        // SOUND OF THE POLICE
      noteOn(midiChannel1, 5, 127); //channel, note, velocity
      noteOn(midiChannel1, 5, 0);        //channel, note, velocity
      MidiUSB.flush();         
  }         
  
  if (nuidPICC[0] == 199) {        // GROOVE ARMADA
      noteOn(midiChannel1, 6, 127); //channel, note, velocity
      noteOn(midiChannel1, 6, 0);        //channel, note, velocity
      MidiUSB.flush();         
  }     
}
