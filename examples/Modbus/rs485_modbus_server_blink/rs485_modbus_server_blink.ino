/*
  Modbus RTU Server LED

  This sketch creates a Modbus RTU Server with a simulated coil.
  The value of the simulated coil is set on the LED

  Server is on port 1 of the P1AM-Serial shield and is set to RS485 mode.

  The Termination line (T) should be tied (i.e. jumpered) to the non-inverting input (RX/+) 
  on the P1AM-Serial shield when using long cable lengths, high data rates, or in cases 
  where communications are noisy.

  created 16 July 2018
  by Sandeep Mistry

  modified 4 April 2023 
  by FACTS Engineering, LLC
*/

#include <ArduinoRS485.h> // ArduinoModbus depends on the ArduinoRS485 library
#include <ArduinoModbus.h>
#include <P1AM_Serial.h>

const int ledPin = LED_BUILTIN;

void setup() {
  Serial.begin(9600);
  Serial.println("Modbus RTU Server LED");
  
  serial_port_config(1, RS485_MODE); // Set port 1 to RS485 prior to starting modbus client

  // start the Modbus RTU server, with (slave) id 1, 9600 baud and 8 data bits, no parity, 1 stop bit
  // see https://www.arduino.cc/reference/en/language/functions/communication/serial/begin/ for other configurations
  if (!ModbusRTUServer.begin(1, 9600, SERIAL_8N1)) {
    Serial.println("Failed to start Modbus RTU Server!");
    while (1);
  }

  // configure the LED
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  // configure a single coil at address 0x00
  ModbusRTUServer.configureCoils(0x00, 1);
}

void loop() {
  // poll for Modbus RTU requests
  int packetReceived = ModbusRTUServer.poll();

  if(packetReceived) {
    // read the current value of the coil
    int coilValue = ModbusRTUServer.coilRead(0x00);
  
    if (coilValue) {
      // coil value set, turn LED on
      digitalWrite(ledPin, HIGH);
    } else {
      // coil value clear, turn LED off
      digitalWrite(ledPin, LOW);
    }
  }
}
