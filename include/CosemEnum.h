/*
 * CosemEnum.h
 *
 *  Created on: Feb 3, 2024
 *      Author: olavt
 */

#pragma once

#include "CosemObject.h"

#include <string>

class CosemEnum : public CosemObject
{

public:

  static std::unique_ptr<CosemEnum> Create(std::span<const uint8_t> fromBytes, size_t& position);

  std::string ToString() const;

  void Log();

private:

    // Private constructor to enforce factory usage
  CosemEnum() = default;

  int8_t _value;

};
