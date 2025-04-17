/*
 * Serial.h
 *
 *  Created on: Dec 22, 2023
 *      Author: olavt
 */

#pragma once

#include "sl_iostream.h"

class SerialPort
{

  // Written to behave like AltSoftSerial for Arduino to test with DS2480B

  private:

    sl_iostream_t* _stream;

  public:

    SerialPort(char* instanceName);

    bool ClearInputBuffer();

    bool GetReadBlockingMode();

    void SetReadBlockingMode(bool blockingMode);

    bool ReadByte(uint8_t& byteRead);

    bool ReadBytes(uint8_t* buffer, int bufferLength, size_t* bytesRead);

    bool WriteByte(uint8_t b);

};
