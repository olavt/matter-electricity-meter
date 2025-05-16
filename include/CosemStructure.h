/*
 * CosemStructure.h
 *
 *  Created on: Feb 3, 2024
 *      Author: olavt
 */

#pragma once

#include "CosemObject.h"
#include <memory>
#include <vector>

class CosemStructure : public CosemObject
{

public:

  static std::unique_ptr<CosemStructure> Create(std::span<const uint8_t> fromBytes, size_t& position);

  ~CosemStructure() = default;

  int size() const;

  CosemObject* operator[](size_t index);

  const CosemObject* operator[](size_t index) const;

private:

  // Private constructor to enforce factory usage
  CosemStructure() = default;

  std::vector<std::unique_ptr<CosemObject>> _cosemObjects;

};
