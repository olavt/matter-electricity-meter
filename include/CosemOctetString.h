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

  static std::unique_ptr<CosemOctetString> Create(std::span<const uint8_t> fromBytes, size_t& position);

  ~CosemOctetString() = default;

  // Copy constructor
  CosemOctetString(const CosemOctetString& copyFrom) = default;

  // Copy assignment operator
  CosemOctetString& operator=(const CosemOctetString& copyFrom) = default;

  std::string ToObisCodeString();

  std::string ToHexString();

  void Log();

private:

  // Private constructor to enforce factory usage
  CosemOctetString() = default;

  std::vector<uint8_t> _buffer;

};
