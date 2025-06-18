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
#include "device.h"

//宏定义区
////////////////////////////////////////////////////////////////////////////////////////////
#define LCD_DEV     "/dev/fb0" //LCD设备文件

#define MMAP_SIZE   800*480*4//映射的内存大小

#define GIF_NUM     72       //开机动画的帧数

#define  TS_DEV   "/dev/input/event0" //触摸屏设备文件


//全局变量区
////////////////////////////////////////////////////////////////////////////////////////////
int touch_x=0;//触摸屏的x坐标

int touch_y=0;//触摸屏的y坐标

struct input_event touch;//触摸屏的输入事件


//函数声明区
////////////////////////////////////////////////////////////////////////////////////////////
/*******************************************************************************************
 *      @name   Bmp_Decode
 *      @brief  图片解码
 *      @note
 *      @param  lcd_mp  :.
 *      @param  bmp_path  :指的是图片的路径名称   
 * ****************************************************************************************/
bool Bmp_Decode(const char *bmp_path,unsigned int *lcd_mp)
{
    //1.打开BMP图像  以二进制只读的方式打开 "rb"
    FILE *bmp_fp = fopen(bmp_path,"rb");

    if( NULL == bmp_fp)
    {
        fprintf(stderr,"fopen [%s] error,errno=%d,%s\n",bmp_path,errno,strerror(errno));
        return false;
    }
    

    //2.由于不需要读取图像的属性信息，所以把文件的位置指示器进行设置，向后偏移54字节
    fseek(bmp_fp,54,SEEK_SET);
   
    //3.循环从BMP图像中读取一行数据并转化为ARGB格式，写入到LCD对应的像素点
    
    char bufline[800*3] = {0}; //用于存储一行像素点的颜色分量
    unsigned int buf[MMAP_SIZE]={0};  //定义一个全部变量用于辅助线覆盖图片上方

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
     //car_line(buf); //显示车线  
     memcpy(lcd_mp,buf,MMAP_SIZE); //将一起映射的内存存入lcd_mp中
     fclose(bmp_fp);

    return true;
}



/*******************************************************************************************
 *      @name   open_gif
 *      @brief  显示开机动画
 *      @note
 *      @param   gif_path 
 *      @param   lcd_mp
 *      @retval 无  
 * ****************************************************************************************/
void open_gif(unsigned int * lcd_mp)
{
    char gif_path[30] ={0}; //用于存储转换好的图像路径

    //3.在LCD显示开机动画,用户需要自己修改路径
    for (int  i = 0; i < GIF_NUM; i++)
    {
        sprintf(gif_path,"/tmp/bmp2/Frame%d.bmp",i);  //构造名称
       
        Bmp_Decode(gif_path,lcd_mp);                 //图像显示
        usleep(10*1000); 
        if (i==72)
        {
            break;
        }
                                    //FPS=50HZ
    }
      

}



//触摸屏代码
void get_touch_xy(int * touch_x,int *touch_y,int ts_fd  )
{
    
    
     int x,y;
        //获取坐标
        while (1)
        {
                read(ts_fd, &touch, sizeof(touch));
                if(touch.type==EV_ABS &&touch.code==ABS_X)  //EV_ABS是 绝对位移：触摸屏的坐标
                x=touch.value; //获取x轴的地址
                if(touch.type==EV_ABS  &&  touch.code==ABS_Y)
                y=touch.value;  //获取y轴的地址
                if(touch.type == EV_KEY && touch.code == BTN_TOUCH && touch.value == 0) //松手
                { 
            
                    *touch_x=x;
                    *touch_y=y;
                    printf("pppX:%d---pppY:%d\n",touch_x,touch_y); //打印坐标
                    break;
                }
        }
        
        

        
}







//主函数
int main()
{
    
    open_device(); //打开设备文件
   
   open_gif(lcd_mp);//打开图片并且申请映射，显示图片出来

   //点击屏幕任意位置进入主页面
   get_touch_xy(&touch_x,&touch_y,ts_fd);
   if((touch_x>0)&&(touch_x<800)&&(touch_y>0)&&(touch_y<480))
             {
              
                close_device(); //关闭设备文件
                system("./q2");//跳进主页面
                
             }

    return 0;
}
