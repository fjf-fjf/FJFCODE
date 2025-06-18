#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <linux/input.h>
#include "font.h"
#include <time.h>
#include <pthread.h>
#include "device.h"



//宏定义区
////////////////////////////////////////////////////////////////////////////////////////////

#define LCD_DEV     "/dev/fb0"//LCD设备文件

#define MMAP_SIZE   (800 * 480 * 4)//映射的大小

#define TS_DEV      "/dev/input/event0"//触摸屏设备文件

#define MAX_IMAGES 20//最大录像数



//宏定义区
////////////////////////////////////////////////////////////////////////////////////////////
int touch_x = 0;//触摸屏x坐标

int touch_y = 0;//触摸屏y坐标

struct input_event touch;//触摸屏事件

int number = 2;//录像数

int have_photo=1;//是否有照片

int video=10;//视频播放速度



/*******************************************************************************************
 *      @name   Bmp_Decode_800
 *      @brief  图片解码显示尺寸为480*800的图片尺寸
 *      @note
 *      @param  bmp_path  :指的是图片的路径名称   
 *      @param  lcd_mp  
 *      @return bool
 * ****************************************************************************************/
bool Bmp_Decode(const char *bmp_path, unsigned int *lcd_mp) {
    FILE *bmp = fopen(bmp_path, "rb");
    if (!bmp) {
        // fprintf(stderr, "Failed to open %s: %s\n", bmp_path, strerror(errno));
        return false;
    }

    // 跳过 BMP 文件头
    fseek(bmp, 54, SEEK_SET);

    char buf_line[640 * 3]; // 每行颜色分量
    for (int y = 0; y < 480; y++) {
        fread(buf_line, sizeof(buf_line), 1, bmp);
        for (int x = 0; x < 640; x++) {
            *(lcd_mp + (480 - y - 1) * 800 + x) = buf_line[3 * x] |
                (buf_line[3 * x + 1] << 8) |
                (buf_line[3 * x + 2] << 16);
        }
    }

    fclose(bmp);
    return true;
}








/*******************************************************************************************
 *      @name   Bmp_Decode_800
 *      @brief  图片解码显示尺寸为800*480的图片尺寸 
 *      @note
 *      @param  bmp_path  :指的是图片的路径名称   
 *      @param  lcd_mp  
 * ****************************************************************************************/
bool Bmp_Decode_800(const char *bmp_path, unsigned int *lcd_mp) {
    FILE *bmp = fopen(bmp_path, "rb");
    if (!bmp) {
        //fprintf(stderr, "Failed to open %s: %s\n", bmp_path, strerror(errno));
        return false;
    }

    // 跳过 BMP 文件头
    fseek(bmp, 54, SEEK_SET);

    char buf_line[800 * 3]; // 每行颜色分量
    for (int y = 0; y < 480; y++) {
        fread(buf_line, sizeof(buf_line), 1, bmp);
        for (int x = 0; x < 800; x++) {
            *(lcd_mp + (480 - y - 1) * 800 + x) = buf_line[3 * x] |
                (buf_line[3 * x + 1] << 8) |
                (buf_line[3 * x + 2] << 16);
        }
    }

    fclose(bmp);
    return true;
}





/*******************************************************************************************
 *      @name   get_touch_xy
 *      @brief  获取触摸屏的坐标    
 *      @note
 *      @param  touch_x  : 触摸屏的x坐标
 *      @param  touch_y  : 触摸屏的y坐标
 *      @param  ts_fd    : 触摸屏设备文件描述符
 * ****************************************************************************************/
void get_touch_xy(int *touch_x, int *touch_y, int ts_fd) 
{
    while (1) 
    {
        read(ts_fd, &touch, sizeof(touch));
        if (touch.type == EV_ABS) 
        {
            if (touch.code == ABS_X) 
            {
                *touch_x = touch.value;
            } else if (touch.code == ABS_Y) 
            {
                *touch_y = touch.value;
            }
        }
        if (touch.type == EV_KEY && touch.code == BTN_TOUCH && touch.value == 0) 
        {
            printf("Touched at: (%d, %d)\n", *touch_x, *touch_y);
            break;
        }
    }
}











// 主函数
int main(void) {
    // 打开设备
    open_device();


	 // 显示查看录像和循环录像页面
    Bmp_Decode_800("/tmp/12.bmp", lcd_mp);
  
    while (1) 
    {
        get_touch_xy(&touch_x, &touch_y, ts_fd);

        // 显示查看录像
        if (touch_x > 143 && touch_x < 249 && touch_y > 263 && touch_y < 340) 
		{
					//判断几个录像
                if (Bmp_Decode("/tmp/bmp4/2.bmp",lcd_mp)==false)
                {
                   Bmp_Decode_800("/tmp/13.bmp", lcd_mp);
                }
                    
				if(Bmp_Decode("/tmp/bmp4/2.bmp",lcd_mp))
				{
					Bmp_Decode_800("7.bmp", lcd_mp);

                    if(Bmp_Decode("/tmp/bmp5/2.bmp",lcd_mp))
                        {
                            Bmp_Decode_800("8.bmp", lcd_mp);

                                if(Bmp_Decode("/tmp/bmp6/2.bmp",lcd_mp))
                                {
                                    Bmp_Decode_800("9.bmp", lcd_mp);

                                        if(Bmp_Decode("/tmp/bmp7/2.bmp",lcd_mp))
                                        {
                                        Bmp_Decode_800("10.bmp", lcd_mp);

                                        
                                            if(Bmp_Decode("/tmp/bmp8/2.bmp",lcd_mp))
                                            {
                                                Bmp_Decode_800("11.bmp", lcd_mp);
                                            }
                                        }
                                }
                        }

				}
				
				
				

		
          
        }
        // 点击视频1
         if (touch_x>42 && touch_x<121 && touch_y>93&& touch_y<220) 
		 {
            char gif_path[30] ={0}; //用于存储转换好的图像路径

					//3.在LCD显示开机动画,用户需要自己修改路径
					for (int  i = 0; i < 100; i++)
					{
						sprintf(gif_path,"/tmp/bmp4/%d.bmp",i);  //构造名称
					
						bool ret = Bmp_Decode(gif_path,lcd_mp);                 //图像显示
						usleep(10*1000); 
					
													//FPS=50HZ
					}

                    
         if (touch_x>726 && touch_x<800 && touch_y>386&& touch_y<480) 
		 {
			  Bmp_Decode_800("11.bmp", lcd_mp);
            
         }

         }

		 // 点击视频2
         if (touch_x>176 && touch_x<253 && touch_y>93&& touch_y<220) 
		 {
            char gif_path[30] ={0}; //用于存储转换好的图像路径

					//3.在LCD显示开机动画,用户需要自己修改路径
					for (int  i = 0; i < 100; i++)
					{
						sprintf(gif_path,"/tmp/bmp5/%d.bmp",i);  //构造名称
					
						Bmp_Decode(gif_path,lcd_mp);                 //图像显示
						usleep(10*1000); 
					
													//FPS=50HZ
					}
         }

		 // 点击视频3
         if (touch_x>310 && touch_x<384 && touch_y>93&& touch_y<220) 
		 {
            char gif_path[30] ={0}; //用于存储转换好的图像路径

					//3.在LCD显示开机动画,用户需要自己修改路径
					for (int  i = 0; i < 100; i++)
					{
						sprintf(gif_path,"/tmp/bmp6/%d.bmp",i);  //构造名称
					
						Bmp_Decode(gif_path,lcd_mp);                 //图像显示
						usleep(10*1000); 
					
													//FPS=50HZ
					}
         }


		  // 点击视频4
         if (touch_x>447 && touch_x<523 && touch_y>93&& touch_y<220) 
		 {
            char gif_path[30] ={0}; //用于存储转换好的图像路径

					//3.在LCD显示开机动画,用户需要自己修改路径
					for (int  i = 0; i < 500; i++)
					{
						sprintf(gif_path,"/tmp/bmp7/%d.bmp",i);  //构造名称
					
						Bmp_Decode(gif_path,lcd_mp);                 //图像显示
						usleep(10*1000); 
					
													//FPS=50HZ
					}
         }


	

         // 点击循环视频
         if (touch_x>500 && touch_x< 611&& touch_y>263&& touch_y<320) 
		 {
            char gif_path[30] ={0}; //用于存储转换好的图像路径

					//3.在LCD显示开机动画,用户需要自己修改路径
					for (int  i = 0; i < 100; i++)
					{
						sprintf(gif_path,"/tmp/bmp9/%d.bmp",i);  //构造名称
					
						Bmp_Decode(gif_path,lcd_mp);                 //图像显示
						usleep(10*1000); 
					
													//FPS=50HZ
					}
         }

		  // 点击家按钮
         if (touch_x>726 && touch_x<800 && touch_y>0&& touch_y<96) 
		 {
			
            system("./q4"); // 返回界面
         }

         if (touch_x>726 && touch_x<800 && touch_y>386&& touch_y<480) 
		 {
			  Bmp_Decode_800("/tmp/12.bmp", lcd_mp);
            
         }


		 
  
    }

    return 0;
}