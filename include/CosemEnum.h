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

  CosemEnum(std::span<const uint8_t> fromBytes, int& position);

  std::string ToString() const;

  void Log();

private:

  int8_t _value;

};
