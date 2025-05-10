#include <stdio.h>
#include "add/add.h"

int main()
{
    int ret = add_int(1,2);
    printf("ret = %d.\n",ret);

    return 0;
}