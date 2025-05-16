#pragma once

#include <cstdint>
#include <memory>
#include <span>
#include <string>
#include "silabs_utils.h"

class CosemObject
{

public:

  static std::unique_ptr<CosemObject> CreateObjectHierarchy(std::span<const uint8_t> fromBytes);

  virtual ~CosemObject();

  static std::string ToHexString(const uint8_t bytes[], int length);

  virtual void Log();

protected:

  static std::unique_ptr<CosemObject> Create(std::span<const uint8_t> fromBytes, size_t& position);

private:

  enum class CosemDataType : uint8_t
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
