#ifndef _HEX_H_
#define _HEX_H_
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdint.h>
#define FILEPATH "../src/instructions.HEX"
typedef enum _data_type_t
{
    HEX_TYPE_DATA,
    HEX_TYPE_EOF,
}data_type_t;

uint8_t *hex_parser(const char* filePath);

#endif