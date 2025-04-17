/*
 * CosemEnum.cpp
 *
 *  Created on: Feb 3, 2024
 *      Author: olavt
 */

#include "CosemEnum.h"

CosemEnum::CosemEnum(std::span<const uint8_t> fromBytes, int& position)
{
  //SILABS_LOG("[INFO] CosemEnum::CosemEnum: position=%d", position);

  _value = fromBytes[position];
  position++;
}

const char* CosemEnum::ToString()
{
  switch (_value)
  {
      case 27:  return "Watt";
      case 29:  return "var";
      case 30:  return "Wh";
      case 32:  return "varh";
      case 33:  return "A";
      case 35:  return "V";
      default:  return "[Undefined]";
  }
}

void CosemEnum::Log()
{
  SILABS_LOG("CosemEnum: %s", ToString());
}


