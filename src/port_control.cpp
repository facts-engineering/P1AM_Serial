/*
MIT License

Copyright (c) 2023 FACTS Engineering, LLC

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#include "port_control.h"

bool p1am_init = false;

void p1am_serial_init(){
  if (&RS485 != NULL){
    RS485.setPins(PORT1_TX_MINUS_PIN, PORT1_DEFAULT_DE_PIN, PORT1_DEFAULT_RE_PIN); // Overwrite default pins from Arduino library
  }

  p1am_init = true;
}

int serial_port_config(int port, int mode){
    if(!p1am_init){
        p1am_serial_init();
    }

    if (mode == 232) mode = RS232_MODE;
    else if (mode == 485) mode = RS485_MODE;

	if(mode != RS232_MODE && mode != RS485_MODE){
		return -1;
	} 
	else if(mode == RS232_MODE) {
		if(port == 1) {
			pinMode(PORT1_DEFAULT_DE_PIN, INPUT);
            Port1.setPins(PORT1_TX_MINUS_PIN, -1, -1);
            Port1.setDelays(0, 0);
            Port1.beginTransmission(); // Allows for easier imitation of RS485 mode
		} 
		else if(port == 2) {
			pinMode(PORT2_DEFAULT_DE_PIN, INPUT);
            Port2.setPins(PORT2_TX_MINUS_PIN, -1, -1);
            Port2.setDelays(0, 0);
            Port2.beginTransmission();
		}
	}
	
	if(port == 1){
		pinMode(PORT1_MODE_PIN, OUTPUT);
		digitalWrite(PORT1_MODE_PIN, mode);
	}
	else if(port == 2){
		pinMode(PORT2_MODE_PIN, OUTPUT);
		digitalWrite(PORT2_MODE_PIN, mode);
	}
	else{
		return -2;
	}
	
	return 0;
}	

int start_handshake(int rts, int cts, unsigned long timeout){
	unsigned long start = 0;
	
	set_rts(rts);
	start = millis();
	while(millis() - start > timeout){
		if(digitalRead(cts)){
			return 0;
		}
	}
	
	return -1; //Timed out
}

void clear_rts(int rts){
	pinMode(rts, OUTPUT);
	digitalWrite(rts, LOW);
}

void set_rts(int rts){
	pinMode(rts, OUTPUT);
	digitalWrite(rts, HIGH);
}

int read_cts(int cts){
	pinMode(cts, INPUT);
	return digitalRead(cts);
}

#ifdef PORT2_SERIAL
RS485Class Port2(PORT2_SERIAL, PORT2_TX_MINUS_PIN, PORT2_DEFAULT_DE_PIN, PORT2_DEFAULT_RE_PIN);
#endif
