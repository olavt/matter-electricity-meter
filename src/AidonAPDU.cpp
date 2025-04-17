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

AidonAPDU::~AidonAPDU()
{
}

std::span<const uint8_t> AidonAPDU::NotificationBody()
{
  int start = 6;
  int length = _buffer.size() - 6;

  std::span<const uint8_t> notificationBody = _buffer.subspan(start, length);

  return notificationBody;
}
