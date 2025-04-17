/*
 * CosemVisibleString.h
 *
 *  Created on: Feb 3, 2024
 *      Author: olavt
 */

#pragma once

#include "CosemObject.h"
#include <deque>
#include <string>

class CosemVisibleString : public CosemObject
{

public:

  CosemVisibleString(std::span<const uint8_t> fromBytes, int& position);

  std::string ToString();

private:

  std::string _visibleString;

};
