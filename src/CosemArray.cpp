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
    CosemObject* cosemObject = CosemObject::Create(fromBytes, position);
    _cosemObjects.push_back(cosemObject);
  }
}

CosemArray::~CosemArray()
{
  int size = _cosemObjects.size();
  for (int i=0; i < size; i++)
    delete _cosemObjects[i];
}

int CosemArray::size()
{
  return _cosemObjects.size();
}

CosemObject*& CosemArray::operator[](int index)
{
  return _cosemObjects[index];
}


