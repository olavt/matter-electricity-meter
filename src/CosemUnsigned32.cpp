/*
 * CosemUnsigned32.cpp
 *
 *  Created on: Feb 3, 2024
 *      Author: olavt
 */

#include "CosemUnsigned32.h"

CosemUnsigned32::CosemUnsigned32(std::span<const uint8_t> fromBytes, int& position)
{
  //SILABS_LOG("[INFO] CosemUnsigned32::CosemUnsigned32: position=%d", position);

  _value = (fromBytes[position] << 24) | (fromBytes[position + 1] << 16) | (fromBytes[position + 2] << 8) | fromBytes[position + 3];
  position += 4;
}

uint32_t CosemUnsigned32::Value()
{
  return _value;
}
