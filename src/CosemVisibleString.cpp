/*
 * CosemVisibleString.cpp
 *
 *  Created on: Feb 3, 2024
 *      Author: olavt
 */

#include "CosemVisibleString.h"

CosemVisibleString::CosemVisibleString(std::span<const uint8_t> fromBytes, int& position)
{
  //SILABS_LOG("[INFO] CosemVisibleString::CosemVisibleString: position=%d", position);

  // Length
  uint8_t length = fromBytes[position];
  position++;

  auto data = fromBytes.subspan(position, length);
  _visibleString = std::string(data.begin(), data.end());
  position += length;
}

std::string CosemVisibleString::ToString() const
{
  return _visibleString;
}
