#include "../include/MCU8051_write.h"
extern MCU_8051_t mcu;

static void mcu_write_code_64KB(uint8_t addr, uint8_t data)
{
    printf("mcu_write_code: addr = 0x%x, data = 0x%x\n", addr, data);
    mcu.mem.code_64KB[addr] = data;
}

static void mcu_write_sfr_high_128B(uint8_t addr, uint8_t data)
{
    // 这里要进行sfr判断，因为里面有一些是已经使用的sfr，其余的才可以放进去！
    printf("mcu_write_sfr: addr = 0x%x, data = 0x%x\n", addr, data);
    switch (addr)
    {
    case 0x88:
        /* code_64KB */
        break;

    default:
        // 为什么要减去SFR_start？因为这是相对于SFR的相对地址，得到的是索引！不然会越界！
        addr -= SFR_START;
        if (addr < MEM_SFR_SIZE)
        {
            mcu.mem.sfr_high_128B[addr] = data;
        }
        else
        {
            printf(RED "mcu_write_sfr: addr = 0x%x, data = 0x%x\n" RESET, addr, data);
            printf(RED "mcu_write_sfr: addr out of range\n" RESET);
            return;
        }
        break;
    }
    mcu.mem.sfr_high_128B[addr] = data;
}

static void mcu_write_iram_low_128B(uint8_t addr, uint8_t data)
{
    printf("mcu_write_iram_SFR: addr = 0x%x, data = 0x%x\n", addr, data);
    mcu.mem.iram_low_128B[addr] = data;
}

static uint8_t mcu_write_bit(uint8_t addr, int bit)
{
    uint8_t bit_idx = addr % 8; // 找到哪一个bit
    bit &= 0x1;
    if (addr < SFR_START)
    {
        uint8_t byte_idx = addr / 8 + BIT_START; // 找到对应的字节
        mcu.mem.iram_low_128B[byte_idx] &= ~(1 << bit_idx);
        mcu.mem.iram_low_128B[byte_idx] |= bit ? (1 << bit_idx) : 0;
    }
    else
    {
        uint8_t byte_idx = (addr - SFR_START) / 8 * 8; // 找到对应的字节
        mcu.mem.sfr_high_128B[byte_idx] &= ~(1 << bit_idx);
        mcu.mem.sfr_high_128B[byte_idx] |= bit ? (1 << bit_idx) : 0;
    }
}

static void mcu_write_xram_64KB(uint16_t addr, uint8_t data)
{
    printf("mcu_write_xram: addr = 0x%x, data = 0x%x\n", addr, data);
    mcu.mem.xram_64KB[addr] = data;
}

void mcu_write_addr(mem_type_t type, uint16_t addr, uint8_t data)
{
    printf("mcu_write_addr: type = %s, addr = 0x%x, data = 0x%x\n", mem_type_to_str(type), addr, data);
    switch (type)
    {
    case MEM_TYPE_CODE:
        mcu_write_code_64KB((uint16_t)addr, data);
        break;
    case MEM_TYPE_SFR:
        mcu_write_sfr_high_128B((uint8_t)addr, data);
        break;
    case MEM_TYPE_IRAM:
        mcu_write_iram_low_128B((uint8_t)addr, data);
        break;
    case MEM_TYPE_BITS:
        mcu_write_bit((uint8_t)addr, data);
        break;
    case MEM_TYPE_XRAM:
        mcu_write_xram_64KB((uint16_t)addr, data);
        break;
    default:
        break;
    }
}