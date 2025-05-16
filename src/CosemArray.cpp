/*
 * CosemArray.cpp
 *
 *  Created on: Feb 2, 2024
 *      Author: olavt
 */

#include "CosemArray.h"

std::unique_ptr<CosemArray> CosemArray::Create(std::span<const uint8_t> fromBytes, size_t& position)
{
  //SILABS_LOG("[INFO] CosemArray::Create: position=%d", position);

  if (position >= fromBytes.size()) {
      // SILABS_LOG("[ERROR] CosemArray::Create: Position exceeds span size.");
      return nullptr;
  }

  // Create the object
  CosemArray* cosemArray = new CosemArray();

  // Parse number of objects
  size_t numObjects = fromBytes[position];
  position++;

  // Reserve space to avoid reallocations
  cosemArray->_cosemObjects.reserve(numObjects);

  // Create child objects
  for (size_t i=0; i < numObjects; i++)
  {
      std::unique_ptr<CosemObject> childObject = CosemObject::Create(fromBytes, position);
      if (!childObject) {
          // Handle failure (e.g., log error and return nullptr)
          // SILABS_LOG("[ERROR] CosemArray::Create: Failed to create CosemObject at index %u", i);
          delete cosemArray;
          return nullptr;
      }

      cosemArray->_cosemObjects.push_back(std::move(childObject));
  }

  return std::unique_ptr<CosemArray>(cosemArray);
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


