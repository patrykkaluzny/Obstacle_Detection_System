/*
 * flash.c
 *
 *  Created on: 14.12.2018
 *      Author: Patryk
 */
#include "flash.h"
#include "stm32l4xx_hal_flash.h"
#include "stm32l432xx.h"
#include "vl53l0_functions.h"
#include "structures.h"
#include "errorFlags.h"

//vl53lx init variable
extern struct typ_VL53L0_InitData initData;

extern volatile typ_DataToSend							boardData;


FLASH_EraseInitTypeDef EraseVL53LxData;
uint8_t FLASH_ClearDataVL53LxData()
{
	HAL_StatusTypeDef status;
	uint32_t PageError=0;
	//filling erasing structure
	EraseVL53LxData.TypeErase = FLASH_TYPEERASE_PAGES;
	EraseVL53LxData.Banks = FLASH_BANK_1;
	EraseVL53LxData.Page = (uint32_t)_FLASH_PAGE_NR_VL53Lx_DATA;
	EraseVL53LxData.NbPages = (uint32_t)_FLASH_NUMBER_OF_PAGES_VL53Lx_DATA;
	//clear flags before erasing
	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR); //Clear OPTVERR bit set on virgin samples
	//erase flash data
	HAL_FLASH_Unlock();
	status=HAL_FLASHEx_Erase(&EraseVL53LxData, &PageError);
	HAL_FLASH_Lock();
	if(status!=HAL_OK){
		return status; //hal error
		SetBits(boardData.errorFlag,ODSSENSOR_ERROR_FLASH_CLEAR);
	}
	HAL_FLASH_Lock();

	//check if everything is fine
	if (PageError != 0xFFFFFFFF) {
		return 0xF; // something wrong with erasing
		SetBits(boardData.errorFlag,ODSSENSOR_ERROR_FLASH_CLEAR);
	}
	return 0; // everything ok
}
uint8_t FLASH_SaveData(uint32_t *Address,uint64_t Data)
{
	uint8_t status;
	HAL_FLASH_Unlock();
	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR); //Clear OPTVERR bit set on virgin samples
	status=HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD,(uint32_t)Address,Data);
	HAL_FLASH_Lock();
	if (*Address != Data) {
		SetBits(boardData.errorFlag, ODSSENSOR_ERROR_FLASH_DIFF);
		return 4; // Flash content doesn't match SRAM content
	}
	if (status)//0 - ok, 1,2,3 - error
	{
		SetBits(boardData.errorFlag,ODSSENSOR_ERROR_FLASH_ERR);
	}
	return status;
}
void Flash_ReadData(uint32_t *Address, uint64_t *Data)
{
	*Data=*Address;
}
void SaveInitDataVL53Lx()  // todo something better than HAL_GPIO_WritePin(ERROR_GPIO_Port,ERROR_Pin,SET);
{
 //todo function to save vl53lx data structure
	uint64_t data;
	uint32_t* address;
	uint8_t status;

	 status =FLASH_ClearDataVL53LxData();
	 if (status) {HAL_GPIO_WritePin(ERROR_GPIO_Port,ERROR_Pin,SET);}

	 data = (uint64_t)(initData.isManufacturingInitDone);
	 address=(uint32_t *)_FLASH_START_ADDRESS_VL53Lx_DATA;
	 status=FLASH_SaveData(address,data);
	 if (status) {HAL_GPIO_WritePin(ERROR_GPIO_Port,ERROR_Pin,SET);}

	 data = (uint64_t)(initData.initTemp);
	 address+=sizeof(uint64_t);
	 status=FLASH_SaveData(address,data);
	 if (status) {HAL_GPIO_WritePin(ERROR_GPIO_Port,ERROR_Pin,SET);}

	 data = (uint64_t)(initData.isApertureSpads);
	 address+=sizeof(uint64_t);
	 status=FLASH_SaveData(address,data);
	 if (status) {HAL_GPIO_WritePin(ERROR_GPIO_Port,ERROR_Pin,SET);}

	 data = (uint64_t)(initData.offsetMicroMeter);
	 address+=sizeof(uint64_t);
	 status=FLASH_SaveData(address,data);
	 if (status) {HAL_GPIO_WritePin(ERROR_GPIO_Port,ERROR_Pin,SET);}

	 data = (uint64_t)(initData.phaseCal);
	 address+=sizeof(uint64_t);
	 status=FLASH_SaveData(address,data);
	 if (status) {HAL_GPIO_WritePin(ERROR_GPIO_Port,ERROR_Pin,SET);}

	 data = (uint64_t)(initData.refSpadCount);
	 address+=sizeof(uint64_t);
	 status=FLASH_SaveData(address,data);
	 if (status) {HAL_GPIO_WritePin(ERROR_GPIO_Port,ERROR_Pin,SET);}

	 data = (uint64_t)(initData.vhvSettings);
	 address+=sizeof(uint64_t);
	 status=FLASH_SaveData(address,data);
	 if (status) {HAL_GPIO_WritePin(ERROR_GPIO_Port,ERROR_Pin,SET);}

	 data = (uint64_t)(initData.xTalkCompensationRateMegaCps);
	 address+=sizeof(uint64_t);
	 status=FLASH_SaveData(address,data);
	 if (status) {HAL_GPIO_WritePin(ERROR_GPIO_Port,ERROR_Pin,SET);}

}
uint8_t ReadInitDataVL53Lx()
{
	uint64_t data;
	uint32_t* address;
	uint8_t status;

	address=(uint32_t *)_FLASH_START_ADDRESS_VL53Lx_DATA;

	Flash_ReadData(address,&data);
	if(data !=1){
		return 0;
	}
	initData.isManufacturingInitDone=(uint8_t)data;

	address+=sizeof(uint64_t);
	Flash_ReadData(address,&data);
	initData.initTemp= (float) data;

	address+=sizeof(uint64_t);
	Flash_ReadData(address,&data);
	initData.isApertureSpads=(uint8_t)data;

	address+=sizeof(uint64_t);
	Flash_ReadData(address,&data);
	initData.offsetMicroMeter=(int32_t)data;

	address+=sizeof(uint64_t);
	Flash_ReadData(address,&data);
	initData.phaseCal=(uint8_t)data;

	address+=sizeof(uint64_t);
	Flash_ReadData(address,&data);
	initData.refSpadCount=(uint32_t)data;

	address+=sizeof(uint64_t);
	Flash_ReadData(address,&data);
	initData.vhvSettings=(uint8_t)data;

	address+=sizeof(uint64_t);
	Flash_ReadData(address,&data);
	initData.xTalkCompensationRateMegaCps=(FixPoint1616_t)data;

	return 1;
}

