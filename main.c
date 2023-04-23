#include"project.h"





//申请资源
int Pro_Init()
{
    GL.lcd=open(LCD_DEV_PATH,O_RDWR);

    if(GL.lcd==-1)
    {
        printf("打开LCD失败\n");
        return -1;
    }
    GL.ts =open(TOUCH_LCD_DEV_PATH,O_RDONLY);

    if (GL.ts==-1)
    {
        printf("打开触摸屏失败!");
        return -1;
    }
    GL.mmap_p=mmap(NULL,800*480*4,PROT_READ|PROT_WRITE,
    MAP_SHARED,GL.lcd,0);

    if(GL.mmap_p == MAP_FAILED)
    {
        printf("映射失败\n");
        return -1;
    }

    Show_Photo("/IOT/bg2.bmp");
    

    //判断管道存在与否,若没有则创建后打开
    if (access(FIFO_PATH,F_OK))
    {

        umask(0000);
        mkfifo(FIFO_PATH,0777);
    }

    //打开

    GL.fifo_fd=open(FIFO_PATH,O_RDWR);

    if (GL.fifo_fd==-1)
    {
        printf("failed!\n");

        return -1;
    }
    return 0;

}

//释放资源
int Pro_Free()
{
    close(GL.lcd);
    close(GL.ts);
    close(GL.fifo_fd);

    munmap(GL.mmap_p,800*480*4);
    

    return 0;

}

//传输管道文件
int Send_Cmd(char * cmd)
{


    write(GL.fifo_fd,cmd,strlen(cmd));


    return 0;
}





int Get_Touch_X_Y()

{

    read(GL.ts,&GL.touch,sizeof(GL.touch));

    if (GL.touch.type==EV_ABS&&GL.touch.code==ABS_X)GL.touch_x=GL.touch.value*800/1024;
    if (GL.touch.type==EV_ABS&&GL.touch.code==ABS_Y)GL.touch_y=GL.touch.value*480/600;



    return 0;



}





//展示图片
int Show_Photo(char *photo_path)
{

    int bmp=open(photo_path,O_RDONLY);

    if(bmp==-1)
    {
        printf("打开图片失败\n");
        return -1;
    }

    int bmp_w,bmp_h;

    
    
    lseek(bmp,18,SEEK_SET);
    read(bmp,&bmp_w,4);
    read(bmp,&bmp_h,4);

    int * new_p = GL.mmap_p + 800*(240-bmp_h/2)+(400-bmp_w/2);

    char rgb[bmp_w*bmp_h*3];
    lseek(bmp,54,SEEK_SET);
    read(bmp,rgb,bmp_w*bmp_h*3);



    if(strcmp(photo_path,"/IOT/game.bmp")==0)
    {
        lseek(bmp,54,SEEK_SET);
        read(bmp,GL.game_bmp,bmp_w*bmp_h*3);
    }

    for(int y=0,n=0; y<480; y++)
    {
        for(int x=0; x<800; x++,n+=3)
        {
            *(new_p+ 800*(479-y)+x) = rgb[n] << 0 | rgb[n+1] <<8 | rgb[n+2] <<16;
        }
    }

    close(bmp);


    return 0;

}

int Main_Ui_Touch_Ctrl()
{


    Show_Photo("/IOT/bg2.bmp");



    while (1)
    {
        /* code */
        Get_Touch_X_Y();

        if (GL.touch.type==EV_KEY&&GL.touch.code==BTN_TOUCH&&GL.touch.value==0)
        {
            //音乐播放器

            if (GL.touch_x>226&&GL.touch_x<373&&GL.touch_y>277&&GL.touch_y<400)
            Music_Player();
        }
        if (GL.touch.type==EV_KEY&&GL.touch.code==BTN_TOUCH&&GL.touch.value==0)
        {
            //视频播放器

            if (GL.touch_x>46&&GL.touch_x<170&&GL.touch_y>277&&GL.touch_y<400)
            Video_Player();
        }
        if (GL.touch.type==EV_KEY&&GL.touch.code==BTN_TOUCH&&GL.touch.value==0)
        {
            //游戏

            if (GL.touch_x>588&&GL.touch_x<720&&GL.touch_y>277&&GL.touch_y<400)
            Game();
        }
        if (GL.touch.type==EV_KEY&&GL.touch.code==BTN_TOUCH&&GL.touch.value==0)
        {
            //退出

            if (GL.touch_x>691&&GL.touch_x<784&&GL.touch_y>3&&GL.touch_y<100)
            End();
        }


    }

    return 0;
    
}




//主函数
int main()
{
    Pro_Init();

    Main_Ui_Touch_Ctrl();

    Pro_Free();

    return 0;
    
}