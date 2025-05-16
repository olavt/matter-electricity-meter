/*
 * CosemUnsigned32.cpp
 *
 *  Created on: Feb 3, 2024
 *      Author: olavt
 */

#include "CosemUnsigned32.h"

std::unique_ptr<CosemUnsigned32> CosemUnsigned32::Create(std::span<const uint8_t> fromBytes, size_t& position)
{
  //SILABS_LOG("[INFO] CosemUnsigned32::Create: position=%d", position);

  // Check if there are enough bytes to read a 32-bit unsigned integer (4 bytes)
  if (position + 3 >= fromBytes.size()) {
    //SILABS_LOG("[ERROR] CosemUnsigned32::Create: position=%zu exceeds buffer size=%zu", position, fromBytes.size());
    return nullptr;
  }

  // Create the object
  CosemUnsigned32* cosemUnsigned32 = new CosemUnsigned32();

  cosemUnsigned32->_value = (fromBytes[position] << 24) | (fromBytes[position + 1] << 16) | (fromBytes[position + 2] << 8) | fromBytes[position + 3];
  position += 4;

  return std::unique_ptr<CosemUnsigned32>(cosemUnsigned32);
}

uint32_t CosemUnsigned32::Value()
{
  return _value;
}
