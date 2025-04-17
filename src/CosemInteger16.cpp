/*
 * CosemInteger16.cpp
 *
 *  Created on: Feb 3, 2024
 *      Author: olavt
 */

#include "CosemInteger16.h"

CosemInteger16::CosemInteger16(std::span<const uint8_t> fromBytes, int& position)
{
  //SILABS_LOG("[INFO] CosemInteger16::CosemInteger16: position=%d", position);

  _value = (fromBytes[position] << 8) | fromBytes[position + 1];
  position += 2;
}

void CosemInteger16::Log()
{
  SILABS_LOG("CosemInteger16: %d", _value);
}

int16_t CosemInteger16::Value()
{
  return _value;
}

