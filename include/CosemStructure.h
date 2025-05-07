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

  CosemStructure(std::span<const uint8_t> fromBytes, int& position);

  ~CosemStructure() = default;

  int size() const;

  CosemObject* operator[](size_t index);

  const CosemObject* operator[](size_t index) const;

private:

  std::vector<std::unique_ptr<CosemObject>> _cosemObjects;

};
