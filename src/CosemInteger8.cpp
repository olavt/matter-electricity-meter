/*
 * CosemInteger8.cpp
 *
 *  Created on: Feb 3, 2024
 *      Author: olavt
 */

#include "CosemInteger8.h"

CosemInteger8::CosemInteger8(std::span<const uint8_t> fromBytes, int& position)
{
  //SILABS_LOG("[INFO] CosemInteger8::CosemInteger8: position=%d", position);

  _value = fromBytes[position];
  position++;
}

void CosemInteger8::Log()
{
  SILABS_LOG("CosemInteger8: %d", _value);
}

int8_t CosemInteger8::Value()
{
  return _value;
}


