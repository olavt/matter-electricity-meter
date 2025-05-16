/*
 * CosemUnsigned32.h
 *
 *  Created on: Feb 3, 2024
 *      Author: olavt
 */

#pragma once

#include "CosemObject.h"

class CosemUnsigned32 : public CosemObject
{

public:

  static std::unique_ptr<CosemUnsigned32> Create(std::span<const uint8_t> fromBytes, size_t& position);
  uint32_t Value();

private:

  // Private constructor to enforce factory usage
  CosemUnsigned32() = default;

  uint32_t _value;

};
