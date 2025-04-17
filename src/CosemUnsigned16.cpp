/*
 * CosemUnsigned16.cpp
 *
 *  Created on: Feb 3, 2024
 *      Author: olavt
 */

#include "CosemUnsigned16.h"

CosemUnsigned16::CosemUnsigned16(std::span<const uint8_t> fromBytes, int& position)
{
  //SILABS_LOG("[INFO] CosemUnsigned16::CosemUnsigned16: position=%d", position);

  _value = (fromBytes[position] << 8) | fromBytes[position + 1];
  position += 2;
}

uint16_t CosemUnsigned16::Value()
{
  return _value;
}

void CosemUnsigned16::Log()
{
  //SILABS_LOG("CosemUnsigned16: %u", _value);
}
