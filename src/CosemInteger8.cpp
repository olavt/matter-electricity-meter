/*
 * CosemInteger8.cpp
 *
 *  Created on: Feb 3, 2024
 *      Author: olavt
 */

#include "CosemInteger8.h"

std::unique_ptr<CosemInteger8> CosemInteger8::Create(std::span<const uint8_t> fromBytes, size_t& position)
{
  //SILABS_LOG("[INFO] CosemInteger8::Create: position=%d", position);

  // Check if there is enough data to read a single byte
  if (position >= fromBytes.size()) {
    return nullptr;
  }

  // Create the object
  CosemInteger8* cosemInteger8 = new CosemInteger8();

  cosemInteger8->_value = fromBytes[position];
  position++;

  return std::unique_ptr<CosemInteger8>(cosemInteger8);
}

void CosemInteger8::Log()
{
  SILABS_LOG("CosemInteger8: %d", _value);
}

int8_t CosemInteger8::Value()
{
  return _value;
}


