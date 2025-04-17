/*
 * HexStrings.h
 *
 *  Created on: Feb 6, 2024
 *      Author: olavt
 */

#pragma once

#include <cstdint>
#include <string>

class HexStrings
{

public:

  static std::string ToHexString(const uint8_t* fromBytes, int length);

};
