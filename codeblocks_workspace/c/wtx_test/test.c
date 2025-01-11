#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <windows.h>
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

#define FLAG_IDLE (0)
#define FLAG_CMD_OK (2)
#define FLAG_CMD_DATA_OK (3)

typedef struct
{
    int pos;
    int ch_cmd;
    int ch_data;
} Client_t;

static char handle_buf[128];
static Client_t client_arr[3];//客户数组

void showClientInfo()
{
    int arr_len = sizeof(client_arr)/sizeof(client_arr[0]);

    for (int i = 0; i <  arr_len; i++)
    {
        printf("%d ch_cmd: %d, ch_data: %d.\n",
               i,client_arr[i].ch_cmd,client_arr[i].ch_data);
    }
}

int getCmdValidSpace()
{
    int arr_len = sizeof(client_arr)/sizeof(client_arr[0]);

    for (int i = 0; i <  arr_len; i++)
    {
        if(client_arr[i].ch_cmd == 0)
        {
            return i;
        }
    }
    return -1;
}
int getDataValidSpace()
{
    int arr_len = sizeof(client_arr)/sizeof(client_arr[0]);

    for (int i = 0; i <  arr_len; i++)
    {
        if(client_arr[i].ch_cmd == 1 && client_arr[i].ch_data == 0)
        {
            return i;
        }
    }
    return -1;
}

void* waitCloseCmdWithIndex(void* args)
{
    Client_t* cli = (Client_t*)args;
    int pos = cli->pos;
    printf("start cmd %d_client.\n",pos);

    char tmp_buf[128]= {0};
    snprintf(tmp_buf,sizeof(tmp_buf),"close cmd %d",pos);
    while(1)
    {
        Sleep(200);

        if(strcmp(handle_buf,tmp_buf)==0)
        {
            break;
        }
    }

    memset(handle_buf,0,sizeof(handle_buf));

    printf("close cmd %d_client.\n",pos);
    cli->ch_cmd = 0;

    return NULL;
}
void* waitCloseDataWithIndex(void* args)
{
    Client_t* cli = (Client_t*)args;
    int pos = cli->pos;
    printf("start data %d_client.\n",pos);

    char tmp_buf[128]= {0};
    snprintf(tmp_buf,sizeof(tmp_buf),"close data %d",pos);
    while(1)
    {
        Sleep(200);

        if(cli->ch_cmd == 0)
        {//指令通道断了，数据通道跟着断
            break;
        }

        if(strcmp(handle_buf,tmp_buf)==0)
        {
            break;
        }
    }
    memset(handle_buf,0,sizeof(handle_buf));

    printf("close data %d_client.\n",pos);
    cli->ch_data = 0;

    return NULL;
}

void startHandleCmd()
{
    int index = getCmdValidSpace();
    if(index == -1)
    {
        printf("no space.\n");
        return;
    }
    client_arr[index].ch_cmd = 1;

    client_arr[index].pos = index;

    pthread_t pid;
    pthread_create(&pid,NULL,waitCloseCmdWithIndex,&client_arr[index]);
    if(pthread_detach(pid) < 0)
    {
        perror("pthread_detach");
    }
}

void startHandleData()
{
    int index = getDataValidSpace();
    if(index == -1)
    {
        printf("no space.\n");
        return;
    }
    client_arr[index].ch_data = 1;

    client_arr[index].pos = index;

    pthread_t pid;
    pthread_create(&pid,NULL,waitCloseDataWithIndex,&client_arr[index]);
    if(pthread_detach(pid) < 0)
    {
        perror("pthread_detach");
    }
}


void test()
{

    uint32_t w_pos = 0;
    char c = 0;
 char recv_buf[128];
    while(1)
    {
        printf("listening:\n");
        w_pos=0;
        memset(recv_buf,0,sizeof(recv_buf));

        while(((c=getchar()) != '\n') && w_pos < sizeof(recv_buf))
        {
            recv_buf[w_pos]=c;
            w_pos++;
        }

        recv_buf[w_pos] = '\0';
//printf("%s\n",recv_buf);


//接受指令
        if(strcmp(recv_buf,"ch_cmd") == 0)
        {
            printf("accept ch_cmd\n");
            startHandleCmd();
        }
        else if(strcmp(recv_buf,"ch_data") == 0)
        {
            printf("accept ch_data\n");
            startHandleData();
        }
        else if(strcmp(recv_buf,"show client") == 0)
        {
            showClientInfo();
        }
        else
        {
            strcpy(handle_buf,recv_buf);
            printf("unknow cmd: %s.\n",recv_buf);
        }
    }

}

