/*
 * CosemEnum.h
 *
 *  Created on: Feb 3, 2024
 *      Author: olavt
 */

#pragma once

#include "CosemObject.h"

class CosemEnum : public CosemObject
{

public:

  CosemEnum(std::span<const uint8_t> fromBytes, int& position);

  const char* ToString();

  void Log();

private:

  int8_t _value;

};
