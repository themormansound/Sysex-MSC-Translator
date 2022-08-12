/* Receive Incoming USB MIDI MSC Comands from Mosart AVAutomation
 * output Midi Notes corresponding to the 'fire' command sent.
 * RaspberryPi PICO edition
 * Captures 8 bytes "F0 7F 04 02 01 07 08 F7" which is sysex to musical midi.
 * v0.1
*/

#include <Arduino.h>
#include <Adafruit_TinyUSB.h>
#include <MIDI.h>

// USB MIDI object
Adafruit_USBD_MIDI usb_midi;
// Create a new instance of the Arduino MIDI Library,
// and attach usb_midi as the transport.
MIDI_CREATE_INSTANCE(Adafruit_USBD_MIDI, usb_midi, MIDI);


void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  usb_midi.setStringDescriptor("MSC-MIDI Translator"); // Set the device name (win10: need to uninstall device for name to change)
  MIDI.begin(MIDI_CHANNEL_OMNI); // Initialize MIDI, and listen to all MIDI channels, This will also call usb_midi's begin()
  MIDI.turnThruOff();
  MIDI.setHandleSystemExclusive(mySystemExclusive); // handles the midi sysex data
  Serial.begin(115200);

  // wait until device mounted
  while( !TinyUSBDevice.mounted() ) delay(1);
}

void loop()
{

  MIDI.read();  
}

void mySystemExclusive(byte *data, unsigned int length) {

      Serial.print("FIRE: ");      // Serial port debugging
      Serial.println(data[6]);     //
      MIDI.sendNoteOn(data[6], 64, 1); // Send the translated NoteOn command

}
