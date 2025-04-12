#include "../include/main.h"
void test_instr()
{
    printf("instructions test......[Start]\n");	
    uint16_t pc;
    uint8_t *code;
    code=hex_parser(FILEPATH);
    mcu_reset();
    mcu_load_bytes(code);
    do{
    	instr_t instr;
    	pc=mcu_pc();
    	mcu_fetch_instr(&instr);
    	mcu_exec_instr(&instr);
	}while(pc!=mcu_pc());//如果是原地跳转，测试就结束了！
    printf(RED"instructions test......[End]\n"RESET);
}
int main()
{
	test_instr();
    return 0;
}