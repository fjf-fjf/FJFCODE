#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/videodev2.h>
#include <pthread.h>
#include <linux/input.h>
#include <stdbool.h>
#include "device.h"


#define LCD_DEV     "/dev/fb0"

#define MMAP_SIZE   800*480*4

#define GIF_NUM     72

//用于记录摄像头的设备文件的文件描述符




//触摸屏设备文件的路径
#define  TS_DEV   "/dev/input/event0"


//触摸屏设备文件的路径
#define  TS_DEV   "/dev/input/event0"







//开启设备
void open_device()
{
            lcd_fd = open(LCD_DEV,O_RDWR);

                if(-1 == lcd_fd)
                {
                    perror("open lcd device failed");
                    exit(-1);
                }

                //进行内存映射，为了提高LCD的刷新效率
    lcd_mp = (unsigned int *)mmap(
                                                    NULL, 
                                                    MMAP_SIZE,
                                                    PROT_READ|PROT_WRITE    ,
                                                    MAP_SHARED,
                                                    lcd_fd,
                                                    0
                                                );
    //错误处理
    if( NULL == lcd_mp)
    {
        perror("mmap failed");
        exit(-1);
    }

      //打开触摸屏，linux系统下把硬件设备抽象为文件，所以可以访问硬件设备的设备文件
     ts_fd = open(TS_DEV,O_RDWR);
    

    //错误处理
    if(-1 == ts_fd)
    {
        fprintf(stderr,"open touch screen error,errno = %d,%s\n",errno,strerror(errno));
    }



}


//关闭设备
void close_device()
{
        //关闭LCD设备文件
        close(lcd_fd);
        //关闭LCD内存映射
        munmap(lcd_mp,MMAP_SIZE);
        //关闭触摸屏设备文件
        close(ts_fd);

}





