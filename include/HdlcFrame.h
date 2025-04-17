/*
 * HdlcFrame.h
 *
 *  Created on: Feb 2, 2024
 *      Author: olavt
 */

#pragma once

#include <cstdint>
#include "ArraySlice.h"
#include <span>

class HdlcFrame
{

// Format documentation Green-Book-Ed-10-Excerpt.pdf

public:

  static const int HDLC_FLAG = 0x7E;

  HdlcFrame();

  void AddByte(uint8_t b);

  // 8.4.1.3 Frame format field, subfields FormatType, FrameLength

  int FormatType();

  int FrameLength();

  int DestinationAddressLength();

  int SourceAddressLength();

  int Control();

  int HeaderCheckSequence();

  std::span<const uint8_t> Information();

  int FrameCheckSequence();

  int Length();

  bool ChecksumIsOk();

  bool FrameIsComplete();

private:

  static constexpr std::size_t MAX_BUFFER_SIZE = 512;

  uint8_t _buffer[MAX_BUFFER_SIZE];
  int byteCount = 0;

  uint16_t ComputeFrameCheckSequence();

};
