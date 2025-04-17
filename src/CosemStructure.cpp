/*
 * CosemStructure.cpp
 *
 *  Created on: Feb 3, 2024
 *      Author: olavt
 */

#include "CosemStructure.h"

CosemStructure::CosemStructure(std::span<const uint8_t> fromBytes, int& position)
{
  //SILABS_LOG("[INFO] CosemStructure::CosemStructure: position=%d", position);

  int length = fromBytes[position];
  position++;

  _cosemObjects.reserve(length);

  for (int i=0; i < length; i++)
  {
    CosemObject* cosemObject = CosemObject::Create(fromBytes, position);
    _cosemObjects.push_back(cosemObject);
  }
}

CosemStructure::~CosemStructure()
{
  int size = _cosemObjects.size();
  for (int i=0; i < size; i++)
    delete _cosemObjects[i];
}

int CosemStructure::size()
{
  return _cosemObjects.size();
}

CosemObject*& CosemStructure::operator[](int index)
{
  return _cosemObjects[index];
}


