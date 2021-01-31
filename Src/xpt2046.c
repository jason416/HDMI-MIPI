/*
 * ds1302.c
 *
 *  Created on: Jan 31, 2021
 *      Author: 16892
 */


#include <xpt2046.h>
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_spi.h"
#include "main.h"


/*****************************************************************/

#define SPI_MAX_DELAY (1000) /* 1000 ticks, here 1 tick = 1ms */

extern SPI_HandleTypeDef hspi1;

/*****************************************************************/
//HAL_StatusTypeDef HAL_SPI_Transmit(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size, uint32_t Timeout);
//HAL_StatusTypeDef HAL_SPI_Receive(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size, uint32_t Timeout);

int spi_write(uint8_t *dat, uint16_t len)
{
	return HAL_SPI_Transmit(&hspi1, dat, len, SPI_MAX_DELAY);
}

int spi_read(uint8_t *dat, uint16_t len)
{
	return HAL_SPI_Receive(&hspi1, dat, len, SPI_MAX_DELAY);
}

int spi_write_byte(uint8_t dat)
{
	return HAL_SPI_Transmit(&hspi1, &dat, 1, SPI_MAX_DELAY);
}

int spi_read_byte(uint8_t *dat)
{
	return HAL_SPI_Receive(&hspi1, dat, 1, SPI_MAX_DELAY);
}

/*****************************************************************/

//int xpt2406_write(uint16_t addr, uint8_t dat)
//{
//
//}

uint16_t xpt2406_read(uint8_t addr)
{
	uint16_t tmp = 0, data = 0;
	uint8_t *p = (uint8_t *)&tmp;

	// CS = 0, WHEN USE THIS, MUST SET PA4 AS GPIO_OUT, NOT SPI1_NSS
#ifdef CS_USER
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
#endif

	// Write cmd
	if (spi_write(&addr, 1) != HAL_OK) {
		pr_info("write cmd(0x%02hhx) failed", addr);
	}


	//发送一个时钟周期清除BUSY
	// CLK = 1
#ifdef BUSY_CLEAR_USER
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
#endif

	// delay_ms(1); // FIXME: can work without this

	// CLK = 0
#ifdef BUSY_CLEAR_USER
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
#endif

	// Read data
	if (spi_read(&p[0], 1) != HAL_OK) {
		pr_info("read addr(0x%02hhx) failed", addr);
	}

	if (spi_read(&p[1], 1) != HAL_OK) {
		pr_info("read addr(0x%02hhx) failed", addr);
	}

	pr_info("p[0]: p[1] = 0x %02x:%02x", p[0], p[1]);

	// 12bit, MSB
	data = p[0] << 4 | ((p[1] >> 4) & 0xf);

	// CS = 1
#ifdef CS_USER
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
#endif

	return data;
}

uint16_t xpt2406_read_ain0(void)
{
	return xpt2406_read(XPT2406_ADDR_AIN0);
}

uint16_t xpt2406_read_ain1(void)
{
	return xpt2406_read(XPT2406_ADDR_AIN1);
}

uint16_t xpt2406_read_ain2(void)
{
	return xpt2406_read(XPT2406_ADDR_AIN2);
}

uint16_t xpt2406_read_ain3(void)
{
	return xpt2406_read(XPT2406_ADDR_AIN3);
}

