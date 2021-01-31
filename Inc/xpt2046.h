/*
 * ds1302.h
 *
 *  Created on: Jan 31, 2021
 *      Author: 16892
 */

#ifndef __XPT2046_H_
#define __XPT2046_H_

#include <stdint.h>

/* Command byte bit field
 *  S A2 A1 A0 MODE SED/~DFR PD1 PD0
 *  1 *  *  *   0      1      0   0
 *
 *  MODE 0 - 12bit, 1- 8bit
 *
 *  A2~A0[7:5] to select port
 */

#define XPT2406_ADDR_BS        (0x8C)

#define XPT2406_ADDR_XP        (XPT2406_ADDR_BS | (0x1 << 4)) // AIN0 - R
#define XPT2406_ADDR_YP        (XPT2406_ADDR_BS | (0x5 << 4)) // AIN1 - NTC1
//#define XPT2406_ADDR_XN
//#define XPT2406_ADDR_YN
#define XPT2406_ADDR_VBAT      (XPT2406_ADDR_BS | (0x2 << 4)) // AIN2 - GR1
#define XPT2406_ADDR_AUX       (XPT2406_ADDR_BS | (0x6 << 4)) // AIN3

#define XPT2406_ADDR_AIN0      XPT2406_ADDR_XP
#define XPT2406_ADDR_AIN1      XPT2406_ADDR_YP
#define XPT2406_ADDR_AIN2      XPT2406_ADDR_VBAT
#define XPT2406_ADDR_AIN3      XPT2406_ADDR_AUX

int spi_write_byte(uint8_t dat);
int spi_read_byte(uint8_t *dat);

#if 0
uint8_t xpt2406_read_ain0(void);
uint8_t xpt2406_read_ain1(void);
uint8_t xpt2406_read_ain2(void);
uint8_t xpt2406_read_ain3(void);
#else
uint16_t xpt2406_read_ain0(void);
uint16_t xpt2406_read_ain1(void);
uint16_t xpt2406_read_ain2(void);
uint16_t xpt2406_read_ain3(void);
#endif

#endif /* INC_DS1302_H_ */
