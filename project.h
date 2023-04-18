#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

#define LCD_DEV_PATH "/dev/fb0"
#define TOUCH_LCD_DEV_PATH "/dev/input/event0"


struct shared_inf
{
    int lcd;
    int ts;
    int *mmap_p;
    int touch_x;
    int touch_y;
    struct input_event touch;
}SI;


/*函数的声明*/
/*****main.c ****/
int Pro_Init();   //申请资源 
int Pro_Free();   //释放资源
int Get_Touch_X_Y();
int Main_Ui_Touch_Ctrl();
int Show_Photo(char * photo_path);

/***music.c****/
int Music_Player();
int Music_Touch_Ctrl();


/****video.v*****/
int Video_Player();
int Video_Touch_Ctrl();

/****game.c*****/
int Game();
int Game_Touch_Ctrl();