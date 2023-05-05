/*
  SerialPassthrough sketch

  This sketch demonstrates how to set up a simple Serial passthrough
  between Serial (USB) and Port 1 and Port 2 of the P1AM-Serial shield.
  It uses the PORT1_RS232_BEGIN and PORT2_RS232_BEGIN  to configure
  and start the ports in RS232 mode.

  created 23 May 2016
  by Erik Nyquist

  modified 4 April 2023 
  by FACTS Engineering, LLC

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/SerialPassthrough
*/

#include <P1AM_Serial.h>

void setup() {

  Serial.begin(9600);
  // Configure and start btoh ports in RS232 mode at 9600 baud, 8 data bits, no parity, 1 stop bit
  PORT1_RS232_BEGIN(9600, SERIAL_8N1); 
  PORT2_RS232_BEGIN(9600, SERIAL_8N1);

}

void loop() {
  if (Serial.available()) { // If anything comes in Serial (USB), write it to Port 1 and Port 2
    uint8_t data = Serial.read();
    Port1.write(data);
    Port2.write(data);
  }

  // Print data from Port 1 and Port 2 to Serial (USB)
  if (Port1.available()) { 
    Serial.write(Port1.read());
  }

  if (Port2.available()) {
    Serial.write(Port2.read());
  }

}

