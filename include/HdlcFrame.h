/*
 * HdlcFrame.h
 *
 *  Created on: Feb 2, 2024
 *      Author: olavt
 */

#pragma once

#include <cstdint>
#include <span>
#include <vector>

class HdlcFrame
{

// Format documentation Green-Book-Ed-10-Excerpt.pdf

public:

  static const int HDLC_FLAG = 0x7E;

  HdlcFrame();

  void AddByte(uint8_t b);

  // 8.4.1.3 Frame format field, subfields FormatType, FrameLength

  int FormatType();

  size_t FrameLength();

  size_t DestinationAddressLength();

  size_t SourceAddressLength();

  uint8_t Control();

  uint16_t HeaderCheckSequence();

  // The Information field contains the payload
  std::span<const uint8_t> InformationField();

  // A 16-bit CRC (Cyclic Redundancy Check)
  uint16_t FrameCheckSequence();

  // The total length of the HDLC Frame
  int Length();

  bool ChecksumIsOk();

  bool FrameIsComplete();

private:

  static constexpr std::size_t MAX_BUFFER_SIZE = 512;
  std::vector<uint8_t> _buffer;

  uint16_t ComputeFrameCheckSequence();

  size_t GetAddressLength(size_t start);

};
