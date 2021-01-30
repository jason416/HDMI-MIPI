/*
 * 24c02.h
 *
 *  Created on: Jan 30, 2021
 *      Author: 16892
 */

#ifndef __24C02_H_
#define __24C02_H_


#define AT24C02_A0           0
#define AT24C02_A1           0
#define AT24C02_A2           0

/*
 * Last bit at LSB is R/W field, W - 0, R - 1
 */

#define AT24C02_ADDR_WR  (0xA0 | (AT24C02_A0 << 1) | (AT24C02_A1 << 2) | (AT24C02_A2 << 3))
#define AT24C02_ADDR_RD  (0xA1 | (AT24C02_A0 << 1) | (AT24C02_A1 << 2) | (AT24C02_A2 << 3))


int at24c02_write(uint16_t addr, uint8_t *buf, uint32_t size);

int at24c02_read(uint16_t addr, uint8_t *buf, uint32_t size);

int at24c02_write_byte(uint16_t addr, uint8_t data);

int at24c02_read_byte(uint16_t addr, uint8_t *data);

#endif /* INC_24C02_H_ */
