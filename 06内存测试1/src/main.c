#include "../include/main.h"
static const char *files[] = {
    "../src/instructions.HEX",
};
void test_instr()
{
    for (int i = 0; i < sizeof(files) / sizeof(const char *); i++)
    {
        printf("file: %s\n", files[i]);
        printf("instructions test......[Start]\n");
        uint16_t pc;
        uint8_t *code;

        code = hex_parser(files[i]);

        mcu_reset();
        mcu_load_bytes(code);
        do
        {
            instr_t instr;
            pc = mcu_pc();
            mcu_fetch_instr(&instr);
            mcu_exec_instr(&instr);
        } while (pc != mcu_pc()); // 如果是原地跳转，测试就结束了！
        printf(RED "instructions test......[End]\n" RESET);
    }
}

// 测试内存的4个区域！
void test_memory()
{
    uint8_t data[MEM_XRAM_SIZE];
    printf("\n\nTest the bit addressing area:\n");
    // 区域1：位寻址区
    for (int i = 0; i < MEM_IRAM_SIZE; i++)
    { // 测试写位寻址区，128B
        mcu_write_addr(MEM_TYPE_BITS, i, 1);
    }
    for (int i = 0; i < MEM_IRAM_SIZE; i++)
    { // 测试读位寻址区，128B
        data[i] = mcu_read_addr(MEM_TYPE_BITS, i);
    }
    printf("\n\nTest the SFR addressing area:\n");

    // 区域2：特殊功能寄存器区
    for (int i = 0; i < MEM_SFR_SIZE; i++)
    { // 测试写SFR区，128位
        mcu_write_addr(MEM_TYPE_SFR, i, 1);
    }
    for (int i = 0; i < MEM_SFR_SIZE; i++)
    { // 测试读SFR区，128位
        data[i] = mcu_read_addr(MEM_TYPE_SFR, i);
    }
    printf("\n\nTest the IRAM addressing area::\n");

    // 区域3：内部程序存储器
    for (int i = 0; i < MEM_IRAM_SIZE; i++)
    { // 测试写iram区，256位
        mcu_write_addr(MEM_TYPE_IRAM, i, 1);
    }

    for (int i = 0; i < MEM_IRAM_SIZE; i++)
    { // 测试读iram区，256位
        data[i] = mcu_read_addr(MEM_TYPE_IRAM, i);
    }
    printf("\n\nTest the XRAM addressing area:\n");

    // 区域4：外部程序存储器
    for (int i = 0; i < MEM_XRAM_SIZE; i++)
    { // 测试写xram区，65536位
        mcu_write_addr(MEM_TYPE_XRAM, i, 1);
    }

    for (int i = 0; i < MEM_XRAM_SIZE; i++)
    { // 测试读xram区，65536位
        data[i] = mcu_read_addr(MEM_TYPE_XRAM, i);
    }
    printf("\n\nTest the SFR_ACC:\n");

    mcu_write_addr(MEM_TYPE_SFR, SFR_ACC, 1);
    uint8_t ret = mcu_read_addr(MEM_TYPE_SFR, SFR_ACC);
    printf("sfr_acc = %d\n", ret);
}
int main()
{
    // test_instr();
    test_memory();
    return 0;
}