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

  CosemUnsigned32(std::span<const uint8_t> fromBytes, int& position);

  uint32_t Value();

private:

  uint32_t _value;

};
