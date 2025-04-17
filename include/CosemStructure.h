/*
 * CosemStructure.h
 *
 *  Created on: Feb 3, 2024
 *      Author: olavt
 */

#pragma once

#include "CosemObject.h"
#include <vector>

class CosemStructure : public CosemObject
{

public:

  CosemStructure(std::span<const uint8_t> fromBytes, int& position);

  ~CosemStructure();

  int size();

  CosemObject*& operator[](int index);

private:

  std::vector<CosemObject*> _cosemObjects;

};
