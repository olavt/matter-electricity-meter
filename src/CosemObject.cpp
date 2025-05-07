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

std::unique_ptr<CosemObject> CosemObject::Create(std::span<const uint8_t> fromBytes, int& position)
{
  //SILABS_LOG("[INFO] CosemObject::Create: position=%d", position);
  //SILABS_LOG("%s", CosemObject::ToHexString(fromBytes).c_str());

  if (position >= fromBytes.size())
    return 0;

  // First byte is COSEM data type
  CosemDataType dataType = static_cast<CosemDataType>(fromBytes[position]);
  position++;

  std::unique_ptr<CosemObject> cosemObject = nullptr;

  switch (dataType)
  {
    case CosemDataType::Array:
      cosemObject = std::make_unique<CosemArray>(fromBytes, position);
      break;

    case CosemDataType::DoubleLongUnsigned:
      cosemObject = std::make_unique<CosemUnsigned32>(fromBytes, position);

    case CosemDataType::Enum:
      cosemObject = std::make_unique<CosemEnum>(fromBytes, position);
      break;

    case CosemDataType::Integer8:
      cosemObject = std::make_unique<CosemInteger8>(fromBytes, position);
      break;

    case CosemDataType::Integer16:
      cosemObject = std::make_unique<CosemInteger16>(fromBytes, position);
      break;

    case CosemDataType::OctetString:
      cosemObject = std::make_unique<CosemOctetString>(fromBytes, position);
      break;

    case CosemDataType::Structure:
      cosemObject = std::make_unique<CosemStructure>(fromBytes, position);
      break;

    case CosemDataType::Unsigned16:
      cosemObject = std::make_unique<CosemUnsigned16>(fromBytes, position);
      break;

    case CosemDataType::VisibleString:
      cosemObject = std::make_unique<CosemVisibleString>(fromBytes, position);
      break;
  }

  return cosemObject;
}

std::unique_ptr<CosemObject> CosemObject::CreateObjectHierarchy(std::span<const uint8_t> fromBytes)
{
  int position = 0;
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
