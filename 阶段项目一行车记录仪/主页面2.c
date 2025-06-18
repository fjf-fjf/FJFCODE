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
#define LCD_DEV     "/dev/fb0" // LCD设备文件的路径

#define MMAP_SIZE   800*480*4  // 映射内存的大小

#define GIF_NUM     72         // GIF图片的数量

#define TS_DEV      "/dev/input/event0"  // 触摸屏设备文件的路径


//全局变量区
////////////////////////////////////////////////////////////////////////////////////////////
int touch_x = 0;  // 触摸屏的x轴坐标

int touch_y = 0;  // 触摸屏的y轴坐标

struct input_event touch;  // 触摸屏事件结构体

int exit_threads1 = 0; // 退出线程1的标志位

// 互斥锁和条件变量
pthread_mutex_t touch_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t touch_cond = PTHREAD_COND_INITIALIZER;



//函数声明区
////////////////////////////////////////////////////////////////////////////////////////////
/*******************************************************************************************
 *      @name   touch_screen_thread
 *      @brief  定义一个线程函数来处理触摸屏事件
 *      @note   none
 *      @param  void *arg  :.
 * ****************************************************************************************/
void *touch_screen_thread(void *arg) 
{
    int ts_fd = *(int *)arg; // 获取触摸屏设备文件描述符

    struct input_event touch;
    while (1) {
        read(ts_fd, &touch, sizeof(touch)); // 读取触摸屏事件

        if (touch.type == EV_ABS && touch.code == ABS_X) {
            pthread_mutex_lock(&touch_mutex); // 加互斥锁
            touch_x = touch.value; // 获取x轴坐标
            pthread_mutex_unlock(&touch_mutex); // 解锁
        }

        if (touch.type == EV_ABS && touch.code == ABS_Y) {
            pthread_mutex_lock(&touch_mutex); // 加互斥锁
            touch_y = touch.value; // 获取y轴坐标
            pthread_mutex_unlock(&touch_mutex); // 解锁
        }

        if (touch.type == EV_KEY && touch.code == BTN_TOUCH && touch.value == 0) {
            // 触摸屏松开事件，可以在这里处理触摸屏的操作
            pthread_mutex_lock(&touch_mutex); // 加互斥锁
            printf("Touch screen released at (%d, %d)\n", touch_x, touch_y);
            pthread_cond_signal(&touch_cond); // 通知主函数坐标已经更新
            pthread_mutex_unlock(&touch_mutex); // 解锁
        }
    }

    return NULL;
}




/*******************************************************************************************
 *      @name   show_time
 *      @brief  实现一个线程函数来显示实时时间
 *      @note   none
 *      @param    unsigned int *lcd_mp  : LCD映射内存的指针
 *      @param    int lcd_fd          : LCD设备文件描述符
 *      @param    int ts_fd           : 触摸屏设备文件描述符
 *      @param    pthread_t thread   : 线程ID
 * ****************************************************************************************/
// 显示时间
void show_time(unsigned int *lcd_mp, int lcd_fd,int ts_fd,pthread_t thread)
{
    while (!exit_threads1) {
        for (;;) {
            char timebuf[128] = {0};
            // 获取系统时间并转化为格式化字符串
            time_t tm = time(NULL);
            struct tm *ptm = localtime(&tm);
            sprintf(timebuf, "%02d/%02d/%02d  %02d:%02d:%02d\n",
                    ptm->tm_year + 1900,  // 年份
                    ptm->tm_mon + 1,      // 月份
                    ptm->tm_mday,         // 日子
                    ptm->tm_hour,         // 小时
                    ptm->tm_min,          // 分钟
                    ptm->tm_sec           // 秒钟
            );

            // 打开TTF格式的字库文件并申请输出框内存，加载字体内容到输出框，把输出框加载到LCD的指定位置
            font *pft = fontLoad("/usr/share/fonts/DroidSansFallback.ttf");         // 打开字库
            fontSetSize(pft, 31);                                                    // 字体大小
            bitmap *bm = createBitmapWithInit(225, 30, 4, getColor(0, 46, 22, 27));   // 申请缓存
            fontPrint(pft, bm, 0, 0, timebuf, getColor(0, 255, 255, 255), 250);     // 加载字体
            show_font_to_lcd(lcd_mp, 0, 0, bm);                                        // 刷新缓存
            destroyBitmap(bm);

            // 检查触摸坐标是否在指定区域内
            pthread_mutex_lock(&touch_mutex); // 加互斥锁
            if ((touch_x > 258) && (touch_x < 489) && (touch_y > 41) && (touch_y < 224)) {
                
                 close_device(); // 关闭设备文件
                 system("./q3"); // 跳进函数
            }
            if ((touch_x > 258) && (touch_x < 489) && (touch_y > 252) && (touch_y < 439)) {
                
                 close_device(); // 关闭设备文件
                 system("./q4"); // 跳进查看历史记录函数
            }
            


            pthread_mutex_unlock(&touch_mutex); // 解锁

            // 延时1s
            sleep(1);
        }
    }
}



/*******************************************************************************************
 *      @name   Bmp_Decode
 *      @brief  实现一个函数来解码BMP图片并显示到LCD     // 显示主页面图片
 *      @note   none
 *      @param    const char *bmp_path : BMP图片的路径
 *      @param    unsigned int *lcd_mp  : LCD映射内存的指针
 *      @return   bool                : 成功返回true，失败返回false
 * ******************************************************************************************/
bool Bmp_Decode(const char *bmp_path, unsigned int *lcd_mp) 
{
    // 打开BMP图像，以二进制只读的方式打开 "rb"
    FILE *bmp_fp = fopen(bmp_path, "rb");

    if (NULL == bmp_fp) {
        fprintf(stderr, "fopen [%s] error,errno=%d,%s\n", bmp_path, errno, strerror(errno));
        return false;
    }

    // 由于不需要读取图像的属性信息，所以把文件的位置指示器进行设置，向后偏移54字节
    fseek(bmp_fp, 54, SEEK_SET);

    // 循环从BMP图像中读取一行数据并转化为ARGB格式，写入到LCD对应的像素点
    char bufline[800 * 3] = {0}; // 用于存储一行像素点的颜色分量
    unsigned int buf[MMAP_SIZE] = {0};  // 定义一个全部变量用于辅助线覆盖图片上方

    for (size_t y = 0; y < 480; y++) {
        // 读取BMP图像的一行数据
        fread(bufline, 800 * 3, 1, bmp_fp);

        // BMP图片的像素点是24bit色深，所以应该把bufline中存储的颜色分量以3个字节为一组,循环处理
        for (size_t x = 0; x < 800; x++) {
            int data = 0; // 用于存储转换之后的像素点

            // BMP是小端存储，所以3个字节的颜色分量的顺序是BGR,需要转换为LCD像素点的存储格式ARGB
            data |= bufline[3 * x + 0];     // B 蓝色分量
            data |= bufline[3 * x + 1] << 8;  // G 绿色分量
            data |= bufline[3 * x + 2] << 16; // R 红色分量

            // 把转换之后的像素点的颜色分量写入到LCD的映射内存，从下向上，从左向右的顺序
            *(buf + (800 * (479 - y)) + x) = data;
        }
    }

    memcpy(lcd_mp, buf, MMAP_SIZE); // 将一起映射的内存存入lcd_mp中
    fclose(bmp_fp);

    return true;
}



/*******************************************************************************************
 *      @name   open_file_all
 *      @brief  实现一个函数来打开所有的硬件文件
 *      @note   none
 *      @param    none
 *      @return   none
 * ***************************************************************************************/
void open_file_all()
{
    // 打开LCD
    int lcd_fd = open(LCD_DEV, O_RDWR);

    if (-1 == lcd_fd) {
        fprintf(stderr, "open lcd error,errno=%d,%s\n", errno, strerror(errno));
        exit(-1);
    }

    // 进行内存映射，为了提高LCD的刷新效率
    unsigned int *lcd_mp = (unsigned int *)mmap(
            NULL,
            MMAP_SIZE,
            PROT_READ | PROT_WRITE,
            MAP_SHARED,
            lcd_fd,
            0
    );

    // 错误处理
    if (NULL == lcd_mp) {
        fprintf(stderr, "mmap error,errno=%d,%s\n", errno, strerror(errno));
        exit(-1);
    }

    // 打开触摸屏
    int ts_fd = open(TS_DEV, O_RDWR);

    // 错误处理
    if (-1 == ts_fd) {
        fprintf(stderr, "open touch screen error,errno = %d,%s\n", errno, strerror(errno));
        exit(-1);
    }
}









//主函数区
int main() 
{

    open_device(); // 打开设备文件

    // 打开图片并且申请映射，显示图片出来
    Bmp_Decode("/tmp/1.bmp", lcd_mp); // 显示主页面图片

    // 创建触摸屏线程
    pthread_t thread;
    pthread_create(&thread, NULL, touch_screen_thread, &ts_fd);

    show_time(lcd_mp,lcd_fd,ts_fd,pthread_self()); // 显示时间

    // 清理资源
    pthread_join(thread, NULL);
    close(lcd_fd);
    close(ts_fd);
    munmap(lcd_mp, MMAP_SIZE);

    return 0;
}
