/*
 * CosemUnsigned16.h
 *
 *  Created on: Feb 3, 2024
 *      Author: olavt
 */

#pragma once

#include "CosemObject.h"

class CosemUnsigned16 : public CosemObject
{

public:

  static std::unique_ptr<CosemUnsigned16> Create(std::span<const uint8_t> fromBytes, size_t& position);

  uint16_t Value();

  void Log();

private:

  // Private constructor to enforce factory usage
  CosemUnsigned16() = default;

  uint16_t _value;

};
