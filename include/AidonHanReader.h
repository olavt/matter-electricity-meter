/*
 * AidonHanReader.h
 *
 *  Created on: Feb 6, 2024
 *      Author: olavt
 */

#pragma once

#include "HanReader.h"

class AidonHanReader : public HanReader
{

public:

  AidonHanReader(std::unique_ptr<SerialPort> serialPort);

  std::unique_ptr<CosemArray> ReadMeterData() override;

};
