/*
 *
 * Copyright (c) [2016] by InvenSense, Inc.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

#ifndef _FLASH_MANAGER_H_
#define _FLASH_MANAGER_H_

#include <stdint.h>

/**
 * @brief  Initialize the FLASH
 * @return 0 if init succeeds, flash_status otherwise
 */
int inv_flash_manager_init(void);

/**
 * @brief  Write data to the FLASH sector
 * @param  pData, pointer on 84 bytes buffer of data
 * @return 0 if write succeeds, flash_status otherwise
 */
int inv_flash_manager_writeData(const uint8_t *pData);

/**
 * @brief  Erase a FLASH sector
 * @return 0 if read succeeds, flash_status otherwise
 */
int inv_flash_manager_eraseData(void);

/**
 * @brief  Read data from the FLASH sector
 * @param  pData, pointer on 84 bytes buffer of data
 * @return 0 if read succeeds, flash_status otherwise
 */
int inv_flash_manager_readData(uint8_t *pData);

#endif /* _FLASH_MANAGER_H_ */
