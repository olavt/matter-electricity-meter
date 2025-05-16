/*
 * CosemEnum.cpp
 *
 *  Created on: Feb 3, 2024
 *      Author: olavt
 */

#include "CosemEnum.h"

std::unique_ptr<CosemEnum> CosemEnum::Create(std::span<const uint8_t> fromBytes, size_t& position)
{
  //SILABS_LOG("[INFO] CosemEnum::Create: position=%d", position);

  // Check if there is enough data to read a single byte
  if (position >= fromBytes.size()) {
    return nullptr;
  }

  // Create the object
  CosemEnum* cosemEnum = new CosemEnum();

  cosemEnum->_value = fromBytes[position];
  position++;

  return std::unique_ptr<CosemEnum>(cosemEnum);
}

std::string CosemEnum::ToString() const
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


