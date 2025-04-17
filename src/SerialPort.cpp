/*
 * Serial.cpp
 *
 *  Created on: Dec 22, 2023
 *      Author: olavt
 */

#include <SerialPort.h>
#include "sl_iostream_uart.h"
#include "sl_iostream_handles.h"
#include "silabs_utils.h"

SerialPort::SerialPort(char* instanceName)
{
  _stream = sl_iostream_get_handle(instanceName);
}

bool SerialPort::ClearInputBuffer()
{
  bool success = false;

  uint8_t buffer[128];
  size_t bytes_read;
  sl_status_t status = sl_iostream_read(_stream, &buffer, sizeof(buffer), &bytes_read);
  if ((status == SL_STATUS_OK) || (status == SL_STATUS_EMPTY))
    success = true;

  return success;
}

bool SerialPort::GetReadBlockingMode()
{
  bool readBlocking = sl_iostream_uart_get_read_block((sl_iostream_uart_t*)_stream);
  return readBlocking;
}

void SerialPort::SetReadBlockingMode(bool blocking)
{
  sl_iostream_uart_set_read_block((sl_iostream_uart_t*)_stream, blocking);
}

bool SerialPort::ReadByte(uint8_t& byteRead)
{
  size_t bytesRead;
  sl_status_t status = sl_iostream_read(_stream, &byteRead, 1, &bytesRead);
  //SILABS_LOG("Serial::ReadBytes: status=%u, bytesRead=%u.", status, bytesRead);
  if (status != SL_STATUS_OK)
    return false;

  return true;
}

bool SerialPort::ReadBytes(uint8_t* buffer, int bufferLength, size_t* bytesRead)
{
  sl_status_t status = sl_iostream_read(_stream, buffer, bufferLength, bytesRead);
  //SILABS_LOG("Serial::ReadBytes: status=%u, bytesRead=%u.", status, *bytesRead);
  if ((status != SL_STATUS_OK) && (status != SL_STATUS_EMPTY))
    return false;


  return true;
}

bool SerialPort::WriteByte(uint8_t b)
{
  sl_status_t status = sl_iostream_write(_stream, &b, sizeof(b));
  //SILABS_LOG("Serial::WriteByte: status=%u, b=%u.", status, b);
  if (status != SL_STATUS_OK)
    return false;

  return true;
}


