#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdint.h>
#include <io.h>

/**< codeblocks 默认使用 gdb 8.1
使用官方的gdb 8.3.1替换
 */

#if 0


void test()
{
    const char* str = "hello world!.\n";
    int str_len = strlen(str);
    write(1,str,str_len);
}


typedef struct pos
{
    int x,y;
    uint8_t name[10];
} pos_t;
void test()
{
    pos_t a = {1,2,{0}};
    for (int i = 0; i < 10 ; i++)
    {
        a.name[i]=i;
    }

    printf("a.x : %d, a.y : %d.\n",a.x,a.y);

}
#endif // 0

void test()
{

}

