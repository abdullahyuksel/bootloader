/*
 * bootloader.h
 *
 *  Created on: 30 Haz 2022
 *      Author: abdul
 */

#ifndef SRC_BOOT_BOOTLOADER_H_
#define SRC_BOOT_BOOTLOADER_H_

#include "main.h"

#define FLASH_SECTOR2_BASE_ADDRESS 	0x08008000
#define INVALID_SECTOR 				0x04
#define BL_RX_DATA_LENGTH			100
#define FLASH_TIMEOUT       		50000U /* 50 s */

extern void bootloader_jump_to_user_app (void);
extern void bootloader_uart_data_read (void);
extern uint8_t execute_memory_write(uint8_t *Buffer, uint32_t memAddress, uint32_t len);
extern uint8_t execute_flash_erase(uint8_t sectorNumber, uint8_t numberOfSector);

#endif /* SRC_BOOT_BOOTLOADER_H_ */
