/*
 * AidonHanReader.cpp
 *
 *  Created on: Feb 6, 2024
 *      Author: olavt
 */

#include "AidonHanReader.h"
#include "AidonAPDU.h"
#include <memory>
#include <span>

AidonHanReader::AidonHanReader(std::unique_ptr<SerialPort> serialPort) : HanReader(std::move(serialPort))
{
}

std::unique_ptr<CosemArray> AidonHanReader::ReadMeterData()
{
  std::unique_ptr<HdlcFrame> hdlcFrame = ReadHdlcFrame();
  if (hdlcFrame == nullptr)
    return nullptr;

  auto informationField = hdlcFrame->InformationField();

  auto aidonAPDU = std::make_unique<AidonAPDU>(informationField);
  auto notificationBody = aidonAPDU->NotificationBody();

  std::unique_ptr<CosemObject> rootObject = CosemObject::CreateObjectHierarchy(notificationBody);
  //CosemObject* rootObject = CosemObject::CreateObjectHierarchy(notificationBody);

  // All the data from the HDLC frame is now stored locally in every object
  // in the CosemObject hierarchy.

  // The root object should be a pointer to a CosemArray
  auto cosemArray = std::unique_ptr<CosemArray>(dynamic_cast<CosemArray*>(rootObject.release()));

  return cosemArray;
}
