#include "project.h"

int Music_Touch_Ctrl()
{
    //显示音乐界面
    Show_Photo("/ui_photo/video.bmp");
    while(1)
    {
        Get_Touch_X_Y();

        if(SI.touch.type == EV_KEY && SI.touch.code == BTN_TOUCH && SI.touch.value == 0)
        {
            if(SI.touch_x > 0 && SI.touch_x<250 && SI.touch_y>0 && SI.touch_y<240)
            {
                printf("播放音乐!\n");
            }

            
            if(SI.touch_x > 250 && SI.touch_x<550 && SI.touch_y>0 && SI.touch_y<240)
            {
                printf("暂停音乐!\n");
            }

            
            if(SI.touch_x > 0 && SI.touch_x<250 && SI.touch_y>240 && SI.touch_y<480)
            {
                printf("停止播放!\n");
            }

            
            if(SI.touch_x > 250 && SI.touch_x<550 && SI.touch_y>240 && SI.touch_y<480)
            {
                printf("继续音乐!\n");
            }

            
            if(SI.touch_x > 550 && SI.touch_x<800)
            {
                printf("退出音乐播放器!\n");
                Show_Photo("/ui_photo/main.bmp");
                break;
            }
        }
    }


    return 0;
}


int Video_Player()
{
    printf("启动视频播放器！\n");
    return 0;
}