#ifndef _MCU8051_READ_h_
#define _MCU8051_READ_h_
#include "MCU8051.h"
static uint8_t mcu_read_code_64KB(uint16_t addr);
static uint8_t mcu_read_sfr_high_128B(uint8_t addr);
static uint8_t mcu_read_iram_low_128B(uint8_t addr);
static uint8_t mcu_read_bit(uint8_t addr);
static uint8_t mcu_read_xram_64KB(uint16_t addr);
uint8_t mcu_read_addr(mem_type_t type, uint16_t addr);
#endif