/*
 * HexStrings.cpp
 *
 *  Created on: Feb 6, 2024
 *      Author: olavt
 */

#include "HexStrings.h"
#include <iomanip>
#include <sstream>

std::string HexStrings::ToHexString(const uint8_t* fromBytes, int length)
{
  std::stringstream ss;
  ss << std::hex << std::setfill('0') << std::uppercase;

  for( int i(0) ; i < length; ++i )
      ss << std::setw(2) << static_cast<int>(fromBytes[i]) << " ";

  return ss.str();
}
