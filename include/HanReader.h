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
#include <memory> // For std::unique_ptr

class HanReader
{

public:

  HanReader(std::unique_ptr<SerialPort> serialPort);

  virtual std::unique_ptr<CosemArray> ReadMeterData() = 0;

  bool Open();

protected:

  // Returns nullptr if no HDLC frame is ready / complete
  std::unique_ptr<HdlcFrame> ReadHdlcFrame();

private:

  bool GetNextInputByte(uint8_t& readByte);

  void GetMoreBytes();

  void ReadBytesFromSerialPort();

  void GetTestBytes();

  void CopyBytesWithInsert(std::deque<uint8_t>& destBuffer, const uint8_t* sourceBuffer, size_t bufferSize);

  void CopyBytesWithPushBack(std::deque<uint8_t>& destBuffer, const uint8_t* sourceBuffer, size_t bufferSize);

  static constexpr std::size_t MAX_BUFFER_SIZE = 512;

  //HdlcFrame* _hdlcFrame = nullptr;
  std::unique_ptr<HdlcFrame> _hdlcFrame;
  std::unique_ptr<SerialPort> _serialPort;
  std::deque<uint8_t> _readBuffer;

};
