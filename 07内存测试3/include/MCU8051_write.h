#ifndef _MCU8051_WRITE_h_
#define _MCU8051_WRITE_h_
#include "MCU8051.h"
static void mcu_write_code_64KB(uint8_t addr, uint8_t data);
static void mcu_write_sfr_high_128B(uint8_t addr, uint8_t data);
static void mcu_write_iram_low_128B(uint8_t addr, uint8_t data);
static uint8_t mcu_write_bit(uint8_t addr, int bit);
static void mcu_write_xram_64KB(uint16_t addr, uint8_t data);

void mcu_write_addr(mem_type_t type, uint16_t addr, uint8_t data);
#endif