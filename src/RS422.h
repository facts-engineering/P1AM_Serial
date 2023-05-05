/*
  This file is part of the ArduinoRS485 library.
  Copyright (c) 2018 Arduino SA. All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
  
  This file is based on the ArduinoRS485 library and was modified by 
  FACTS Engineering, LLC as part of the P1AM_Serial Library
  
*/

#ifndef _RS422_H_INCLUDED
#define _RS422_H_INCLUDED

#include <Arduino.h>
#include "RS485.h"
#include "port_control.h"


class RS422Class : public Stream {
  public:
    RS422Class(RS485Class& tx_port, RS485Class& rx_port);
	RS422Class(void);

    void begin(unsigned long baudrate);
    void begin(unsigned long baudrate, uint16_t config);
    void end();
    int available();
    int peek();
    int read(void);
    void flush();
    size_t write(uint8_t b);
    using Print::write; // pull in write(str) and write(buf, size) from Print
    operator bool();

    void beginTransmission();
    void endTransmission();
    void receive();
    void noReceive();

    void sendBreak(unsigned int duration);
    void sendBreakMicroseconds(unsigned int duration);


  private:
	RS485Class* _tx_port;
	RS485Class* _rx_port;

    bool _transmisionBegun;
    unsigned long _baudrate;
    uint16_t _config;
};


#endif
