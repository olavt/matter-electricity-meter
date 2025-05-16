/*
 * CosemOctetString.cpp
 *
 *  Created on: Feb 3, 2024
 *      Author: olavt
 */

#include "CosemOctetString.h"
#include <sstream>

  std::unique_ptr<CosemOctetString> CosemOctetString::Create(std::span<const uint8_t> fromBytes, size_t& position)
  {
    if (position >= fromBytes.size()) {
      //SILABS_LOG("[ERROR] CosemOctetString::Create: position=%zu exceeds buffer size=%zu", position, fromBytes.size());
      return nullptr;
    }

    size_t length = fromBytes[position];
    position++;

    // Check if there are enough bytes to read 'length' bytes
    if (position + length > fromBytes.size()) {
      //SILABS_LOG("[ERROR] CosemOctetString::Create: position=%zu, length=%zu exceeds buffer size=%zu", position, length, fromBytes.size());
      return nullptr;
    }

    // Create the object
    CosemOctetString* cosemOctetString = new CosemOctetString();

    cosemOctetString->_buffer = std::vector<uint8_t>(fromBytes.begin() + position, fromBytes.begin() + position + length);
    position += length;

    return std::unique_ptr<CosemOctetString>(cosemOctetString);
  }

std::string CosemOctetString::ToObisCodeString()
{
  // Note! These variables can't be uint8_t, since the stream have a sopecial
  // overload for printing unsigned char as a character and not the number.
  int A = _buffer[0];
  int B = _buffer[1];
  int C = _buffer[2];
  int D = _buffer[3];
  int E = _buffer[4];
  int F = _buffer[5];

  std::stringstream ss;
  ss << A <<  '-' << B << ':' << C << '.' << D << '.' << E << '.' << F;

  return ss.str();
}

std::string CosemOctetString::ToHexString()
{
  return CosemObject::ToHexString(_buffer.data(), _buffer.size());
}

void CosemOctetString::Log()
{
  SILABS_LOG("CosemOctetString: %s", ToHexString().c_str());
}
