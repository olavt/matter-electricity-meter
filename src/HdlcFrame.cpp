/*
 * HdlcFrame.cpp
 *
 *  Created on: Feb 2, 2024
 *      Author: olavt
 */

#include "HdlcFrame.h"
#include "Crc16.h"
#include <cstdint>
#include <span>

HdlcFrame::HdlcFrame()
{
}

void HdlcFrame::AddByte(uint8_t b)
{
  if (Length() >= MAX_BUFFER_SIZE)
    return;

  if (Length() == 0)
  {
      if (b != HDLC_FLAG)
          return; // Ignore until HDLC_FLAG
  }

  if ((b == HDLC_FLAG) && (Length() == 1))
      return; // HDLC_FLAG already added

  _buffer[byteCount] = b;
  byteCount++;
}

// 8.4.1.3 Frame format field
int HdlcFrame::FormatType()
{
  int frameFormat = (_buffer[1] << 8) | _buffer[2];
  int formatType = (frameFormat & 0b1111000000000000) >> 12;

  return formatType;
}

int HdlcFrame::FrameLength()
{
  int frameFormat = (_buffer[1] << 8) | _buffer[2];
  int frameLength = frameFormat & 0b0000011111111111;

  return frameLength;
}

int HdlcFrame::DestinationAddressLength()
{
  int start = 3;
  int index = 0;
  int address = _buffer[start + index];
  while ((address & 0b00000001) != 1)
  {
      index++;
      address = _buffer[start + index];
  }
  int length = index + 1;

  return length;
}

int HdlcFrame::SourceAddressLength()
{
  int start = 3 + DestinationAddressLength();
  int index = 0;
  int address = _buffer[start + index];
  while ((address & 0b00000001) != 1)
  {
      index++;
      address = _buffer[start + index];
  }
  int length = index + 1;

  return length;
}

int HdlcFrame::Control()
{
  int start = 3 + DestinationAddressLength() + SourceAddressLength();
  int control = _buffer[start];

  return control;
}

int HdlcFrame::HeaderCheckSequence()
{
  int start = 4 + DestinationAddressLength() + SourceAddressLength();
  int hcs = (_buffer[start] << 8) | _buffer[start + 1];
  return hcs;
}

std::span<const uint8_t> HdlcFrame::Information()
{
  int start = 9 + DestinationAddressLength() + SourceAddressLength();
  size_t length = (FrameLength() - 2) - start + 1;

  std::span<const uint8_t> information = std::span{_buffer + start, length};

  //ArraySlice<uint8_t>* information = new ArraySlice<uint8_t>(_buffer, start, length);

  return information;
}

int HdlcFrame::FrameCheckSequence()
{
  int start = byteCount - 3;
  int fcs = (_buffer[start + 1] << 8) | _buffer[start];

  return fcs;
}

int HdlcFrame::Length()
{
  return byteCount;
}

bool HdlcFrame::ChecksumIsOk()
{
  bool checksumIsOk = ComputeFrameCheckSequence() == FrameCheckSequence();

  return checksumIsOk;
}

bool HdlcFrame::FrameIsComplete()
{
  // Note! The Aidon meter may include the 0x7e (flag byte) inside the messages
  // Use length to check the frame and do not assume that 0x7e is the closing flag

  if (Length() >= MAX_BUFFER_SIZE)
    return true;

  if (Length() == 0)
      return false;

  if (Length() < 3)
      return false;   // Need to get to FrameLength to have complete message

  if (Length() >= (1 + FrameLength() + 1))
      return true;

  return false;
}

// Private

uint16_t HdlcFrame::ComputeFrameCheckSequence()
{
  // Compute checksum excluding the opening / closing flags (first and last byte) and the two FCS bytes
  int start = 1;
  int length = Length() - start - 3;

  uint16_t fcs = Crc16::CalculateChecksum(_buffer, start, length);

  return fcs;
}




