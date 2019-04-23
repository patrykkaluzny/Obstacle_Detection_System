/*
 * initSystemFunctions.h
 *
 *  Created on: 03.12.2018
 *      Author: Patryk
 */

#ifndef INITSYSTEMFUNCTIONS_H_
#define INITSYSTEMFUNCTIONS_H_

#include "structures.h"


#define FLASH_START_ADRESS (0x08060000) // base adress of sector 7 (0x0800 8000 - 0x0807 FFFF)
#define FLASH_SECTOR FLASH_Sector_7


void FLASH_Configuration();
uint8_t FLASH_WriteListOfID(uint32_t* FlashAddress, typ_ODSsesnorData *dataToWrite, uint8_t dataLength);
uint8_t SaveListOfIDs();
uint8_t FLASH_ReadListOFIDs();
uint8_t AddNewElementToIDList(uint32_t* newSnsorID1,uint32_t* newSnsorID2);
uint8_t FLASH_ClearIDData();
void SortList(typ_ODSsesnorData *ListToSort, uint8_t NumberOfElements);
void StartTimeMeassuringProcedure();
void DeleteNoTimeIDsFromSortedList(typ_ODSsesnorData *SortedList);
void ClearListOfIDs();


#endif /* INITSYSTEMFUNCTIONS_H_ */
