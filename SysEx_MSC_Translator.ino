/* Receive Incoming USB MIDI MSC Comands from Mosart AVAutomation
 * output Midi Notes corresponding to the 'fire' command sent.
*/


void setup() {
  Serial.begin(115200);
  usbMIDI.setHandleSystemExclusive(mySystemExclusive); // handles the midi sysex data
  const int channel = 1;
  
}

void loop() {
  // The handler functions are called when usbMIDI reads data.  They
  // will not be called automatically.  You must call usbMIDI.read()
  // regularly from loop() for usbMIDI to actually read incoming
  // data and run the handler functions as messages arrive.
  usbMIDI.read();
}


// This simpler 2-input System Exclusive function can only receive messages
// up to the size of the internal buffer.  Larger messages are truncated, with
// no way to receive the data which did not fit in the buffer.  If both types
// of SysEx functions are set, the 3-input version will be called by usbMIDI.
//
void mySystemExclusive(byte *data, unsigned int length) {

      Serial.print("FIRE: ");
      Serial.println(data[6]);
      usbMIDI.sendNoteOn(data[6], 64, 1);
}
