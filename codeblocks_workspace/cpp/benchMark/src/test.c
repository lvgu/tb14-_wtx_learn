#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <io.h>


int factorial(int n)
{
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}
#if 0


#endif // 0


/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
void test()
{
    const char* str = "hello world!.\n";
    int str_len = strlen(str);
    write(1,str,str_len);
    int i = 0;
    int a = 0;

    /**< 100000 152us
    1000000 723us
     */
    for(; i<1000000; i++)
    {
        a++;
    }
    printf("%s ok.\n",__FUNCTION__);
}


