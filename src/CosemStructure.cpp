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
      std::unique_ptr<CosemObject> cosemObject = CosemObject::Create(fromBytes, position);
      _cosemObjects.push_back(std::move(cosemObject));
  }
}

int CosemStructure::size() const
{
  return _cosemObjects.size();
}

CosemObject* CosemStructure::operator[](size_t index)
{
    return _cosemObjects.at(index).get();
}

const CosemObject* CosemStructure::operator[](size_t index) const
{
    return _cosemObjects.at(index).get();
}

