#include"project.h"

// int Music_Touch_Ctrl()
// {
// }


int Video_Player()
{
    printf("欢迎启动视频播放器\n");
    

//显示音乐图片
    Show_Photo("/IOT/video.bmp");


    while (1)
    {
        Get_Touch_X_Y();

        if(GL.touch.type==EV_KEY && GL.touch.code==BTN_TOUCH && GL.touch.value==0)
        {


        
             //音量+
            if (GL.touch_x>1&&GL.touch_x<106&&GL.touch_y>413&&GL.touch_y<480)
            {
                printf("音量加!\n");
                Send_Cmd("volume +10\n");
            }
            
            

                //音量-
            if (GL.touch_x>121&&GL.touch_x<224&&GL.touch_y>413&&GL.touch_y<480)
            {
                printf("音量减!\n");
                Send_Cmd("volume -10\n");
            }
            


                //快进
            if (GL.touch_x>238&&GL.touch_x<338&&GL.touch_y>413&&GL.touch_y<480)
            {
                printf("快进!\n");
                Send_Cmd("seek +10\n");
            }
            

        
                //播放
            if (GL.touch_x>355&&GL.touch_x<455&&GL.touch_y>413&&GL.touch_y<480)
            {
                printf("播放\n");
                //后台播放使用且能用触摸屏
                system("mplayer -slave -input file=/tmp/my_fifo -zoom -x 800 -y 400 Faded3.avi&");
                
            }
                
            
            
                //暂停
            if (GL.touch_x>473&&GL.touch_x<573&&GL.touch_y>413&&GL.touch_y<480)
            {
                printf("暂停!\n");
                Send_Cmd("pause\n");
            }
            
            
            
                //继续
            if (GL.touch_x>592&&GL.touch_x<692&&GL.touch_y>413&&GL.touch_y<480)
            {
                printf("继续!\n");
                Send_Cmd("pause\n");
            }
            
            
            
                //退出
            if (GL.touch_x>710&&GL.touch_x<792&&GL.touch_y>413&&GL.touch_y<480)
            {
                printf("退出!\n");
                system("killall -9 mplayer");
                //返回主界面
                Show_Photo("/IOT/bg2.bmp");
                break;
            }

        }    
    }

    return 0;
}