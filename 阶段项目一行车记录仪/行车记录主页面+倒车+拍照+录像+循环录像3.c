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


//宏定义区
////////////////////////////////////////////////////////////////////////////////////////////
#define  LCD_DEV   "/dev/fb0" //LCD设备文件路径

#define  LCD_MAPSIZE   800*480*4 //LCD映射内存大小

#define WIDTH 640    //定义图片的大小

#define HEIGHT 480   //定义摄像头的大小

#define CAMERA_PATH  "/dev/video7" //定义摄像头设备文件路径

#define  TS_DEV   "/dev/input/event0" //定义触摸屏设备文件路径

// 转换一个像素点 YUV --> RGB
#define YUV_OFFSET 16
#define UVC_OFFSET 128


//全局变量区
////////////////////////////////////////////////////////////////////////////////////////////////
int camera_fd = -1;  //定义摄像头设备文件描述符

unsigned int n_buffers= 0; //用于记录缓冲区的编号

int touch_x=0; //定义触摸屏的x坐标

int touch_y=0;  //定义触摸屏的y坐标

struct input_event touch; //定义触摸屏的输入事件

int DAO_CHE=1;//定义一个数字用来判断是否点到倒车线

int photo=1;//定义一个数字用来判断是否拍照

int photo_num=1; //定义一个数字用来记录拍照的张数

int video=1;//定义一个数字用来判断是否点到录像

int video_num=0;//定义一个数字用来判断是否点到拍照

int video_num_1=0;//定义一个数字用来记录录像的视频数1
int video_num_2=0;//定义一个数字用来记录录像的视频数2 
int video_num_3=0;//定义一个数字用来记录录像的视频数3
int video_num_4=0;//定义一个数字用来记录录像的视频数4
int video_num_5=0;//定义一个数字用来记录录像的视频数5

int video_circle=1;//定义一个数字用来判断是否点到循环录像

int video_num_circle=0;//定义一个数字用来记录循环拍照

int close_1=1;//定义一个数字用来判断是否点到关闭按钮

int close_video=0;//定义一个数字用来判断是否点到关闭视频按钮

unsigned int * rgbbuf;//定义一个指针变量来指向映射的内存

int  exit_threads1=0;//退出线程1的标志位

//结构体定义区
////////////////////////////////////////////////////////////////////////////////////////////////
struct buffer 
{
        void * start;   //申请的缓冲区的地址
        size_t length;  //申请的缓冲求的大小
};

extern struct buffer *buffers; //用于记录申请的缓冲区信息

struct buffer *buffers = NULL; //用于记录申请的缓冲区信息



//函数声明区
////////////////////////////////////////////////////////////////////////////////////////////////
/*******************************************************************************************
 *      @name   setGlobalVariable
 *      @brief  将循环录像的视频定义在1--200中，循环录像的视频数值从1开始，每循环一次，视频数值加1
 *      @note
 *      @param  无
 *      @return 0：成功，-1：失败
 *      @retval
 * *****************************************************************************************/
void setGlobalVariable()
{
    video_num_circle = (video_num_circle + 1) % 201; // 取模运算，如果a等于200，则a等于1，否则a加1
}




/*******************************************************************************************
 *      @name   open_camera
 *      @brief  打开摄像头设备文件
 *      @note
 *      @param  无
 *      @return 0：成功，-1：失败
 *      @retval
 * *****************************************************************************************/
void close_camera(void)
{
    if (camera_fd != -1) {
        for (unsigned int i = 0; i < n_buffers; ++i) {
            if (munmap(buffers[i].start, buffers[i].length) == -1) {
                //fprintf(stderr, "munmap error, errno=%d, %s\n", errno, strerror(errno));
            }
        }
        free(buffers);
        buffers = NULL;
        if (ioctl(camera_fd, VIDIOC_STREAMOFF, &camera_fd) == -1) {
            //fprintf(stderr, "ioctl STREAMOFF error, errno=%d, %s\n", errno, strerror(errno));
        }
        if (close(camera_fd) == -1) {
            //fprintf(stderr, "close camera_fd error, errno=%d, %s\n", errno, strerror(errno));
        }
        camera_fd = -1;
    }
}


 
 
/*******************************************************************************************
 *      @name   car_line
 *      @brief  显示倒车线
 *      @note
 *      @param  rgbbuf  :这个参数是将倒车辅助线闪烁原因，所改进的参数，可以将线不会闪烁，提前将线存入参数中
 *                       最后一起映射到lcd上       
 * ****************************************************************************************/
void  car_line(unsigned int * rgbbuf)
{
//左横线
    {
    int x,y;
    int z=0;

     for(int y=0;y<=240;y++)
    {
        
        for(x=z;x<20+z;x++)
        {
            if (y>=0 && y<=80)
            {
            *(rgbbuf+640*(479-y)+x) = 0xFF0000; //红色   *(lcd_mp+i) <==> lcd_mp[i]
                if(y>=40 && y<=80)
                {
                    for (int i=x; i <x+40; i++)
                    {
                         *(rgbbuf+640*(479-y)+i) = 0xFF0000;
                    }
                    
                }
            }
            else if(y>=80 && y<=160)
            {
            *(rgbbuf+640*(479-y)+x) = 0xFFFF00;
             if(y>=140 && y<=160)
                {
                     for (int i=x; i <x+40; i++)
                    {
                         *(rgbbuf+640*(479-y)+i) = 0xFFFF00;
                    }
                    
                }
            }
            else
            {
            *(rgbbuf+640*(479-y)+x) = 0x00FF00;
             if(y>=220 && y<=240)
                {
                    for (int i=x; i <x+20; i++)
                    {
                         *(rgbbuf+640*(479-y)+i) = 0x00FF00;
                    }
                }
            }
           
        }
        z++;
    }
    }
    //右横线
    {
    int x,y;
    int z=639;

    for(y=0;y<=240;y++)
    {
        
        for(x=z;x>z-20;x--)
        {
            
            if (y>=0 && y<=80)
            {
            *(rgbbuf+640*(479-y)+x) = 0xFF0000; //红色   *(lcd_mp+i) <==> lcd_mp[i]
             if(y>=40 && y<=80)
                {
                    for (int i=x;i>=x-40;i--)
                    {
                         *(rgbbuf+640*(479-y)+i) = 0xFF0000;
                    }
                    
                }
            }
            else if(y>=80 && y<=160)
            {
            *(rgbbuf+640*(479-y)+x) = 0xFFFF00;
            if(y>=140 && y<=160)
                {
                    for (int i=x; i>=x-40 ; i--)
                    {
                         *(rgbbuf+640*(479-y)+i) = 0xFFFF00;
                    }
                    
                }
            
            }
            else
            {
            *(rgbbuf+640*(479-y)+x) = 0x00FF00;
            if(y>=220 && y<=240)
                {
                    for (int i=x; i>=x-20 ; i--)
                    {
                         *(rgbbuf+640*(479-y)+i) = 0x00FF00;
                    }
                    
                }
            }       
        }
        z--;
    }
    }


}




/*******************************************************************************************
 *      @name   touch_screen_thread
 *      @brief  触摸屏线程函数
 *      @note
 *      @param  arg  :这个参数是将倒车辅助线闪烁原因，所改进的参数，可以将线不会闪烁，提前将线存入参数中
 *                       最后一起映射到lcd上
 * ****************************************************************************************/
void *touch_screen_thread(void *arg) 
{
    int ts_fd = *(int *)arg; // 获取触摸屏设备文件描述符

    int x,y; // 定义x,y坐标变量
    while (1) 
    {
        

        read(ts_fd, &touch, sizeof(touch)); // 读取触摸屏事件

        if (touch.type == EV_ABS && touch.code == ABS_X) 
        {
            x = touch.value; // 获取x轴坐标
        }

        if (touch.type == EV_ABS && touch.code == ABS_Y) 
        {
            y = touch.value; // 获取y轴坐标
        }

        if (touch.type == EV_KEY && touch.code == BTN_TOUCH && touch.value == 0)
        {
            // 触摸屏松开事件，可以在这里处理触摸屏的操作
            touch_x = x;
            touch_y = y;
            if (touch_x>0 && touch_x<80 && touch_y>0&& touch_y<236)
            {
                 DAO_CHE++; //倒车线
                  
            }

             if (touch_x>720 && touch_x<800 && touch_y>0&& touch_y<125)
            {
                  photo++; //拍照
                  
            }

             if (touch_x>720 && touch_x<800 && touch_y>175&& touch_y<235)
            {
                   video++; //录像
                  
            }

             if (touch_x>720 && touch_x<800 && touch_y>250&& touch_y<310)
            {
                   close_video +=2; //结束录像
                  
            }

             if (touch_x>720&& touch_x<800 && touch_y>330&& touch_y<460)
            {
                   video_circle++; //循环录像
                  
            }
            

             if (touch_x>0 && touch_x<80&& touch_y>366&& touch_y<480)
            {
                close_1=2; //关闭按钮
              
                
                  
            }

            
            
        }
    }

    return NULL;
}




/*******************************************************************************************
 *      @name   create_blank_bmp
 *      @brief  创建空白BMP文件返回文件路径
 *      @note
 *      @param  char *filepath 
 * ****************************************************************************************/
char *create_blank_bmp( char *filepath) //创建空白BMP文件返回文件路径
{
    char *ff=filepath;
    FILE *fp = fopen(filepath, "wb");
    if (fp == NULL) {
        //fprintf(stderr, "Failed to open file for writing, errno=%d, %s\n", errno, strerror(errno));
        exit(-1);
    }

    // BMP 文件头
    unsigned char bmp_header[54] = {
        0x42, 0x4D,                               // BMP Signature
        0x36, 0x58, 0x00, 0x00,                   // File size (54 + WIDTH*HEIGHT*3)
        0x00, 0x00,                               // Reserved1
        0x00, 0x00,                               // Reserved2
        0x36, 0x00, 0x00, 0x00,                   // Offset to data
        0x28, 0x00, 0x00, 0x00,                   // Size of Info Header
        WIDTH & 0xFF, (WIDTH >> 8) & 0xFF, (WIDTH >> 16) & 0xFF, (WIDTH >> 24) & 0xFF, // Width
        HEIGHT & 0xFF, (HEIGHT >> 8) & 0xFF, (HEIGHT >> 16) & 0xFF, (HEIGHT >> 24) & 0xFF, // Height
        0x01, 0x00,                               // Number of color planes
        0x18, 0x00,                               // Bits per pixel
        0x00, 0x00, 0x00, 0x00,                   // Compression
        0x00, 0x00, 0x00, 0x00,                   // Size of bitmap data
        0x13, 0x0B, 0x00, 0x00,                   // Horizontal resolution
        0x13, 0x0B, 0x00, 0x00,                   // Vertical resolution
        0x00, 0x00, 0x00, 0x00,                   // Number of color palettes
        0x00, 0x00, 0x00                           // Important color
    };

    // 计算文件大小并填入文件头
    int filesize = 54 + WIDTH * HEIGHT * 3;
    bmp_header[2] = (unsigned char)(filesize);
    bmp_header[3] = (unsigned char)(filesize >> 8);
    bmp_header[4] = (unsigned char)(filesize >> 16);
    bmp_header[5] = (unsigned char)(filesize >> 24);

    // 写入 BMP 文件头
    fwrite(bmp_header, sizeof(bmp_header), 1, fp);

    // 创建全白图像数据
    unsigned char *data = (unsigned char *)malloc(WIDTH * HEIGHT * 3);
    if (data == NULL) {
        //fprintf(stderr, "malloc error, errno=%d, %s\n", errno, strerror(errno));
        fclose(fp);
        exit(-1);
    }

    // 填充图像数据为白色
    memset(data, 255, WIDTH * HEIGHT * 3); // 设置为全白

    // 写入图像数据
    fwrite(data, 1, WIDTH * HEIGHT * 3, fp);

    free(data);
    fclose(fp);
    return ff;//返回文件路径
}






/*******************************************************************************************
 *      @name   Bmp_Decode
 *      @brief  解码图片文件并写入到LCD映射内存中
 *      @note   none
 *      @param  char *filepath 
 * ****************************************************************************************/
bool Bmp_Decode(const char *bmp_path,unsigned int *lcd_mp)
{
    //1.打开BMP图像  以二进制只读的方式打开 "rb"
    FILE *bmp_fp = fopen(bmp_path,"rb");

    if( NULL == bmp_fp)
    {
        //fprintf(stderr,"fopen [%s] error,errno=%d,%s\n",bmp_path,errno,strerror(errno));
        return false;
    }
    

    //2.由于不需要读取图像的属性信息，所以把文件的位置指示器进行设置，向后偏移54字节
    fseek(bmp_fp,54,SEEK_SET);
   
    //3.循环从BMP图像中读取一行数据并转化为ARGB格式，写入到LCD对应的像素点
    
    char bufline[800*3] = {0}; //用于存储一行像素点的颜色分量
    unsigned int buf[LCD_MAPSIZE]={0};  //定义一个全部变量用于辅助线覆盖图片上方

    for (size_t y = 0; y < 480; y++)
    {
        //读取BMP图像的一行数据 
        fread(bufline,800*3,1,bmp_fp);

        //BMP图片的像素点是24bit色深，所以应该把bufline中存储的颜色分量以3个字节为一组,循环处理 
        for (size_t x = 0; x < 800; x++)
        {
            int data = 0; //用于存储转换之后的像素点

            //BMP是小端存储，所以3个字节的颜色分量的顺序是BGR,需要转换为LCD像素点的存储格式ARGB
            data |= bufline[3*x+0];     //B 蓝色分量
            data |= bufline[3*x+1]<<8;  //G 绿色分量
            data |= bufline[3*x+2]<<16; //R 红色分量

            //把转换之后的像素点的颜色分量写入到LCD的映射内存，从下向上，从左向右的顺序
            *(buf+(800*(479-y))+x) = data;
        }
    }

     memcpy(lcd_mp,buf,LCD_MAPSIZE); //将一起映射的内存存入lcd_mp中
     fclose(bmp_fp);

    return true;
}






/*******************************************************************************************
 *      @name   pixel_yuv2rgb
 *      @brief  解码YUV文件并写入到LCD映射内存中
 *      @note   none
 *      @param  char *filepath 
 * ****************************************************************************************/
int pixel_yuv2rgb(unsigned char Y, unsigned char U, unsigned char V)
 {
    int R, G, B;

    // 转换公式，使用整数算术和移位
    R = ((298 * (Y - YUV_OFFSET) + 409 * (U - UVC_OFFSET) + 128) >> 8);
    G = ((298 * (Y - YUV_OFFSET) - 100 * (U - UVC_OFFSET) - 208 * (V - UVC_OFFSET) + 128) >> 8);
    B = ((298 * (Y - YUV_OFFSET) + 516 * (V - UVC_OFFSET) + 128) >> 8);

    // 限制 R, G, B 值在合法范围内
    R = (R < 0) ? 0 : (R > 255 ? 255 : R);
    G = (G < 0) ? 0 : (G > 255 ? 255 : G);
    B = (B < 0) ? 0 : (B > 255 ? 255 : B);

    return (B << 16) | (G << 8) | R; // ARGB 格式
}




/*******************************************************************************************
 *      @name   pixel_yuv3rgb
 *      @brief  计算分量转换为 RGB 格式
 *      @note   none
 *      @param  char *filepath 
 * 
 *  * ****************************************************************************************/

void pixel_yuv3rgb(char Y, char Cb, char Cr, unsigned char rgbbuf[]) 
{
    // 计算 R, G, B 分量
    int R = (int)(Y + 1.402 * (Cr - 128));
    int G = (int)(Y - 0.344136 * (Cb - 128) - 0.714136 * (Cr - 128));
    int B = (int)(Y + 1.772 * (Cb - 128));

    // 边界处理
    rgbbuf[0] = B < 0 ? 0 : (B > 255 ? 255 : B);
    rgbbuf[1] = G < 0 ? 0 : (G > 255 ? 255 : G);
    rgbbuf[2] = R < 0 ? 0 : (R > 255 ? 255 : R);
}



/*******************************************************************************************
 *      @name   O_put_yuv_to_bmp
 *      @brief  将YUV数据写入BMP文件
 *      @note   none
 *      @param  char *yuvbuf 
****************************************************************************************/
void O_put_yuv_to_bmp(char *yuvbuf) 
{
    
    //创建空白BMP文件返回文件路径
    // 打开空白 BMP 文件
    char bmp_path[100] = {0};
    //拍照
    if (photo%2==0)
    {
        sprintf(bmp_path, "/tmp/bmp3/%d.bmp", photo_num);
    }
    //录像
    if (video%2==0)
    {
         
        if (video==2)
        {
              
              sprintf(bmp_path, "/tmp/bmp4/%d.bmp", ++video_num_1);
        }
        
        if (video==4)
        {
             
              sprintf(bmp_path, "/tmp/bmp5/%d.bmp", ++video_num_2);
        }

         if ( video==6)
        {
             
              sprintf(bmp_path, "/tmp/bmp6/%d.bmp", ++video_num_3);
        }

         if ( video==8)
        {
            
              sprintf(bmp_path, "/tmp/bmp7/%d.bmp", ++video_num_4);
        }

         if (video==10)
        {
             
              sprintf(bmp_path, "/tmp/bmp8/%d.bmp", ++video_num_5);
        } 
         
       

    }

    //循环录像
    if (video_circle%2==0)
    {
        setGlobalVariable();     // 循环录像图片范围维持在1-200之间
        sprintf(bmp_path, "/tmp/bmp9/%d.bmp", video_num_circle);
    }

    char *ff = create_blank_bmp(bmp_path);
    FILE *fp = fopen(ff, "w+b");
    if (fp == NULL) {
        //fprintf(stderr, "Failed to open file for writing, errno=%d, %s\n", errno, strerror(errno));
        exit(-1);
    }

    // 写入 BMP 文件头
    unsigned char bmp_header[54] = {
        0x42, 0x4D, // BM
        0x36, 0x58, 0x00, 0x00, 0x00, // 文件大小
        0x00, 0x00, // 保留
        0x00, 0x00, // 保留
        0x36, 0x00, 0x00, 0x00, // 从哪开始
        0x28, 0x00, 0x00, 0x00, // 头的大小
        0x40, 0x01, 0x00, 0x00, // 图宽 640
        0xE0, 0x01, 0x00, 0x00, // 图高 480
        0x01, 0x00, // 颜色平面数
        0x18, 0x00, // 每像素位数
        0x00, 0x00, 0x00, 0x00, // 压缩类型
        0x00, 0x00, 0x00, 0x00, // 原图像大小
        0x13, 0x0B, 0x00, 0x00, // 水平分辨率
        0x13, 0x0B, 0x00, 0x00, // 垂直分辨率
        0x00, 0x00, 0x00, 0x00, // 调色板数
        0x00, 0x00, 0x00 // 重要颜色数
    };

    fwrite(bmp_header, sizeof(bmp_header), 1, fp);
    int j=0;
    unsigned char rgbbuf[640 * 480 * 3] = {0}; // RGB 缓冲区
    char Y,Cb,Cr;
    for (int i = 0; i < 640 * 480; ) 
    {
        Y = yuvbuf[j+0]; // Y 数据
        Cb = yuvbuf[j+1]; // Cb 数据
        Cr = yuvbuf[j+3]; // Cr 数据 (需要修正索引)
        pixel_yuv3rgb(Y, Cb, Cr, rgbbuf + i * 3); // 转换为 RGB
        i++;
        Y = yuvbuf[j+2]; // Y 数据
        Cb = yuvbuf[j+1]; // Cb 数据
        Cr = yuvbuf[j+3]; // Cr 数据 (需要修正索引)
        pixel_yuv3rgb(Y, Cb, Cr, rgbbuf + i * 3); // 转换为 RGB
        i++;
        j+=4;
    }
    
     // 写入 RGB 数据，从上到下写入
    for (int y = 0; y < 480; y++)
     {
        fwrite(rgbbuf +( 479-y) * 640 * 3, 1, 640 * 3, fp);
    }
    fclose(fp);
}





/*******************************************************************************************
 *      @name   yuyv_to_lcd
 *      @brief  将YUYV数据写入LCD映射内存中
 *      @note   none
 *      @param  char *yuvbuf 
 * ****************************************************************************************/
void yuyv_to_lcd(char *yuvbuf)
{   
    size_t i = 0,j = 0;
   
    unsigned int rgbbuf[640*480] = {0}; //相当于是缓冲区

    //YUYV是用4个字节表示2个像素点 
    for (i = 0,j = 0; i < 640*480; i+=2,j+=4)
    {
        rgbbuf[i+0] = pixel_yuv2rgb(yuvbuf[j+0],yuvbuf[j+1],yuvbuf[j+3]);  //Y1 U V -- ARGB
        rgbbuf[i+1] = pixel_yuv2rgb(yuvbuf[j+2],yuvbuf[j+1],yuvbuf[j+3]);  //Y2 U V -- ARGB 
    }
    
    size_t x = 0,y = 0;
    
    //判断倒车的次数，如果是偶数次，则显示倒车辅助线
    if (DAO_CHE%2==0)
    {
        car_line(rgbbuf);
    }
    
    
    for (size_t y = 0; y < 480; y++)
    {
        for (size_t x = 0; x < 640; x++)
        {
            lcd_mp[y*800+x+80] = rgbbuf[y*640+x]; 
        } 
    } 

    
}




/*******************************************************************************************
 *      @name   open_device_video
 *      @brief  打开摄像头
 *      @note   none
 *      @param  none 
****************************************************************************************/
void open_device_video(void)
{
      
    //打开摄像头，以非阻塞的方式打开摄像头，read或者write不会阻塞
    camera_fd = open (CAMERA_PATH, O_RDWR | O_NONBLOCK, 0);

    //错误处理
    if (-1 == camera_fd) 
    {
            fprintf (stderr, "Cannot open '%s': %d, %s\n",
                                                CAMERA_PATH, errno, strerror (errno));
            exit (-1); //终止程序
    }
}




/*******************************************************************************************
 *      @name   init_device
 *      @brief  打开摄像头
 *      @note   none
 *      @param  none 
****************************************************************************************/
void init_device(void)
{
    //定义摄像头的相关类
    struct v4l2_cropcap cropcap;    //用于记录视频设备的裁剪功能和缩放功能信息
    struct v4l2_format fmt;         //用于记录视频设备的捕捉画面的格式信息
    struct v4l2_requestbuffers req; //用于记录申请的缓冲区的信息

    //1.应用程序应该设置视频设备的数据流的类型，如果需要捕获图像，应该设置V4L2_BUF_TYPE_VIDEO_CAPTURE
	memset (&cropcap,0,sizeof(cropcap));        //清空内存
    cropcap.type = V4L2_BUF_TYPE_VIDEO_CAPTURE; //设置参数
    ioctl(camera_fd, VIDIOC_S_CROP, &cropcap);  //发送请求
    
    
    //2.设置摄像头的采集的图像的格式(帧宽度、帧高度、图像格式...)
	memset (&fmt,0,sizeof(fmt));                            //清空内存
    fmt.type                = V4L2_BUF_TYPE_VIDEO_CAPTURE;  //数据流的类型
    fmt.fmt.pix.width       = 640;                          //图像的宽度，目前使用的摄像头支持(640,480) or (320,240)
    fmt.fmt.pix.height      = 480;                          //图像的高度，目前使用的摄像头支持(640,480) or (320,240)
    fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;            //目前使用的摄像头只支持YUYV格式(像素点的颜色分量编码格式)
    ioctl(camera_fd, VIDIOC_S_FMT, &fmt);                   //发送请求

    //3.为了提高摄像头采集的速率，所以为摄像头申请缓冲区，用于存储采集的图像的颜色分量，一般申请4块缓冲区
    memset (&req,0,sizeof(req));                            //清空内存
    req.count               = 4;                            //缓冲区的数量
    req.type                = V4L2_BUF_TYPE_VIDEO_CAPTURE;  //数据流的类型
    req.memory              = V4L2_MEMORY_MMAP;             //内存映射方式
    ioctl(camera_fd, VIDIOC_REQBUFS, &req);                 //发送请求

    buffers = calloc(req.count, sizeof (*buffers));    //申请内存，用于记录申请到的缓冲区的信息

    //循环申请用于存储图像的缓冲区，并把每个缓冲区的信息都存储到刚才申请的堆空间
    for (n_buffers = 0; n_buffers < req.count; ++n_buffers) 
    {
        //用于记录申请成功的缓冲区
        struct v4l2_buffer buf;

        memset (&buf,0,sizeof(buf));                        //清空内存
        buf.type        = V4L2_BUF_TYPE_VIDEO_CAPTURE;      //数据流的类型
        buf.memory      = V4L2_MEMORY_MMAP;                 //内存映射方式
        buf.index       = n_buffers;                        //缓冲区的编号
        ioctl (camera_fd, VIDIOC_QUERYBUF, &buf);           //发送请求

        buffers[n_buffers].length = buf.length;             //记录信息
        buffers[n_buffers].start  = mmap(                   //内存映射
                                            NULL,
                                            buf.length,
                                            PROT_READ | PROT_WRITE,
                                            MAP_SHARED ,
                                            camera_fd, 
                                            buf.m.offset
                                        );
    }
}   





/*******************************************************************************************
 *      @name   start_capturing
 *      @brief  打开摄像头
 *      @note   none
 *      @param  none 
****************************************************************************************/
void start_capturing(void)
{
    unsigned int i;
    enum v4l2_buf_type type;

    //循环把缓冲区入队，此时摄像头才会把采集的画面存储到缓冲区中
    for (i = 0; i < n_buffers; ++i) 
    {
        struct v4l2_buffer buf;

        memset (&buf,0,sizeof(buf));                    //清空内存
        buf.type        = V4L2_BUF_TYPE_VIDEO_CAPTURE;  //数据流的类型
        buf.memory      = V4L2_MEMORY_MMAP;             //内存映射方式
        buf.index       = i;                            //缓冲区的编号
        ioctl (camera_fd, VIDIOC_QBUF, &buf);           //把缓冲区入队

    }
    
    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;                 //数据流的类型
    ioctl (camera_fd, VIDIOC_STREAMON, &type);          //开始进行捕获
}





/*******************************************************************************************
 *      @name   mainloop
 *      @brief  循环读取摄像头数据，并显示在LCD上
 *      @note   none
 *      @param  none 
****************************************************************************************/
static void mainloop(void)
{
	unsigned int count;
    struct v4l2_buffer buf;
	unsigned int i;

    count = 100;

    while (count-- > 0) 
    {
        //死循环
        for (;;) 
        {

              if (close_1==2)
                {
                    break;
                   
                }

           
                
            //添加了超时机制，去检测文件描述符的读状态
            fd_set fds;
            struct timeval tv;
            int r;

            FD_ZERO (&fds);
            FD_SET (camera_fd, &fds);

            //超时时间是2s，也就是如果超过2s摄像头的读状态没发生变化，说明不可读
            tv.tv_sec = 2;
            tv.tv_usec = 0;

            r = select (camera_fd + 1, &fds, NULL, NULL, &tv);

            if (-1 == r) 
            {
                if (EINTR == errno)
                        continue;
            }

            if (0 == r) {
                    fprintf (stderr, "select timeout\n");
                    exit (EXIT_FAILURE);
            }

            //如果缓冲区中存储画面，则把缓冲区出队
            for(int i =0;i < n_buffers; ++i)
            {
                struct v4l2_buffer buf;
                memset (&buf,0,sizeof(buf));                    //清空内存
                buf.type        = V4L2_BUF_TYPE_VIDEO_CAPTURE;  //数据流的类型
                buf.memory      = V4L2_MEMORY_MMAP;             //内存映射方式
                ioctl(camera_fd, VIDIOC_DQBUF, &buf);           //把缓冲区出队

                
                //应该用户把出队的缓冲区的像素进行转换，并显示在LCD上
                yuyv_to_lcd(buffers[i].start);
                //拍照
                if (photo%2==0)
                {
                    O_put_yuv_to_bmp(buffers[i].start); //保存图片
                    photo_num++;
                    photo++;
                }

                   //录像
                if (video%2==0)
                {
                    O_put_yuv_to_bmp(buffers[i].start); //保存图片
                    video_num++;
                   
                }

                //循环录像
                if (video_circle%2==0)
                {
                    O_put_yuv_to_bmp(buffers[i].start); //保存图片
                    video_num_circle++;
                   
                }

               
                


                //处理完成后，则把缓冲区入队
                ioctl (camera_fd, VIDIOC_QBUF, &buf);           //把缓冲区入队
            }          
        }

        break;
    }
}











//主函数
int main()
{
  

    open_device(); //打开设备
    
    Bmp_Decode("/tmp/2.bmp",lcd_mp); //显示图片
    //1.打开摄像头
    open_device_video();

    //2.初始化设备
    init_device();

    //3.开始捕获
    start_capturing();


    //触摸线程开启
    pthread_t thread;
    pthread_create(&thread, NULL, touch_screen_thread, &ts_fd);
    //4.开始转换
    mainloop();

    close_camera(); //关闭摄像头
    // close_device(); //关闭设备


    system("./q2");


    

    
    return 0;
}