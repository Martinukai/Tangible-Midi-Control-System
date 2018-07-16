void Instruments(){
  if (nuidPICC[0] == 103) {           // SNARE
      noteOn(midiChannel2, 12, 127);    //channel, note, velocity
      noteOn(midiChannel2, 12, 0);        //channel, note, velocity
      MidiUSB.flush();   
  }   

  if (nuidPICC[0] == 84) {           // SHAKER
      noteOn(midiChannel2, 13, 127);    //channel, note, velocity
      noteOn(midiChannel2, 13, 0);        //channel, note, velocity
      MidiUSB.flush();   
  }   

  if (nuidPICC[0] == 167) {        // SOUND OF THE POLICE
      noteOn(midiChannel2, 3, 127); // MOUSE DOWN ONLY - TEST
      //noteOn(midiChannel2, 3, 0);     
      MidiUSB.flush();         
  }          
}

