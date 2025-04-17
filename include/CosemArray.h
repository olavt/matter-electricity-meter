/*
 * CosemArray.h
 *
 *  Created on: Feb 2, 2024
 *      Author: olavt
 */

#pragma once

#include "CosemObject.h"
#include <vector>

class CosemArray : public CosemObject
{

public:

  CosemArray(std::span<const uint8_t> fromBytes, int& position);

  ~CosemArray();

  int size();

  CosemObject*& operator[](int index);

private:

  std::vector<CosemObject*> _cosemObjects;

};
