#include "../include/MCU8051.h"
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

uint16_t mcu_pc()
{
    printf("get CPU's PC value......[%X]\n", mcu.pc);
    return mcu.pc;
}
void mcu_load_bytes(uint8_t *code)
{
    mcu.mem.code = code;
}
void mcu_fetch_instr(instr_t *instr)
{ // 为了简便期间，统一取出3字节，实际有些指令只有1、2个字节，但是问题不大。
    instr->opcode = mcu.mem.code[mcu.pc];
    instr->op0 = mcu.mem.code[mcu.pc + 1];
    instr->op1 = mcu.mem.code[mcu.pc + 2];
}
void mcu_exec_instr(instr_t *instr)
{
    printf("start execute instruction......\n");
}