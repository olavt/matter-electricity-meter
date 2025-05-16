/*
 * CosemObject.cpp
 *
 *  Created on: Feb 2, 2024
 *      Author: olavt
 */

#include "CosemArray.h"
#include "CosemObject.h"
#include "CosemEnum.h"
#include "CosemInteger8.h"
#include "CosemInteger16.h"
#include "CosemOctetString.h"
#include "CosemStructure.h"
#include "CosemUnsigned16.h"
#include "CosemUnsigned32.h"
#include "CosemVisibleString.h"
#include <iomanip>
#include <sstream>

CosemObject::~CosemObject()
{
//  SILABS_LOG("CosemObject destructed.");
}

std::unique_ptr<CosemObject> CosemObject::Create(std::span<const uint8_t> fromBytes, size_t& position)
{
  //SILABS_LOG("[INFO] CosemObject::Create: position=%d", position);
  //SILABS_LOG("%s", CosemObject::ToHexString(fromBytes).c_str());

  if (position >= fromBytes.size()) {
      return nullptr;
  }

  // First byte is COSEM data type
  CosemDataType dataType = static_cast<CosemDataType>(fromBytes[position]);
  position++;

  std::unique_ptr<CosemObject> cosemObject = nullptr;

  switch (dataType)
  {
    case CosemDataType::Array:
      //SILABS_LOG("CosemObject::Create: CosemArray");
      cosemObject = CosemArray::Create(fromBytes, position);
      break;

    case CosemDataType::DoubleLongUnsigned:
      //SILABS_LOG("CosemObject::Create: CosemUnsigned32");
      cosemObject = CosemUnsigned32::Create(fromBytes, position);
      break;

    case CosemDataType::Enum:
      //SILABS_LOG("CosemObject::Create: CosemEnum");
      cosemObject = CosemEnum::Create(fromBytes, position);
      break;

    case CosemDataType::Integer8:
      //SILABS_LOG("CosemObject::Create: CosemInteger8");
      cosemObject = CosemInteger8::Create(fromBytes, position);
      break;

    case CosemDataType::Integer16:
      //SILABS_LOG("CosemObject::Create: CosemInteger16");
      cosemObject = CosemInteger16::Create(fromBytes, position);
      break;

    case CosemDataType::OctetString:
      //SILABS_LOG("CosemObject::Create: CosemOctetString");
      cosemObject = CosemOctetString::Create(fromBytes, position);
      break;

    case CosemDataType::Structure:
      //SILABS_LOG("CosemObject::Create: CosemStructure");
      cosemObject = CosemStructure::Create(fromBytes, position);
      break;

    case CosemDataType::Unsigned16:
      //SILABS_LOG("CosemObject::Create: CosemUnsigned16");
      cosemObject = CosemUnsigned16::Create(fromBytes, position);
      break;

    case CosemDataType::VisibleString:
      //SILABS_LOG("CosemObject::Create: CosemVisibleString");
      cosemObject = CosemVisibleString::Create(fromBytes, position);
      break;
  }

  return cosemObject;
}

std::unique_ptr<CosemObject> CosemObject::CreateObjectHierarchy(std::span<const uint8_t> fromBytes)
{
  size_t position = 0;
  std::unique_ptr<CosemObject> rootObject = CosemObject::Create(fromBytes, position);

  return rootObject;
}

std::string CosemObject::ToHexString(const uint8_t* bytes, int length)
{
  std::stringstream ss;
  ss << std::hex << std::setfill('0') << std::uppercase;

  for( int i(0) ; i < length; ++i )
      ss << std::setw(2) << static_cast<int>(bytes[i]);

  return ss.str();
}

void CosemObject::Log()
{
}
