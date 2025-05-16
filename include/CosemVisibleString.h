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

  static std::unique_ptr<CosemVisibleString> Create(std::span<const uint8_t> fromBytes, size_t& position);

  std::string ToString() const;

private:

  // Private constructor to enforce factory usage
  CosemVisibleString() = default;

  std::string _visibleString;

};
