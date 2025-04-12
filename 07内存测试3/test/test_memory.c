#include "../include/test_memory.h"


// 打印数据数组
void print_data_array(uint8_t data[], int size) {
    printf("this is data array's data:\n");
    for (int i = 0; i < size; i++) {
        printf("data[%zu]=0x%x\n", i, data[i]);
    }
}

// 打印字节数据（每8位组合成1字节）
void print_byte_array(uint8_t bits[], int bit_count) {
    printf("Byte data (grouped by 8 bits):\n");
    int byte_count = bit_count / 8;  // 计算完整字节数
    for (int i = 0; i < byte_count; i++) {
        uint8_t byte = 0;
        // 组合8个位成1字节（LSB first）
        for (int j = 0; j < 8; j++) {
            byte |= (bits[i * 8 + j] << j);
        }
        printf("byte[%d] = 0x%02X\n", i, byte);
    }
}

// 测试位寻址区
void test_bit_addressing_area() {
    uint8_t data[MEM_IRAM_SIZE];
    printf("\n\nTest the bit addressing area:\n");
    for (int i = 0; i < MEM_IRAM_SIZE; i++) {
        mcu_write_addr(MEM_TYPE_BITS, i, 1);
    }
    printf("\n\n");
    for (int i = 0; i < MEM_IRAM_SIZE; i++) {
        data[i] = mcu_read_addr(MEM_TYPE_BITS, i);
    }
    printf("\n\n");
    print_data_array(data, MEM_IRAM_SIZE);
    print_byte_array(data, MEM_IRAM_SIZE);
}

// 测试特殊功能寄存器区
void test_sfr_addressing_area() {
    uint8_t data[MEM_SFR_SIZE];
    printf("\n\nTest the SFR addressing area:\n");
    for (int i = 0; i < MEM_SFR_SIZE; i++) {
        mcu_write_addr(MEM_TYPE_SFR, i, 1);
    }
    printf("\n\n");

    for (int i = 0; i < MEM_SFR_SIZE; i++) {
        data[i] = mcu_read_addr(MEM_TYPE_SFR, i);
    }
    printf("\n\n");
    print_data_array(data, MEM_SFR_SIZE);
}

// 测试内部程序存储器
void test_iram_addressing_area() {
    uint8_t data[MEM_IRAM_SIZE];
    printf("\n\nTest the IRAM addressing area:\n");
    for (int i = 0; i < MEM_IRAM_SIZE; i++) {
        mcu_write_addr(MEM_TYPE_IRAM, i, 1);
    }
    printf("\n\n");

    for (int i = 0; i < MEM_IRAM_SIZE; i++) {
        data[i] = mcu_read_addr(MEM_TYPE_IRAM, i);
    }
    printf("\n\n");
    print_data_array(data, MEM_IRAM_SIZE);
}

// 测试外部程序存储器
void test_xram_addressing_area() {
    uint8_t data[MEM_XRAM_SIZE];
    printf("\n\nTest the XRAM addressing area:\n");
    for (int i = 0; i < MEM_XRAM_SIZE; i++) {
        mcu_write_addr(MEM_TYPE_XRAM, i, 1);
    }
    printf("\n\n");

    for (int i = 0; i < MEM_XRAM_SIZE; i++) {
        data[i] = mcu_read_addr(MEM_TYPE_XRAM, i);
    }
    printf("\n\n");
    print_data_array(data, MEM_XRAM_SIZE);
}

// 测试 SFR_ACC
void test_sfr_acc() {
    printf("\n\nTest the SFR_ACC:\n");
    mcu_write_addr(MEM_TYPE_SFR, SFR_ACC, 1);
    uint8_t ret = mcu_read_addr(MEM_TYPE_SFR, SFR_ACC);
    printf("sfr_acc = %d\n", ret);
}


// 主测试函数
void test_memory() {
    test_bit_addressing_area();
    // test_sfr_addressing_area();
    // test_iram_addressing_area();
    // test_xram_addressing_area();
    // test_sfr_acc();
    // 由于之前的测试函数中数据数组是局部的，这里无法直接打印
    // 可以考虑将数据存储在全局数组或者通过参数传递的方式处理
    // 这里简单示例，不实际打印数据
    // uint8_t data[MEM_XRAM_SIZE];
    // print_data_array(data, MEM_XRAM_SIZE);
}   