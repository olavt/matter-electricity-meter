/*
 * CosemOctetString.cpp
 *
 *  Created on: Feb 3, 2024
 *      Author: olavt
 */

#include "CosemOctetString.h"
#include <sstream>

CosemOctetString::CosemOctetString(std::span<const uint8_t> fromBytes, int& position)
{
  int length = fromBytes[position];
  position++;
  _buffer = std::vector<uint8_t>(fromBytes.begin() + position, fromBytes.begin() + position + length);
  position += length;
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
