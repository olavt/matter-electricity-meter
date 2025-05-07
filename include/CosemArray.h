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

  CosemArray(std::span<const uint8_t> fromBytes, int& position);

  ~CosemArray() = default;

  int size() const;

  CosemObject* operator[](size_t index);

  const CosemObject* operator[](size_t index) const;

private:

  std::vector<std::unique_ptr<CosemObject>> _cosemObjects;

};
