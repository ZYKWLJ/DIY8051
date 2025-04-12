#include "../include/MCU8051.h"
MCU_8051_t mcu;
const char *mem_type_to_str(mem_type_t type)
{
    switch (type)
    {
    case MEM_TYPE_CODE:
        return "CODE";
        break;
    case MEM_TYPE_IRAM:
        return "IRAM";
        break;
    case MEM_TYPE_SFR:
        return "SFR";
        break;
    case MEM_TYPE_XRAM:
        return "XRAM";
        break;
    case MEM_TYPE_BITS:
        return "BITS";
        break;
    default:
        return "UNKNOWN";
        break;
    }
}

void mcu_reset()
{
    printf("CPU reset.....[Start]\n");
    mcu.pc = 0;
    printf("CPU reset.....[Done]\n");
}
void mcu_init()
{
    printf("CPU initialition.....[Start]\n");
    mcu.mem.code_64KB = (uint8_t *)0;
    memset(mcu.mem.iram_low_128B, 0, MEM_IRAM_SIZE);
    memset(mcu.mem.sfr_high_128B, 0, MEM_SFR_SIZE);
    memset(mcu.mem.xram_64KB, 0, MEM_XRAM_SIZE);
    mcu_reset();
    printf("CPU initialition.....[Done]\n");
}

uint16_t mcu_pc()
{
    printf("get CPU's PC value......[%d]\n", mcu.pc);
    return mcu.pc;
}
void mcu_load_bytes(uint8_t *code_64KB)
{
    mcu.mem.code_64KB = code_64KB;
}
void mcu_fetch_instr(instr_t *instr)
{ // 为了简便期间，统一取出3字节，实际有些指令只有1、2个字节，但是问题不大。
    instr->opcode = mcu.mem.code_64KB[mcu.pc];
    instr->op0 = mcu.mem.code_64KB[mcu.pc + 1];
    instr->op1 = mcu.mem.code_64KB[mcu.pc + 2];
}

// 以二进制形式打印整数的函数
// 将整数转换为 8 位二进制字符串
char *print_binary(int num)
{
    static char ret[9]; // 多一个字符用于存储字符串结束符 '\0'
    ret[8] = '\0';
    for (int i = 7; i >= 0; i--)
    {
        ret[7 - i] = ((num >> i) & 1) + '0';
    }
    return ret;
}

// 打印指令信息，以二进制形式输出
void print_instr(instr_t *instr)
{
    printf(GREEN);
    printf("Full instructions:\n");
    printf("%s\t", print_binary(instr->opcode));
    printf("%s\t", print_binary(instr->op0));
    printf("%s", print_binary(instr->op1));
    printf(RESET);
    printf("\n");
}

void mcu_exec_instr(instr_t *instr)
{
    // 首先解析nop、sjmp指令
    printf("\n\nstart execute instruction......\n");
    print_instr(instr);
    switch (instr->opcode)
    {
        // 解析nop指令
    case 0x00:
        /* code_64KB */
        printf("PC: instruciton\tassemble\n");
        printf(GREEN "%d: [%s] %s\n" RESET, mcu.pc, print_binary(instr->opcode), "nop");
        mcu.pc++;
        break;
        // 解析sjmp指令(将op0设置为0xFE即-2，使得在原地跳转，完成循环功能)
    case 0x80:
        /* code_64KB */
        printf("PC: instruciton\tassemble\n");
        printf(GREEN "%d: [%s] %s\n" RESET, mcu.pc, print_binary(instr->opcode), "sjmp");
        mcu.pc += 2 + (int8_t)instr->op0; // 这里的是个有符号数的跳转，所以要加上符号位灵活跳转
        break;
    default:
        printf("PC: instruciton\tassemble\n");
        printf(RED "%d: [%s] %s\n" RESET, mcu.pc, print_binary(instr->opcode), "no matching instruction available");
        break;
    }
}
