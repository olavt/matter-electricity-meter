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
  _buffer.reserve(MAX_BUFFER_SIZE);
}

void HdlcFrame::AddByte(uint8_t b)
{
  if (_buffer.size() >= MAX_BUFFER_SIZE)
      return;

  if (Length() == 0)
  {
      if (b != HDLC_FLAG)
          return; // Ignore until HDLC_FLAG
  }

  if ((b == HDLC_FLAG) && (Length() == 1))
      return; // HDLC_FLAG already added

  _buffer.push_back(b);

}

// 8.4.1.3 Frame format field
int HdlcFrame::FormatType()
{
  int frameFormat = (_buffer[1] << 8) | _buffer[2];
  int formatType = (frameFormat & 0b1111000000000000) >> 12;
  return formatType;
}

size_t HdlcFrame::FrameLength()
{
  uint16_t frameFormat = (_buffer[1] << 8) | _buffer[2];
  size_t frameLength = frameFormat & 0b0000011111111111;

  return frameLength;
}

size_t HdlcFrame::DestinationAddressLength()
{
  size_t start = 3;
  size_t length = GetAddressLength(start);

  return length;
}

size_t HdlcFrame::SourceAddressLength()
{
  size_t start = 3 + DestinationAddressLength();
  size_t length = GetAddressLength(start);

  return length;
}

uint8_t HdlcFrame::Control()
{
  size_t start = 3 + DestinationAddressLength() + SourceAddressLength();
  uint8_t control = _buffer[start];

  return control;
}

uint16_t HdlcFrame::HeaderCheckSequence()
{
  size_t start = 4 + DestinationAddressLength() + SourceAddressLength();
  uint16_t hcs = (_buffer[start] << 8) | _buffer[start + 1];
  return hcs;
}

std::span<const uint8_t> HdlcFrame::InformationField()
{
  size_t start = 9 + DestinationAddressLength() + SourceAddressLength();
  size_t length = (FrameLength() - 2) - start + 1;

  std::span<const uint8_t> informationField = std::span{_buffer.data() + start, length};

  return informationField;
}

uint16_t HdlcFrame::FrameCheckSequence()
{
  size_t start = Length() - 3;
  uint16_t fcs = (_buffer[start + 1] << 8) | _buffer[start];

  return fcs;
}

size_t HdlcFrame::Length()
{
  return _buffer.size();
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

  if (Length() >= MAX_BUFFER_SIZE) {
    return true;
  }

  if (Length() == 0) {
      return false;
  }

  if (Length() < 3) {
      return false;   // Need to get to FrameLength to have complete message
  }

  if (Length() >= (1 + FrameLength() + 1)) {
      return true;
  }

  return false;
}

// Private

uint16_t HdlcFrame::ComputeFrameCheckSequence()
{
  // Compute checksum excluding the opening / closing flags (first and last byte) and the two FCS bytes
  size_t start = 1;
  size_t length = Length() - start - 3;

  uint16_t fcs = Crc16::CalculateChecksum(_buffer.data(), start, length);

  return fcs;
}

// Format of the HDLC Address
// The HDLC Address in DLMS/COSEM uses a variable-length encoding where each byte’s
// least significant bit (LSB) indicates whether additional address bytes follow:
// LSB = 1: The current byte is the final byte of the address.
// LSB = 0: Additional address bytes follow.
// This allows addresses to be 1, 2, 3, or 4 bytes long, depending on the complexity of the network.
size_t HdlcFrame::GetAddressLength(size_t start)
{
  size_t index = 0;
  uint8_t address = _buffer[start + index];
  while ((address & 0b00000001) != 1)
  {
      index++;
      address = _buffer[start + index];
  }
  size_t length = index + 1;

  return length;
}




