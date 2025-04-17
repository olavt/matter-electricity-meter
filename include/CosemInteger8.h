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

  CosemInteger8(std::span<const uint8_t> fromBytes, int& position);

  void Log();

  int8_t Value();

private:

  int8_t _value;

};
