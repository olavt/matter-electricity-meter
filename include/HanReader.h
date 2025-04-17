/*
 * HanReader.h
 *
 *  Created on: Feb 5, 2024
 *      Author: olavt
 */

#pragma once

#include "CosemArray.h"
#include "HdlcFrame.h"
#include "SerialPort.h"
#include <cstdint>
#include <deque>

class HanReader
{

public:

  HanReader(SerialPort* serialPort);

  virtual CosemArray* ReadMeterData() = 0;

  bool Open();

protected:

  // Returns NULL if no HDLC frame is ready / complete
  HdlcFrame* ReadHdlcFrame();

private:

  bool GetNextInputByte(uint8_t& readByte);

  void GetMoreBytes();

  void GetTestBytes();

  void ReadBytesFromSerialPort();

  static constexpr std::size_t MAX_BUFFER_SIZE = 512;

  HdlcFrame* _hdlcFrame;
  SerialPort* _serialPort;
  std::deque<uint8_t> _readBuffer;

};
