/*
  Modbus RTU Client Toggle

  This sketch toggles the coil of a Modbus RTU server connected via RS485
  on and off every second.

  Client is on port 1 of the P1AM-Serial shield and is set to RS485 mode.

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

void setup() {
  Serial.begin(9600);
  Serial.println("Modbus RTU Client Toggle");
    
  serial_port_config(1, RS485_MODE); // Set port1 to RS485 prior to starting modbus client

  // start the Modbus RTU client at 9600 baud and 8 data bits, no parity, 1 stop bit
  // see https://www.arduino.cc/reference/en/language/functions/communication/serial/begin/ for other configurations
  if (!ModbusRTUClient.begin(9600, SERIAL_8N1)) {
    Serial.println("Failed to start Modbus RTU Client!");
    while (1);
  }
}

void loop() {
  // for (slave) id 1: write the value of 0x01, to the coil at address 0x00 
  if (!ModbusRTUClient.coilWrite(1, 0x00, 0x01)) {
    Serial.print("Failed to write coil! ");
    Serial.println(ModbusRTUClient.lastError());
  }

  // wait for 1 second
  delay(1000);

  // for (slave) id 1: write the value of 0x00, to the coil at address 0x00 
  if (!ModbusRTUClient.coilWrite(1, 0x00, 0x00)) {
    Serial.print("Failed to write coil! ");
    Serial.println(ModbusRTUClient.lastError());
  }

  // wait for 1 second
  delay(1000);
}
