/*
 * CosemStructure.cpp
 *
 *  Created on: Feb 3, 2024
 *      Author: olavt
 */

#include "CosemStructure.h"

std::unique_ptr<CosemStructure> CosemStructure::Create(std::span<const uint8_t> fromBytes, size_t& position)
{
  //SILABS_LOG("[INFO] CosemStructure::Create: position=%d", position);

  if (position >= fromBytes.size()) {
      // SILABS_LOG("[ERROR] CosemArray::Create: Position exceeds span size.");
      return nullptr;
  }

  // Create the object
  CosemStructure* cosemStructure = new CosemStructure();

  size_t numObjects = fromBytes[position];
  position++;

  cosemStructure->_cosemObjects.reserve(numObjects);

  for (size_t i=0; i < numObjects; i++)
  {
      std::unique_ptr<CosemObject> childObject = CosemObject::Create(fromBytes, position);
      if (!childObject) {
          // Handle failure (e.g., log error and return nullptr)
          // SILABS_LOG("[ERROR] CosemStructure::Create: Failed to create CosemObject at index %u", i);
          delete cosemStructure;
          return nullptr;
      }

      cosemStructure->_cosemObjects.push_back(std::move(childObject));
  }

  return std::unique_ptr<CosemStructure>(cosemStructure);
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

