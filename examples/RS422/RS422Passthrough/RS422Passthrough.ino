/*
  SerialPassthrough sketch

  This sketch relays data sent and received between the Serial port and the RS422 interface
  The two ports on the P1AM-Serial shield are combined for use as one port so full duplex
  communication is possible.

  Port 1 is TX + and -
  Port 2 is RX + and -

  created 23 May 2016
  by Erik Nyquist

  modified 4 April 2023 
  by FACTS Engineering, LLC

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/SerialPassthrough
*/
#include <P1AM_Serial.h>

RS422Class RS422; 

void setup() {
  Serial.begin(9600);
  RS422.begin(9600, SERIAL_8N1); // Configure and start RS422 at 9600 baud, 8 data bits, no parity, 1 stop bit

}

void loop() {
  if (Serial.available()) {
    RS422.write(Serial.read());
  }

  if (RS422.available()) {
    Serial.write(RS422.read());
  }
}

