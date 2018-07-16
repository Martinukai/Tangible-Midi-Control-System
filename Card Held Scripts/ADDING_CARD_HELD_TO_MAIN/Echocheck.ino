void echoCheck() { // Timer2 interrupt calls this function every 24uS where you can check the ping status.
  // Don't do anything here!
  if (sonar.check_timer()) { // This is how you check to see if the ping was received.
    // Here's where you can add code.
    Serial.print("Ping: ");
    Serial.print(sonar.ping_result / US_ROUNDTRIP_CM); // Ping returned, uS result in ping_result, convert to cm with US_ROUNDTRIP_CM.
    Serial.println("cm");
    
    int mappedVal = sonar.ping_cm();
    mappedVal = map(mappedVal, 0, 100, 0, 127);
    //Serial.println(mappedVal);
    
        controlChange(midiChannel1, 14, 10*(sonar.ping_result / US_ROUNDTRIP_CM)); // (Channel, CC number, CC value)
        MidiUSB.flush();      
  }
  // Don't do anything here!
}

