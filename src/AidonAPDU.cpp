/*
 * AidonAPDU.cpp
 *
 *  Created on: Feb 2, 2024
 *      Author: olavt
 */

#include "AidonAPDU.h"

AidonAPDU::AidonAPDU(std::span<const uint8_t> fromSlice)
{
  _buffer = fromSlice;
}

std::span<const uint8_t> AidonAPDU::NotificationBody()
{
  if (_buffer.size() < HEADER_SIZE) {
    return {};
  };

  size_t start = HEADER_SIZE;
  size_t length = _buffer.size() - start;

  std::span<const uint8_t> notificationBody = _buffer.subspan(start, length);

  return notificationBody;
}
