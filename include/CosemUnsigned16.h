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

  CosemUnsigned16(std::span<const uint8_t> fromBytes, int& position);

  uint16_t Value();

  void Log();

private:

  uint16_t _value;

};
