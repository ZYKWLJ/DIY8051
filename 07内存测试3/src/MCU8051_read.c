#include "../include/MCU8051_read.h"
extern MCU_8051_t mcu;

static uint8_t mcu_read_code_64KB(uint16_t addr)
{
    printf("mcu_read_code: addr = 0x%x\n", addr);
    return mcu.mem.code_64KB[addr];
}

static uint8_t mcu_read_sfr_high_128B(uint8_t addr)
{
    if (addr > SFR_START) // 为什么要减去SFR_start？因为这是相对于SFR的相对地址，得到的是索引！不然会越界！
    {
        addr -= SFR_START;
    }
    switch (addr)
    {
        // 为什么要减去SFR_start？因为这是相对于SFR的相对地址，得到的是索引！不然会越界！
    default:
        return (addr < MEM_SFR_SIZE) ? mcu.mem.sfr_high_128B[addr] : 0;
    }
    return 0;
}

static uint8_t mcu_read_iram_low_128B(uint8_t addr)
{
    printf("mcu_read_iram: addr = 0x%x\n", addr);
    return mcu.mem.iram_low_128B[addr];
}

static uint8_t mcu_read_bit(uint8_t addr)
{
    uint8_t bit_idx = addr % 8; // 找到哪一个bit
    if (addr < SFR_START)
    {
        uint8_t byte_idx = addr / 8 + BIT_START; // 找到对应的字节
        return mcu.mem.iram_low_128B[byte_idx] & (1 << bit_idx) ? 1 : 0;
    }
    else
    {
        uint8_t byte_idx = (addr - SFR_START) / 8 * 8; // 找到对应的字节
        return mcu.mem.sfr_high_128B[byte_idx] & (1 << bit_idx) ? 1 : 0;
    }
}

static uint8_t mcu_read_xram_64KB(uint16_t addr)
{
    printf("mcu_read_xram: addr = 0x%x\n", addr);
    return mcu.mem.xram_64KB[addr];
}

uint8_t mcu_read_addr(mem_type_t type, uint16_t addr)
{
    printf("mcu_read_addr: type = %s, addr = 0x%x\n", mem_type_to_str(type), addr);
    switch (type)
    {
    case MEM_TYPE_CODE:
        return mcu_read_code_64KB((uint16_t)addr);
    case MEM_TYPE_SFR:
        return mcu_read_sfr_high_128B((uint8_t)addr);
    case MEM_TYPE_IRAM:
        return mcu_read_iram_low_128B((uint8_t)addr);
    case MEM_TYPE_BITS:
        return mcu_read_bit((uint8_t)addr);
    case MEM_TYPE_XRAM:
        return mcu_read_xram_64KB((uint16_t)addr);
    default:
        return 0;
    }
}
