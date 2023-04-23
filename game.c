#include "project.h"


void * Move_Ball(void * arg)
{
    int x0=400;
    int y0=240;
    int r = 50;

    int x_mask = 0;
    int y_mask = 0; // 0:-- 1:++
    while(1)
    {

        for(int y=y0-r; y<=y0+r; y++)
        {
            for(int x=x0-r; x<=x0+r; x++)
            {
                if((x-x0) * (x-x0) + (y-y0) * (y-y0) < r*r)
                {
                    //⚪的里面
                    *(GL.mmap_p + (800*y+x)) = 0x00fff00;
                }
                else
                {
                    //⚪的外面
                      *(GL.mmap_p + (800*y+x)) = GL.game_bmp[3*(800*(479-y)+x)] << 0 | GL.game_bmp[(3*(800*(479-y)+x))+1] << 8| GL.game_bmp[(3*(800*(479-y)+x))+2] << 16;
                }
            }
        }

        while (1)
        {
           if(GL.S_S == 1 || GL.RESTART == 1) break;
        }
        
        if(GL.RESTART == 1)
        {
            x0 = 400;
            y0 = 240;
            Show_Photo("/IOT/game.bmp");

            x_mask = 0;
            y_mask = 0;

            GL.RESTART = 0;

        }


        if((y0 +r == 399) && (x0 > GL.touch_x-80 && x0<GL.touch_x+80)) y_mask = 0;

        
        if(x0 + r == 799) x_mask = 0; //是否撞到右边
        if(y0 + r > 410)
        {
            //输了
            GL.GV = 1;
            Show_Photo("/IOT/gameover.bmp");
            break;
        }

        if(y0 - r == 0)  y_mask = 1;//是否撞到上面

        if(x0 - r == 0)  x_mask = 1;//是否撞到左边

        if(y_mask == 1) y0++;
        if(y_mask == 0) y0--;
        if(x_mask == 1) x0++;
        if(x_mask == 0) x0--;

        usleep(3000);//延时3千微妙
    }

    return 0;
}

int Draw_Plate()
{
    int plate_w = 100;
    int plate_h = 30;

    for(int y=400; y<430; y++)
    {
        for(int x=0; x<800; x++)
        {

            if(x>GL.touch_x-50 && x<GL.touch_x+50)
            {
                *(GL.mmap_p + 800*y+x) = 0x000f0f;
            }
            else
            {
                *(GL.mmap_p + 800*y+x) = 0x0000ff;
            }
            
        }
    }

    return 0;
}

void * Touch_Ctrl_Plate(void * arg)
{
    while(1)
    {
        Get_Touch_X_Y();

        if(GL.touch_y > 400)
        {   
            Draw_Plate();
        }

        if(GL.touch.type == EV_KEY && GL.touch.code == BTN_TOUCH && GL.touch.value == 0)
        {
            if(GL.touch_x>700&&GL.touch_x<780&&GL.touch_y>43&&GL.touch_y<167)//开始暂停
            
            {   
                printf("接触1");
                if (GL.S_S==0)
                {
                    GL.S_S=1;
                }
                else
                {
                    GL.S_S=0;
                }
            }
            if(GL.touch_x>700&&GL.touch_x<780&&GL.touch_y>238&&GL.touch_y<306)//重新开始
            {
                printf("接触2");
                GL.RESTART=1;
            }

            if(GL.touch_x>700&&GL.touch_x<780&&GL.touch_y>360&&GL.touch_y<450)//退出
            {
                printf("接触3");
                GL.GV=1;
                break;
            }
        }

    }

    return 0;
}

int Game()
{
    printf("启动游戏！\n");

    Show_Photo("/IOT/game.bmp");

    GL.GV     = 0;
    GL.S_S    = 0;
    GL.RESTART = 0;

    pthread_t ball_pid , plate_pid;

    //在这里创建两条线程

    pthread_create(&ball_pid,NULL,Move_Ball,NULL);
    pthread_create(&plate_pid,NULL,Touch_Ctrl_Plate,NULL);
    

    while(1)
    {
        if(GL.GV == 1)
        {
            //取消两条线程
            pthread_cancel(ball_pid);
            pthread_cancel(plate_pid);


            Show_Photo("/IOT/gameover.bmp");

            sleep(1);
            Show_Photo("/IOT/bg2.bmp");
           
            break;
        }
    }
    
    return 0;
}