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

  CosemInteger16(std::span<const uint8_t> fromBytes, int& position);

  void Log();

  int16_t Value();

private:

  int16_t _value;

};
