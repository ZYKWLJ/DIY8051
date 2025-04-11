#include "../include/main.h"
static uint8_t t0_nop_code[]={0x00,0x00,0x80,0xFE}; 
void test_instr()
{
    printf("instructions test......[Start]\n");	
    uint16_t pc;
    mcu_reset();
    mcu_load(t0_nop_code);
    do{
    	instr_t instr;
    	
    	pc=mcu_pc();
    	mcu_fetch_instr(&instr);
    	mcu_exec_instr(&instr);
	}while(pc!=mcu_pc());
    printf("instructions test......[End]\n");
}
int main()
{
	test_instr();
    return 0;
}