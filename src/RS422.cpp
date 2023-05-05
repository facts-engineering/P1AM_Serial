/*
  This file is part of the ArduinoRS422 library.
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

#include "RS422.h"

RS422Class::RS422Class(RS485Class& tx_port, RS485Class& rx_port) :
  _tx_port(&tx_port),
  _rx_port(&rx_port)
{	
}

RS422Class::RS422Class(void): 
  _tx_port(new RS485Class(PORT1_SERIAL,PORT1_TX_MINUS_PIN,PORT1_DEFAULT_DE_PIN, PORT1_DEFAULT_RE_PIN)),
  _rx_port(new RS485Class(PORT2_SERIAL,PORT2_TX_MINUS_PIN,PORT2_DEFAULT_DE_PIN, PORT2_DEFAULT_RE_PIN))
{
}


void RS422Class::begin(unsigned long baudrate)
{
  begin(baudrate, SERIAL_8N1);
}

void RS422Class::begin(unsigned long baudrate, uint16_t config)
{
  _baudrate = baudrate;
  _config = config;

  _tx_port->begin(baudrate, config);
  beginTransmission();
  _rx_port->begin(baudrate, config);
  receive();
  _transmisionBegun = true;
}

void RS422Class::end()
{
  _tx_port->end();
  _rx_port->end();

}

int RS422Class::available()
{
  return _rx_port->available();
}

int RS422Class::peek()
{
  return _rx_port->peek();
}

int RS422Class::read(void)
{
  return _rx_port->read();
}

void RS422Class::flush()
{
  return _tx_port->flush();
}

size_t RS422Class::write(uint8_t b)
{
  if (!_transmisionBegun) {
    setWriteError();
    return 0;
  }

  return _tx_port->write(b);
}

RS422Class::operator bool()
{
  return true;
}

void RS422Class::beginTransmission()
{
  _tx_port->beginTransmission();
  _transmisionBegun = true;
}

void RS422Class::endTransmission()
{
  _tx_port->endTransmission();
}

void RS422Class::receive()
{
    _rx_port->receive();
}

void RS422Class::noReceive()
{
    _rx_port->noReceive();
}

void RS422Class::sendBreak(unsigned int duration)
{
  _tx_port->sendBreak(duration);
}

void RS422Class::sendBreakMicroseconds(unsigned int duration)
{
  _tx_port->sendBreakMicroseconds(duration);
}
