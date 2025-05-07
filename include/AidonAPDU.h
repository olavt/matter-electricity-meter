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

  ~AidonAPDU() = default;

  std::span<const uint8_t> NotificationBody();

private:

  static constexpr size_t HEADER_SIZE = 6;
  std::span<const uint8_t> _buffer;         // Non-owning view of the APDU data.

};
