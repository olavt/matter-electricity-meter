/*
 * HexStrings.cpp
 *
 *  Created on: Feb 6, 2024
 *      Author: olavt
 */

#include "HexStrings.h"
#include <iomanip>
#include <sstream>

std::string HexStrings::ToHexString(const uint8_t* fromBytes, size_t length)
{
  if (!fromBytes || length == 0) {
    return "";
  }

  std::stringstream ss;
  ss << std::hex << std::setfill('0') << std::uppercase;

  for (size_t i = 0; i < length; ++i) {
    ss << std::setw(2) << static_cast<unsigned int>(fromBytes[i]);
    if (i < length - 1) {
      ss << " ";  // Add space only between bytes, not after the last one
    }
  }

  return ss.str();
}
