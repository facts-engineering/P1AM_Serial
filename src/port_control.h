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

#ifndef port_control_h
#define port_control_h

#include "Arduino.h"
#include "RS485.h"

#ifndef PORT1_SERIAL
#define PORT1_SERIAL Serial1
#define PORT1_MODE_PIN	3
#define PORT1_TX_MINUS_PIN	14
#define PORT1_RX_PLUS_PIN 13
#define PORT1_DEFAULT_DE_PIN	A6
#define PORT1_DEFAULT_RE_PIN	PORT1_DEFAULT_DE_PIN
#endif

#ifndef PORT2_SERIAL
#define PORT2_SERIAL Serial2
#define PORT2_MODE_PIN	2
#define PORT2_TX_MINUS_PIN	0
#define PORT2_RX_PLUS_PIN 1
#define PORT2_DEFAULT_DE_PIN	6
#define PORT2_DEFAULT_RE_PIN	PORT2_DEFAULT_DE_PIN
#endif

#define CTS_PIN PORT2_RX_PLUS_PIN
#define RTS_PIN PORT2_TX_MINUS_PIN

#define RS485_MODE 0
#define RS232_MODE 1


int serial_port_config(int port, int mode);	//Set single port mode
void p1am_serial_init();
int start_handshake(int timeout = 1000, int rts = RTS_PIN, int cts = CTS_PIN);
void set_rts(int rts = RTS_PIN);
void clear_rts(int rts = RTS_PIN);
int read_cts(int cts = CTS_PIN);

extern RS485Class RS485;
#define Port1 RS485
#define Port1_RS485 RS485
#define Port1_RS232 PORT1_SERIAL

extern RS485Class Port2;
#define Port2_RS485 Port2
#define Port2_RS232 PORT2_SERIAL


// Begin functions defined with macros so 232 options can be used in 485 only libraries
// Configures 485 ports to default to receving
#define PORT1_RS485_BEGIN(...) {   \
        serial_port_config(1, RS485_MODE); \
        Port1.begin(__VA_ARGS__);    \
        Port1.endTransmission();    \
    }

#define PORT1_RS232_BEGIN(...) {   \
        serial_port_config(1, RS232_MODE); \
        Port1.begin(__VA_ARGS__);    \
        Port1.beginTransmission();    \
    }

#define PORT2_RS485_BEGIN(...) {   \
        serial_port_config(2, RS485_MODE); \
        Port2.begin(__VA_ARGS__);    \
        Port2.endTransmission();    \
    }

#define PORT2_RS232_BEGIN(...) {   \
        serial_port_config(2, RS232_MODE); \
        Port2.begin(__VA_ARGS__);    \
        Port2.beginTransmission();    \
    }

#endif
