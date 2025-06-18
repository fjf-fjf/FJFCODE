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

#define MAX_IMAGES 20//最大图片数量


//全局变量区
////////////////////////////////////////////////////////////////////////////////////////////

int touch_x = 0;//触摸屏x坐标

int touch_y = 0;//触摸屏y坐标

struct input_event touch;//触摸屏事件

int number = 1;//当前图片编号

int have_photo=1;//是否有照片




// 函数声明区
////////////////////////////////////////////////////////////////////////////////////////////
/*******************************************************************************************
 *      @name   Bmp_Decode
 *      @brief  图片解码
 *      @note
 *      @param  lcd_mp  :.
 *      @param  bmp_path  :指的是图片的路径名称   
 * ****************************************************************************************/
bool Bmp_Decode(const char *bmp_path, unsigned int *lcd_mp) {
    FILE *bmp = fopen(bmp_path, "rb");
    if (!bmp) {
        //fprintf(stderr, "Failed to open %s: %s\n", bmp_path, strerror(errno));
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
 *      @brief  图片解码显示尺寸为480*800的图片尺寸
 *      @note
 *      @param  bmp_path  :指的是图片的路径名称   
 *      @param  lcd_mp  
 *      @return bool
 * ****************************************************************************************/
bool Bmp_Decode_800(const char *bmp_path, unsigned int *lcd_mp) {
    FILE *bmp = fopen(bmp_path, "rb");
    if (!bmp) {
        // fprintf(stderr, "Failed to open %s: %s\n", bmp_path, strerror(errno));
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
 *      @brief  图片解码显示尺寸为480*800的图片尺寸
 *      @note
 *      @param  touch_x  :触摸屏x坐标   
 *      @param  touch_y  :触摸屏y坐标   
 *      @param  ts_fd    :触摸屏设备文件描述符   
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







/*******************************************************************************************
 *      @name   display_image
 *      @brief  显示图片
 *      @note    显示图片到LCD屏幕上    
 *      @param  path  :图片路径名称   
 * ****************************************************************************************/
void display_image(const char *path) 
{
    if (!Bmp_Decode(path, lcd_mp)) 
    {
        Bmp_Decode_800("/tmp/5.bmp", lcd_mp);
        
    }
}
















// 主函数
int main(void) {
    // 打开设备
    open_device();

    char gif_path[256] = {0};
    snprintf(gif_path, sizeof(gif_path), "/tmp/bmp3/%d.bmp", number);
    Bmp_Decode_800("/tmp/5.bmp", lcd_mp);
    display_image(gif_path);

  
    
    while (1) 
    {
        get_touch_xy(&touch_x, &touch_y, ts_fd);

        // 下一张照片
        if (touch_x > 691 && touch_x < 800 && touch_y > 297 && touch_y < 396) {
            if (number < MAX_IMAGES) {
                snprintf(gif_path, sizeof(gif_path), "/tmp/bmp3/%d.bmp", ++number);
                display_image(gif_path);
            }
        }
        // 上一张照片
        else if (touch_x > 691 && touch_x < 800 && touch_y > 167 && touch_y < 270) {
            if (number > 1) {
                snprintf(gif_path, sizeof(gif_path), "/tmp/bmp3/%d.bmp", --number);
                display_image(gif_path);
            }
        }
        // 返回主菜单
        else if (touch_x > 691 && touch_x < 800 && touch_y > 0 && touch_y < 128) {
            close_device();
            system("./q4");
            break; // 退出循环
        }
    }

    return 0;
}
