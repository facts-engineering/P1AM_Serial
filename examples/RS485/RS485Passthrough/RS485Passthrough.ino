/*
  RS-485 Passthrough

  This sketch relays data sent and received between the Serial port and port 1 
  of the P1AM-Serial shield. 

  The Termination line (T) should be tied (i.e. jumpered) to the non-inverting input (RX/+) 
  on the P1AM-Serial shield when using long cable lengths, high data rates, or in cases 
  where communications are noisy.

  created 4 July 2018
  by Sandeep Mistry

  modified 4 April 2023 
  by FACTS Engineering, LLC
*/

#include <ArduinoRS485.h>
#include <P1AM_Serial.h>

void setup() {
  // Set port 1 to RS485 and 115200 baud, 8 data bits, no parity, 1 stop bit
  PORT1_RS485_BEGIN(115200, SERIAL_8N1); 
  Serial.begin(115200);

  Port1.setDelays(100, 100); // Set pre and post transmit delays to 100us
}

void loop() {

  // Wait for data from the USB Serial 
  if(Serial.available()){
    Port1.beginTransmission(); // Set Port1 to begin transmitting
    while(Serial.available()){
      Port1.write(Serial.read()); // Send each byte out Port1
    }
    Port1.endTransmission(); // End transmission and set port back to receive
  }

  if (Port1.available()) { // If data available on Port1
    Serial.write(Port1.read()); // Print data to USB Serial
  }
}
