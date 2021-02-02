/*
 * 24c02.c
 *
 *  Created on: Jan 30, 2021
 *      Author: 16892
 */


#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_i2c.h"

#include "24c02.h"

/*****************************************************************/

#define I2C_MAX_DELAY (1000) /* 1000 ticks, here 1 tick = 1ms */

extern I2C_HandleTypeDef hi2c1;

/*****************************************************************/

static inline int i2c_write_byte(uint16_t dev_addr, uint16_t addr, uint8_t dat)
{
	 return HAL_I2C_Mem_Write(&hi2c1, dev_addr, addr, I2C_MEMADD_SIZE_8BIT, &dat, 1, I2C_MAX_DELAY);
}

static inline int i2c_read_byte(uint16_t dev_addr, uint16_t addr, uint8_t *dat)
{
	return HAL_I2C_Mem_Read(&hi2c1, dev_addr, addr, I2C_MEMADD_SIZE_8BIT, dat, 1, I2C_MAX_DELAY);
}

/*****************************************************************/

int at24c02_write_byte(uint16_t addr, uint8_t dat)
{
	 return i2c_write_byte(AT24C02_ADDR_WR, addr, dat);
}

int at24c02_read_byte(uint16_t addr, uint8_t *dat)
{
	return i2c_read_byte(AT24C02_ADDR_RD, addr, dat);
}

#if 0
int at24c02_write(uint16_t addr, uint8_t *buf, uint32_t size)
{

}

int at24c02_read(uint16_t addr, uint8_t *buf, uint32_t size)
{

}
#endif

