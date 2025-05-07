/*
 * CosemArray.cpp
 *
 *  Created on: Feb 2, 2024
 *      Author: olavt
 */

#include "CosemArray.h"

CosemArray::CosemArray(std::span< const uint8_t> fromBytes, int& position)
{
  //SILABS_LOG("[INFO] CosemArray::CosemArray: position=%d", position);

  int length = fromBytes[position];
  position++;

  _cosemObjects.reserve(length);

  for (int i=0; i < length; i++)
  {
      std::unique_ptr<CosemObject> cosemObject = CosemObject::Create(fromBytes, position);
      _cosemObjects.push_back(std::move(cosemObject));
  }
}

int CosemArray::size() const
{
  return _cosemObjects.size();
}

CosemObject* CosemArray::operator[](size_t index)
{
    return _cosemObjects.at(index).get();
}

const CosemObject* CosemArray::operator[](size_t index) const
{
    return _cosemObjects.at(index).get();
}


