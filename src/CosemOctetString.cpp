/*
 * CosemOctetString.cpp
 *
 *  Created on: Feb 3, 2024
 *      Author: olavt
 */

#include "CosemOctetString.h"
#include <sstream>
#include <vector>

CosemOctetString::CosemOctetString(const CosemOctetString& copyFrom)
{
    _size = copyFrom._size;
    _buffer = new uint8_t[copyFrom._size];
    for (int i = 0; i < copyFrom._size; i++)
      _buffer[i] = copyFrom._buffer[i];
}

CosemOctetString::CosemOctetString(std::span<const uint8_t> fromBytes, int& position)
{
  int length = fromBytes[position];
  position++;

  //SILABS_LOG("[INFO] CosemOctetString::CosemOctetString: position=%d, length=%d", position);

  _buffer = new uint8_t[length];
  for (int i=0; i < length; i++)
    _buffer[i] = fromBytes[position + i];
  _size = length;

  //_buffer.reserve(length);
  //for (int i=0; i < length; i++)
  //  _buffer.push_back(fromBytes[i]);

  position += length;
}

CosemOctetString::~CosemOctetString()
{
  delete[] _buffer;
}

// Copy assignment operator
CosemOctetString& CosemOctetString::operator=(const CosemOctetString& copyFrom)
{
  uint8_t* localArray = new uint8_t[copyFrom._size];
  // If the above statement throws,
  // the object is still in the same state as before.
  // None of the following statements will throw an exception :)
  for (int i = 0; i < copyFrom._size; i++)
      localArray[i] = copyFrom._buffer[i];
  delete[] _buffer;
  _buffer = localArray;
  _size = copyFrom._size;

  return *this;
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
  return CosemObject::ToHexString(_buffer, _size);
}

void CosemOctetString::Log()
{
  SILABS_LOG("CosemOctetString: %s", ToHexString().c_str());
}
