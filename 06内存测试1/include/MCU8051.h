#ifndef _MCU_8051_H
#define _MCU_8051_H
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "color.h"
#define MEM_CODE_SIZE 65536
#define MEM_IRAM_SIZE 128
#define MEM_SFR_SIZE 128
#define MEM_XRAM_SIZE 65536
#define SFR_ACC 0xE0
typedef struct _memory_t
{
    uint8_t *code;               // 代码区 (用指针指向)
    uint8_t iram[MEM_IRAM_SIZE]; // 内部数据存储区区 128B
    uint8_t sfr[MEM_SFR_SIZE];   // 特殊功能寄存器区 128B
    uint8_t xram[MEM_XRAM_SIZE]; // 外部数据存储区区 64KB==65536B
} memory_t;

typedef struct _MCU_8051_t
{
    uint16_t pc; // 指向程序执行的地址(因为是64KB，即64*1024=2^16，即16位即可完全表示所有地址)
    memory_t mem;
} MCU_8051_t;

typedef struct _instr_t // 字节块的连续三个字节指令，第一个是操作指令，第二第三十操作指令。
{
    uint8_t opcode;
    uint8_t op0;
    uint8_t op1;
} instr_t;

typedef enum _mem_type_t//内存区域类型
{
    MEM_TYPE_CODE,
    MEM_TYPE_IRAM,
    MEM_TYPE_SFR,
    MEM_TYPE_XRAM,
    MEM_TYPE_BITS,
} mem_type_t;

void mcu_init();                      // CPU初始化
void mcu_reset();                     // CPU重置位
uint16_t mcu_pc();                    // 返回pc即当前指令的执行的地址
void mcu_load_bytes(uint8_t *code);   // 从指定地点读取数据
void mcu_fetch_instr(instr_t *instr); // 挨个读取字节块的指令
void mcu_exec_instr(instr_t *instr);  // 挨个执行读取到的指令
uint8_t mcu_read_addr(mem_type_t type,uint16_t addr/*地址是16位的,共有64KB*/);// 读某个地址的数据
void mcu_write_addr(mem_type_t type,uint16_t addr,uint8_t data);// 写某个地址的数据
#endif
