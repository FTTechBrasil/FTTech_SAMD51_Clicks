/*
  This file is part of the ArduinoModbus library.
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
*/

#include <errno.h>

extern "C" {
#include "libmodbus/modbus.h"
#include "libmodbus/modbus-rtu.h"
}

#include "ModbusRTUServer.h"

ModbusRTUServerClass::ModbusRTUServerClass(RS485Class& rs485) :
  _rs485(&rs485)
{
}

ModbusRTUServerClass::~ModbusRTUServerClass()
{
}

int ModbusRTUServerClass::begin(int id, unsigned long baudrate, uint16_t config)
{
  modbus_t* mb = modbus_new_rtu(_rs485, baudrate, config);
  modbus_set_debug(mb,TRUE);

  if (!ModbusServer::begin(mb, id)) {
    return 0;
  }

  modbus_connect(mb);

  return 1;
}

void ModbusRTUServerClass::poll()
{
  uint8_t request[MODBUS_RTU_MAX_ADU_LENGTH];

  int requestLength = modbus_receive(_mb, request);
  if (requestLength > 0) {
    Serial.print("Received: ");
    for(int i=0; i<requestLength;i++)
    {
      if(request[i]<=0x0F)
        Serial.print('0');
      Serial.print(request[i],HEX);
    }
    Serial.println(" ");
  // Looks like the reply is so fast that the board can't send the signal. 
  // Let's try adding some delay here
  // It worked from 105 to 500 (didn't tried more than this)
#ifdef __SAMD51__
  delay(110);
#endif
  modbus_reply(_mb, request, requestLength, &_mbMapping);
  // Serial.println(_time);
  // if(_time >= 500)
  //   _time=90;
  // else
  // {
  //   _time+=5;
  // }
  }
}

ModbusRTUServerClass ModbusRTUServer(RS485);
