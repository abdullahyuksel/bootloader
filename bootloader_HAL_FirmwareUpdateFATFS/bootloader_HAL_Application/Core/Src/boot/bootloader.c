/*
 * bootloader.c
 *
 *  Created on: 30 Haz 2022
 *      Author: abdul
 */

#include "bootloader.h"

void bootloader_jump_to_user_app (void);
void bootloader_uart_data_read (void);
uint8_t execute_memory_write(uint8_t *Buffer, uint32_t memAddress, uint32_t len);
uint8_t execute_flash_erase(uint8_t sectorNumber, uint8_t numberOfSector);

void bootloader_uart_data_read (void)
{

}
void bootloader_jump_to_user_app (void)
{
	//1. Sıfırlama işleyicisinin adresini tutan bir fonksiyon göstericisi
	void (*bootloader_application_reset_handler)(void);
	printMessages("BL DEBUG MSG: Called bootloader_jump_to_user_application() \n");

	//3. MSP değerini taban adresten çekip applicatiom başlangıcına yaz
	uint32_t mspValue = *(volatile uint32_t*) FLASH_SECTOR2_BASE_ADDRESS;
	printMessages("BL DEBUG MSG: MSP Value: %#x \n", mspValue);
	__set_MSP(mspValue);

	//2. Reset Handler değerini taban adresten çekip applicatiom başlangıcına yaz
	//reset handler adresi msp değerinin adresinden 4 byte sonrasındadır.
	uint32_t resetValue = *(volatile uint32_t*) (FLASH_SECTOR2_BASE_ADDRESS + 4);
	printMessages("BL DEBUG MSG: Reset Value: %#x \n", resetValue);

	//5. Reset Handler ile bir işlev başlat
	bootloader_application_reset_handler = (void*) resetValue;

	//6. Reset Handler çağır ve kullanıcı uygulamasına atla
	bootloader_application_reset_handler();

	//7. system clock başlat.
	__HAL_RCC_SYSCFG_CLK_ENABLE();
}

uint8_t execute_memory_write(uint8_t *Buffer, uint32_t memAddress, uint32_t len)
{
	uint8_t status = HAL_OK;

	HAL_FLASH_Unlock();
	FLASH_WaitForLastOperation(FLASH_TIMEOUT);
	for(uint32_t i = 0 ; i <len ; i++)
	{
		status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, memAddress+i, Buffer[i]);
	}

	HAL_FLASH_Lock();

	return status;
}

uint8_t execute_flash_erase(uint8_t sectorNumber, uint8_t numberOfSector)
{
	FLASH_EraseInitTypeDef FlashEraseInitStruct = {0};
	uint32_t SectorError = 0;
	HAL_StatusTypeDef status = {0};

	if(numberOfSector > 11)
		return INVALID_SECTOR;

	if((sectorNumber <= 11) || (sectorNumber == 0xFF))
	{
		if(sectorNumber == 0xFF)
		{
			FlashEraseInitStruct.TypeErase = FLASH_TYPEERASE_MASSERASE;
		}
		else
		{
			uint8_t remainingSector = 11 - sectorNumber;

			if(sectorNumber > remainingSector)
				sectorNumber = remainingSector;

		FlashEraseInitStruct.TypeErase = FLASH_TYPEERASE_SECTORS;
		FlashEraseInitStruct.Sector = sectorNumber;
		FlashEraseInitStruct.NbSectors = numberOfSector;
		}
		FlashEraseInitStruct.Banks = FLASH_BANK_1;

		HAL_FLASH_Unlock();
		FlashEraseInitStruct.VoltageRange = FLASH_VOLTAGE_RANGE_3;
	    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP);
	    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPERR);
	    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_WRPERR);
	    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_PGAERR);
	    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_PGPERR);
	    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_PGSERR);
		status = (uint8_t) HAL_FLASHEx_Erase(&FlashEraseInitStruct, &SectorError);
		HAL_FLASH_Lock();

		return status;
	}

	return INVALID_SECTOR;
}
