/*
 * AidonHanReader.cpp
 *
 *  Created on: Feb 6, 2024
 *      Author: olavt
 */

#include "AidonHanReader.h"
#include "AidonAPDU.h"
#include <span>

AidonHanReader::AidonHanReader(SerialPort* serialPort) : HanReader(serialPort)
{
}

CosemArray* AidonHanReader::ReadMeterData()
{
  HdlcFrame* hdlcFrame = ReadHdlcFrame();
  if (hdlcFrame == NULL)
    return NULL;

  auto information = hdlcFrame->Information();

  AidonAPDU* aidonAPDU = new AidonAPDU(information);
  auto notificationBody = aidonAPDU->NotificationBody();

  CosemObject* rootObject = CosemObject::CreateObjectHierarchy(notificationBody);

  // All the data from the HDLC frame is now stored locally in every object
  // in the CosemObject hierarchy.
  delete aidonAPDU;
  delete hdlcFrame;

  // The root object should be a pointer to a CosemArray
  CosemArray* cosemArray = dynamic_cast<CosemArray*>(rootObject);

  return cosemArray;
}


