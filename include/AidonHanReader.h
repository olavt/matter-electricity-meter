/*
 * AidonHanReader.h
 *
 *  Created on: Feb 6, 2024
 *      Author: olavt
 */

#pragma once

#include "CosemArray.h"
#include "HanReader.h"
#include "SerialPort.h"

class AidonHanReader : public HanReader
{

public:

  AidonHanReader(SerialPort* serialPort);

  CosemArray* ReadMeterData();

};
