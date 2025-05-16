/*
 * CosemArray.h
 *
 *  Created on: Feb 2, 2024
 *      Author: olavt
 */

#pragma once

#include "CosemObject.h"
#include <memory>
#include <vector>

class CosemArray : public CosemObject
{

public:

  static std::unique_ptr<CosemArray> Create(std::span<const uint8_t> fromBytes, size_t& position);

  ~CosemArray() = default;

  int size() const;

  CosemObject* operator[](size_t index);

  const CosemObject* operator[](size_t index) const;

private:

  // Private constructor to enforce factory usage
  CosemArray() = default;

  std::vector<std::unique_ptr<CosemObject>> _cosemObjects;

};
