/*
 * CosemInteger16.h
 *
 *  Created on: Feb 3, 2024
 *      Author: olavt
 */

#pragma once

#include "CosemObject.h"

class CosemInteger16 : public CosemObject
{

public:

  static std::unique_ptr<CosemInteger16> Create(std::span<const uint8_t> fromBytes, size_t& position);

  void Log();

  int16_t Value();

private:

  // Private constructor to enforce factory usage
  CosemInteger16() = default;

  int16_t _value;

};
