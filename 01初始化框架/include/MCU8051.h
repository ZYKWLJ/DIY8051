#ifndef _MCU_8051_H
#define _MCU_8051_H
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#define  MEM_CODE_SIZE 65536
#define  MEM_IRAM_SIZE 128
#define  MEM_SFR_SIZE 128
#define  MEM_XRAM_SIZE 65536

typedef struct _memory_t{
	uint8_t* code;//代码区 (用指针指向)
	uint8_t iram[MEM_IRAM_SIZE];//内部数据存储区区 128B
	uint8_t sfr[MEM_SFR_SIZE];//特殊功能寄存器区 128B
	uint8_t xram[MEM_XRAM_SIZE];//外部数据存储区区 64KB==65536B
}memory_t;

typedef struct _MCU_8051_t{
	uint16_t pc;//指向程序执行的地址(因为是64KB，即64*1024=2^16，即16位即可完全表示所有地址) 
	memory_t mem;
} MCU_8051_t;

void mcu_init(); 
void mcu_reset(); 
#endif