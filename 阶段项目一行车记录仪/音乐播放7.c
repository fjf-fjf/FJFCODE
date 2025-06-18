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

#define LCD_DEV     "/dev/fb0"
#define MMAP_SIZE   (800 * 480 * 4)
#define TS_DEV      "/dev/input/event0"
#define MAX_IMAGES 20

int touch_x = 0;
int touch_y = 0;
struct input_event touch;

int number = 2;
int have_photo=1;
int video=10;

// BMP 解码
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

// BMP 解码
bool Bmp_Decode_800(const char *bmp_path, unsigned int *lcd_mp) {
    FILE *bmp = fopen(bmp_path, "rb");
    if (!bmp) {
        fprintf(stderr, "Failed to open %s: %s\n", bmp_path, strerror(errno));
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

// 获取触摸坐标
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
 * @name    Music
 * @param   None
 * @return  None
 *******************************************************************************************/
int main()
{
    
    open_device();

    int m;
    Bmp_Decode_800("/tmp/14.bmp",lcd_mp);               //显示网QQ音乐图片
    sleep(2);

    //点击播放
    
    
    
    m=system("madplay /tmp/jay.mp3 -a -10 &"); // 后台播放
    if(m==0)
    {
        printf("播放成功\n");
    }
    Open_Bmp("001.bmp",lcd_mp);                 //显示音乐图片
    for(;;)
    {
        Get_Touch_Xy();
        if (touch_x> 307 && touch_x < 370 && touch_y > 360 && touch_y < 430) // 点了暂停位置
        {
            system("killall -19 madplay"); // 暂停
            printf("暂停播放\n");
        }
        if (touch_x > 25 && touch_x < 90 && touch_y > 362 && touch_y < 430) // 点了继续位置
        {
            system("killall -18 madplay"); // 恢复
            printf("继续播放\n");
        }
        if (touch_x > 240 && touch_x < 305 && touch_y > 360 && touch_y < 435)// 点了下一首位置
        {
            system("killall -9 madplay"); // 停止
            m=system("madplay /tmp/iku.mp3 -a -10 &"); // 后台播放
            if(m==0)
            {
                printf("播放成功\n");
            }
            Open_Bmp("002.bmp",lcd_mp);
        }
        if (touch_x > 95 && touch_x < 160 && touch_y > 360 && touch_y < 430)// 点了上一首位置
        {
            system("killall -9 madplay"); // 停止
            m=system("madplay /tmp/jay.mp3 -a -10 &"); // 后台播放
            if(m==0)
            {
                printf("播放成功\n");
            }
            Open_Bmp("002.bmp",lcd_mp);           //显示音乐图片
        }
        if(touch_x>700&&touch_y<100)
        {
            system("killall -9 madplay"); // 停止
            break;
        }


    }
}