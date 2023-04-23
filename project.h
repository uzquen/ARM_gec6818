/*库函数声明*/
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/mman.h>
#include<linux/input.h>
#include<pthread.h>
#include<string.h>
#include<stdlib.h>


#define LCD_DEV_PATH "/dev/fb0"
#define TOUCH_LCD_DEV_PATH "/dev/input/event0"
#define FIFO_PATH  "/tmp/my_fifo"



/*全局变量声明*/
struct shared_inf
{
    int lcd;
    int ts;
    int fifo_fd;
    int *mmap_p;
    int touch_x;
    int touch_y;
    struct input_event touch;
    int GV; //0：输   1：没输
    int S_S;//  0:暂停  1：继续
    int RESTART;// 0：不要重新开始  1：重新开始
    char game_bmp[800*480*3];
}GL;



/*  函数的声明*/
int Pro_Init();
int Pro_Free();
int Get_Touch_X_Y();
int Main_Ui_Touch_Ctrl();
int Show_Photo(char *photo_path);
int Send_Cmd(char *cmd);



int Video_Player();

int Music_Player();
/*    game    */
int Game();
int Draw_Plate();
void * Move_Ball(void * arg);
void * Touch_Ctrl_Plate(void * arg);

int End();
