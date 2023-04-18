#include "project.h"

int Pro_Init()
{
    SI.lcd = open(LCD_DEV_PATH,O_RDWR);
    if(SI.lcd == -1)
    {
        printf("打开 LCD 失败！\n");
        return -1;
    }

    SI.ts = open(TOUCH_LCD_DEV_PATH,O_RDONLY);
    if(SI.ts == -1)
    {
        printf("打开 触摸屏 失败!\n");
        return -1;
    }

    SI.mmap_p = mmap(NULL,800*480*4,PROT_READ|PROT_WRITE,MAP_SHARED,SI.lcd,0);//内存映射函数 
    if(SI.mmap_p == MAP_FAILED)
    {
        printf("映射失败!\n");
        return -1;
    }

   
    return 0;
}


int Pro_Free()
{

    close(SI.lcd);
    close(SI.ts);

    munmap(SI.mmap_p,800*480*4);

    return 0;
}


int Get_Touch_X_Y()
{

    
    read(SI.ts,&SI.touch,sizeof(SI.touch));

    if(SI.touch.type == EV_ABS && SI.touch.code == ABS_X)  SI.touch_x = SI.touch.value * 800 / 1024;
    if(SI.touch.type == EV_ABS && SI.touch.code == ABS_Y)  SI.touch_y = SI.touch.value * 480 / 600;

    return 0;
}


int Show_Photo(char * photo_path)
{

    int bmp = open(photo_path,O_RDONLY);
    if(bmp == -1)
    {
        printf("打开 图片 。。。\n");
        return -1;
    }

    char rgb[800*480*3];
    lseek(bmp,54,SEEK_SET);
    read(bmp,rgb,800*480*3);

    for(int y=0,n=0; y<480; y++)
    {
        for(int x=0; x<800; x++,n+=3)
        {
            *(SI.mmap_p+ 800*(479-y)+x) = rgb[n] << 0 | rgb[n+1] <<8 | rgb[n+2] <<16;
        }
    }


    close(bmp);

    return 0;
}


int Main_Ui_Touch_Ctrl()
{
    Show_Photo("/ui_photo/main.bmp");


    while(1)
    {
        Get_Touch_X_Y();

        if(SI.touch.type == EV_KEY && SI.touch.code == BTN_TOUCH && SI.touch.value == 0)
        {

            if(SI.touch_x>232 && SI.touch_x<350 && SI.touch_y>300  && SI.touch_y<400)  //音乐
            {
                //printf("启动音乐！\n");
                Music_Player();
            }

            if(SI.touch_x>672 && SI.touch_x<792 && SI.touch_y>300  && SI.touch_y<400)  //视频
            {
                //printf("启动视频！\n");
                Video_Player();
            }

            if(SI.touch_x>450 && SI.touch_x<569 && SI.touch_y>300  && SI.touch_y<400) //游戏
            {
                printf("启动游戏！\n");
                Game();
            }

            if(SI.touch_x>338 && SI.touch_x<441 && SI.touch_y>181  && SI.touch_y<279) //退出
            {
                printf("退出！\n");
            }
        }

    }

    return 0;
}

int main()
{
    Pro_Init();

    
    Main_Ui_Touch_Ctrl();
    

    Pro_Free();

    return 0;
}