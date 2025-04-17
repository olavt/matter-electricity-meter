/*
 * CosemObject.h
 *
 *  Created on: Feb 2, 2024
 *      Author: olavt
 */

#pragma once

#include <cstdint>
#include <span>
#include <string>
#include "silabs_utils.h"

class CosemObject
{

public:

  static CosemObject* Create(std::span<const uint8_t> fromBytes, int& position);

  static CosemObject* CreateObjectHierarchy(std::span<const uint8_t> fromBytes);

  virtual ~CosemObject();

  static std::string ToHexString(const uint8_t bytes[], int length);

  virtual void Log();

private:

  enum class CosemDataType
  {
      Array = 0x01,
      Structure = 0x02,
      DoubleLongUnsigned = 0x06,
      OctetString = 0x09,
      VisibleString = 0x0a,
      Integer8 = 0x0f,
      Integer16 = 0x10,
      Unsigned16 = 0x12,
      Enum = 0x16
  };

};
