/*
 * CosemInteger8.h
 *
 *  Created on: Feb 3, 2024
 *      Author: olavt
 */

#pragma once

#include "CosemObject.h"

class CosemInteger8 : public CosemObject
{

public:

  static std::unique_ptr<CosemInteger8> Create(std::span<const uint8_t> fromBytes, size_t& position);

  void Log();

  int8_t Value();

private:

  // Private constructor to enforce factory usage
  CosemInteger8() = default;

  int8_t _value;

};
