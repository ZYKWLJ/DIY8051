#include "../include/MCU8051.h"
#include "MCU8051.h"
static MCU_8051_t mcu;
void mcu_reset()
{
    printf("CPU reset.....[Start]\n");
    mcu.pc = 0;
    printf("CPU reset.....[Done]\n");
}
void mcu_init()
{
    printf("CPU initialition.....[Start]\n");
    mcu.mem.code = (uint8_t *)0;
    memset(mcu.mem.iram, 0, MEM_IRAM_SIZE);
    memset(mcu.mem.sfr, 0, MEM_SFR_SIZE);
    memset(mcu.mem.xram, 0, MEM_XRAM_SIZE);
    mcu_reset();
    printf("CPU initialition.....[Done]\n");
}
