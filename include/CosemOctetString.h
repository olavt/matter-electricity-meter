/*
 * CosemOctetString.h
 *
 *  Created on: Feb 3, 2024
 *      Author: olavt
 */

#pragma once

#include "CosemObject.h"
#include <cstdint>
#include <string>
#include <vector>

class CosemOctetString : public CosemObject
{

public:

  // Copy constructor
  CosemOctetString(const CosemOctetString& copyFrom);

  CosemOctetString(std::span<const uint8_t> fromBytes, int& position);

  ~CosemOctetString();

  // Copy assignment operator
  CosemOctetString& operator=(const CosemOctetString& copyFrom);

  std::string ToObisCodeString();

  std::string ToHexString();

  void Log();

private:

  //std::vector<uint8_t> _buffer;
  uint8_t* _buffer;
  int _size;

};
