#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <io.h>
#include <dirent.h>
#include <direct.h>

#if 0

typedef struct student
{
    /* data */
    int x, y;
    uint8_t name[10];
} student_t;

void test()
{
    student_t wtx = {1, 2, {0}};
    for (size_t i = 0; i < 10; i++)
    {
        wtx.name[i] = i;
    }

    printf("wtx.x = %d, wtx.y = %d.\n", wtx.x, wtx.y);
}
#endif



void test()
{

    char * cur_path = getcwd(NULL,0);
    if(cur_path == NULL)
    {
        perror("Error _getcwd\n");
    }
    printf("buf: %s\n",cur_path);
}

