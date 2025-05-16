/*
 * CosemVisibleString.cpp
 *
 *  Created on: Feb 3, 2024
 *      Author: olavt
 */

#include "CosemVisibleString.h"

std::unique_ptr<CosemVisibleString> CosemVisibleString::Create(std::span<const uint8_t> fromBytes, size_t& position)
{
  //SILABS_LOG("[INFO] CosemVisibleString::Create: position=%d", position);

  // Check if there are enough bytes to read the length field (1 byte)
  if (position >= fromBytes.size()) {
    //SILABS_LOG("[ERROR] CosemVisibleString::Create: position=%zu exceeds buffer size=%zu", position, fromBytes.size());
    return nullptr;
  }

  // Length
  size_t length = fromBytes[position];
  position++;

  // Check if there are enough bytes to read 'length' bytes
  if (position + length > fromBytes.size()) {
    //SILABS_LOG("[ERROR] CosemVisibleString::Create: position=%zu, length=%zu exceeds buffer size=%zu", position, length, fromBytes.size());
    return nullptr;
  }

  // Create the object
  CosemVisibleString* cosemVisibleString = new CosemVisibleString();

  auto data = fromBytes.subspan(position, length);
  cosemVisibleString->_visibleString = std::string(data.begin(), data.end());
  position += length;

  return std::unique_ptr<CosemVisibleString>(cosemVisibleString);
}

std::string CosemVisibleString::ToString() const
{
  return _visibleString;
}
