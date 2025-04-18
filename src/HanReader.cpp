/*
 * HanReader.cpp
 *
 *  Created on: Feb 5, 2024
 *      Author: olavt
 */

#include "HanReader.h"
#include "HexStrings.h"
#include <chrono>

using namespace std::chrono;

const uint8_t testBytes[] = { 0x7e, 0xa1, 0x8a, 0x41, 0x08, 0x83, 0x13, 0xeb, 0xfd, 0xe6, 0xe7, 0x00, 0x0f, 0x40, 0x00, 0x00, 0x00, 0x00, 0x01, 0x12, 0x02, 0x02, 0x09, 0x06, 0x01, 0x01, 0x00, 0x02, 0x81, 0xff, 0x0a, 0x0b, 0x41, 0x49, 0x44, 0x4f, 0x4e, 0x5f, 0x56, 0x30, 0x30, 0x30, 0x31, 0x02, 0x02, 0x09, 0x06, 0x00, 0x00, 0x60, 0x01, 0x00, 0xff, 0x0a, 0x10, 0x37, 0x33, 0x35, 0x39, 0x39, 0x39, 0x32, 0x38, 0x39, 0x35, 0x38, 0x38, 0x34, 0x39, 0x32, 0x31, 0x02, 0x02, 0x09, 0x06, 0x00, 0x00, 0x60, 0x01, 0x07, 0xff, 0x0a, 0x04, 0x36, 0x35, 0x33, 0x34, 0x02, 0x03, 0x09, 0x06, 0x01, 0x00, 0x01, 0x07, 0x00, 0xff, 0x06, 0x00, 0x00, 0x00, 0xb8, 0x02, 0x02, 0x0f, 0x00, 0x16, 0x1b, 0x02, 0x03, 0x09, 0x06, 0x01, 0x00, 0x02, 0x07, 0x00, 0xff, 0x06, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x0f, 0x00, 0x16, 0x1b, 0x02, 0x03, 0x09, 0x06, 0x01, 0x00, 0x03, 0x07, 0x00, 0xff, 0x06, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x0f, 0x00, 0x16, 0x1d, 0x02, 0x03, 0x09, 0x06, 0x01, 0x00, 0x04, 0x07, 0x00, 0xff, 0x06, 0x00, 0x00, 0x01, 0x80, 0x02, 0x02, 0x0f, 0x00, 0x16, 0x1d, 0x02, 0x03, 0x09, 0x06, 0x01, 0x00, 0x1f, 0x07, 0x00, 0xff, 0x10, 0x00, 0x07, 0x02, 0x02, 0x0f, 0xff, 0x16, 0x21, 0x02, 0x03, 0x09, 0x06, 0x01, 0x00, 0x33, 0x07, 0x00, 0xff, 0x10, 0x00, 0x03, 0x02, 0x02, 0x0f, 0xff, 0x16, 0x21, 0x02, 0x03, 0x09, 0x06, 0x01, 0x00, 0x47, 0x07, 0x00, 0xff, 0x10, 0x00, 0x08, 0x02, 0x02, 0x0f, 0xff, 0x16, 0x21, 0x02, 0x03, 0x09, 0x06, 0x01, 0x00, 0x20, 0x07, 0x00, 0xff, 0x12, 0x09, 0x3c, 0x02, 0x02, 0x0f, 0xff, 0x16, 0x23, 0x02, 0x03, 0x09, 0x06, 0x01, 0x00, 0x34, 0x07, 0x00, 0xff, 0x12, 0x09, 0x40, 0x02, 0x02, 0x0f, 0xff, 0x16, 0x23, 0x02, 0x03, 0x09, 0x06, 0x01, 0x00, 0x48, 0x07, 0x00, 0xff, 0x12, 0x09, 0x2e, 0x02, 0x02, 0x0f, 0xff, 0x16, 0x23, 0x02, 0x02, 0x09, 0x06, 0x00, 0x00, 0x01, 0x00, 0x00, 0xff, 0x09, 0x0c, 0x07, 0xe6, 0x06, 0x06, 0x01, 0x0d, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x02, 0x03, 0x09, 0x06, 0x01, 0x00, 0x01, 0x08, 0x00, 0xff, 0x06, 0x00, 0x43, 0xab, 0xee, 0x02, 0x02, 0x0f, 0x01, 0x16, 0x1e, 0x02, 0x03, 0x09, 0x06, 0x01, 0x00, 0x02, 0x08, 0x00, 0xff, 0x06, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x0f, 0x01, 0x16, 0x1e, 0x02, 0x03, 0x09, 0x06, 0x01, 0x00, 0x03, 0x08, 0x00, 0xff, 0x06, 0x00, 0x00, 0x00, 0x69, 0x02, 0x02, 0x0f, 0x01, 0x16, 0x20, 0x02, 0x03, 0x09, 0x06, 0x01, 0x00, 0x04, 0x08, 0x00, 0xff, 0x06, 0x00, 0x15, 0x04, 0xba, 0x02, 0x02, 0x0f, 0x01, 0x16, 0x20, 0x4f, 0xce, 0x7e };

HanReader::HanReader(SerialPort* serialPort)
{
  _hdlcFrame = 0;
  _serialPort = serialPort;
}

HdlcFrame* HanReader::ReadHdlcFrame()
{
  uint8_t byteRead = 0;
  if (_hdlcFrame == NULL)
    _hdlcFrame = new HdlcFrame();

  while (!_hdlcFrame->FrameIsComplete())
  {
    if (!GetNextInputByte(byteRead))
    {
      SILABS_LOG("HanReader::ReadHdlcFrame: No more input bytes available.");
      return NULL;
    }

    _hdlcFrame->AddByte(byteRead);
  }

  if (byteRead == HdlcFrame::HDLC_FLAG)
    _readBuffer.push_front(byteRead); // Make it available for next frame

  HdlcFrame* hdlcFrame = _hdlcFrame;
  _hdlcFrame = NULL;

  if (!hdlcFrame->ChecksumIsOk())
  {
    SILABS_LOG("HanReader::ReadHdlcFrame: Checksum mismatch.");
    return NULL;
  }

  return hdlcFrame;
}

bool HanReader::GetNextInputByte(uint8_t& byteRead)
{
  if (_readBuffer.size() == 0)
  {
      GetMoreBytes();

      if (_readBuffer.size() == 0)
        return false;
  }

  byteRead = _readBuffer.front();
  _readBuffer.pop_front();

  return true;
}

void HanReader::GetMoreBytes()
{
  if (_serialPort != NULL)
    ReadBytesFromSerialPort();
  else
    GetTestBytes();
}

void HanReader::ReadBytesFromSerialPort()
{
  uint8_t buffer[MAX_BUFFER_SIZE];
  size_t bytesRead;

  bool result = _serialPort->ReadBytes(buffer, MAX_BUFFER_SIZE, &bytesRead);
  if (!result)
    return;

  std::string hexString = HexStrings::ToHexString(buffer, bytesRead);

  SILABS_LOG("HanReader: %d bytes read from serial port.", bytesRead);
  SILABS_LOG("%s", hexString.c_str());

  for (int i=0; i < bytesRead; i++)
    _readBuffer.push_back(buffer[i]);
}

void HanReader::GetTestBytes()
{
  for (int i=0; i < 396; i++)
    _readBuffer.push_back(testBytes[i]);
}


