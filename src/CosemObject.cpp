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

CosemObject* CosemObject::Create(std::span<const uint8_t> fromBytes, int& position)
{
  //SILABS_LOG("[INFO] CosemObject::Create: position=%d", position);
  //SILABS_LOG("%s", CosemObject::ToHexString(fromBytes).c_str());

  if (position >= fromBytes.size())
    return 0;

  // First byte is COSEM data type
  CosemDataType dataType = static_cast<CosemDataType>(fromBytes[position]);
  position++;

  CosemObject* cosemObject = 0;

  switch (dataType)
  {
    case CosemDataType::Array:
      cosemObject = new CosemArray(fromBytes, position);
      break;

    case CosemDataType::DoubleLongUnsigned:
      cosemObject = new CosemUnsigned32(fromBytes, position);
      break;

    case CosemDataType::Enum:
      cosemObject = new CosemEnum(fromBytes, position);
      break;

    case CosemDataType::Integer8:
      cosemObject = new CosemInteger8(fromBytes, position);
      break;

    case CosemDataType::Integer16:
      cosemObject = new CosemInteger16(fromBytes, position);
      break;

    case CosemDataType::OctetString:
      cosemObject = new CosemOctetString(fromBytes, position);
      break;

    case CosemDataType::Structure:
      cosemObject = new CosemStructure(fromBytes, position);
      break;

    case CosemDataType::Unsigned16:
      cosemObject = new CosemUnsigned16(fromBytes, position);
      break;

    case CosemDataType::VisibleString:
      cosemObject = new CosemVisibleString(fromBytes, position);
      break;
  }

  return cosemObject;
}

CosemObject* CosemObject::CreateObjectHierarchy(std::span<const uint8_t> fromBytes)
{
  int position = 0;
  CosemObject* rootObject = CosemObject::Create(fromBytes, position);

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
