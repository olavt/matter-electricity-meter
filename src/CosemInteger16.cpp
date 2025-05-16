/*
 * CosemInteger16.cpp
 *
 *  Created on: Feb 3, 2024
 *      Author: olavt
 */

#include "CosemInteger16.h"

std::unique_ptr<CosemInteger16> CosemInteger16::Create(std::span<const uint8_t> fromBytes, size_t& position)
{
  //SILABS_LOG("[INFO] CosemInteger16::Create: position=%d", position);

  // Check if there are enough bytes to read a 16-bit integer (2 bytes)
  if (position + 1 >= fromBytes.size()) {
    return nullptr;
  }

  // Create the object
  CosemInteger16* cosemInteger16 = new CosemInteger16();

  cosemInteger16->_value = (fromBytes[position] << 8) | fromBytes[position + 1];
  position += 2;

  return std::unique_ptr<CosemInteger16>(cosemInteger16);
}

void CosemInteger16::Log()
{
  SILABS_LOG("CosemInteger16: %d", _value);
}

int16_t CosemInteger16::Value()
{
  return _value;
}

