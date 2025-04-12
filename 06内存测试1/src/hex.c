#include "../include/hex.h"
static int hex_read(uint8_t *ptr, int width)
{
    // 为 str 分配足够的内存空间，宽度 + 1 用于存储字符串结束符
    char *str = (char *)malloc((width + 1) * sizeof(char));
    if (str == NULL)
    {
        // 内存分配失败，输出错误信息并返回 -1
        perror("Memory allocation failed");
        return -1;
    }
    // 复制字符串
    strncpy(str, (char *)ptr, width);
    // 手动添加字符串结束符
    str[width] = '\0';
    int res = 0;
    for (int i = 0; i < width; i++)
    {
        uint8_t c = ptr[i];
        printf("the char is %c\n", c);
        // 0x30FF
        if (c >= '0' && c <= '9')
        {
            res = (res << 4) | (c - '0');
        }
        else if (c >= 'A' && c <= 'F')
        {
            res = (res << 4) | (c - 'A' + 10);
        }
        else if (c >= 'a' && c <= 'f')
        {
            res = (res << 4) | (c - 'a' + 10);
        }
        else
        {
            printf("[hex-read]------invalid hex file!\n");
            return -1;
        }
    }
    printf("read hex datas: width:%d  instructions:%s  value:%d\n", width, str, res);
    free(str);
    return res;
}

uint8_t *hex_parser(const char *filePath)
{
    printf("this is hex_parser\n");
    FILE *fp = NULL;
    fp = fopen(filePath, "r");
    if (fp == NULL)
    {
        printf("open file failed!\n");
        return NULL;
    }
    uint8_t *code = (uint8_t *)malloc(MEM_CODE_SIZE * sizeof(uint8_t)); // 64KB的代码空间
    if (code == NULL)
    {
        printf("malloc failed!\n");
        return NULL;
    }
    uint8_t *line_buf = (uint8_t *)malloc(MEM_CODE_SIZE * sizeof(uint8_t)); // 256B的一行的空间
    if (line_buf == NULL)
    {
        printf("malloc failed!\n");
        return NULL;
    }
    int line = 0;
    while (fgets(line_buf, MEM_CODE_SIZE, fp)) // 这里开始逐行解析了
    {

        printf("\n\nanaylize line %d hex data %s\n", ++line, line_buf);
        uint8_t *ptr = line_buf;
        if (*ptr++ != ':')
        {
            printf("[hex-:]------invalid hex file!\n");
            fclose(fp);
            return NULL;
        }

        uint8_t data_len = hex_read(ptr, 2); // 2个字符的数据长度，即1字节
        ptr += 2;
        printf("data_len:%d\n", data_len);
        uint16_t addr = hex_read(ptr, 4); // 4个字符的起始地址，即两字节
        ptr += 4;
        printf("addr:%d\n", addr);
        uint8_t type = hex_read(ptr, 2); // 2个字符的数据类型，即1字节
        printf("type:%d\n", type);
        ptr += 2;
        switch (type) // 根据数据类型进行判断！
        {
        case HEX_TYPE_EOF:
            printf("File EOF!\n");
            fclose(fp);
            return code;
        case HEX_TYPE_DATA:
            printf("this is data\n");
            int originAddr = addr;
            for (uint8_t i = 0; i < data_len; i++, ptr += 2)
            {
                code[addr++] = hex_read(ptr, 2); // 一次读取两字符
            }
            printf("this full data in hex: ");
            for (int i = originAddr; i < data_len; i++)
            {
                printf("%02X ", code[i]); // %02X 打印两位十六进制
            }
            printf("\n");
            break;
        default:
            printf("[hex-type]------invalid hex file!\n");
            fclose(fp);
            break;
        }
    }
    fclose(fp);
    free(line_buf);
    return code;
}

// 测试功能
// int main(){
//     uint8_t *code="30FF";
//     printf("%d\n",hex_read(code,4));
//     return 0;
// }
