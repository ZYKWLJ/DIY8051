#include "../include/test_instr.h"
extern const char*files[50];
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