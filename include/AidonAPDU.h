/*
 * AidonAPDU.h
 *
 *  Created on: Feb 2, 2024
 *      Author: olavt
 */

#pragma once

#include <cstdint>
#include <span>

class AidonAPDU
{

public:

  AidonAPDU(std::span<const uint8_t> fromSlice);

  ~AidonAPDU();

  std::span<const uint8_t> NotificationBody();

private:

  std::span<const uint8_t> _buffer;

};
