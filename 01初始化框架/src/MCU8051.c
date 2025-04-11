#include"../include/MCU8051.h"
static MCU_8051_t mcu;
void mcu_reset(){
	printf("CPU重置位.....[Start]\n");
	mcu.pc==0;
	printf("CPU重置位.....[Done]\n");
}
void mcu_init(){
	printf("CPU初始化.....[Start]\n");
	mcu.mem.code=(uint8_t*)0;
	memset(mcu.mem.iram,0,MEM_IRAM_SIZE);
	memset(mcu.mem.sfr,0,MEM_SFR_SIZE);
	memset(mcu.mem.xram,0,MEM_XRAM_SIZE);
	mcu_reset();
	printf("CPU初始化.....[Done]\n");
}