#define _POSIX_C_SOURCE 200112L
#include "lvgl/lvgl.h"
#include "lvgl/demos/lv_demos.h"
#include "lv_drivers/display/fbdev.h"
#include "lv_drivers/indev/evdev.h"
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h> // 添加stdlib.h头文件以使用system函数
#include <stdio.h> // 添加stdio.h头文件以使用printf函数
#include "my_font.c"
#include"./output/ui.h"


#include <time.h>      // 或 #include <sys/time.h>








#define DISP_BUF_SIZE (128 * 1024)

// 全局变量：键盘对象
static lv_obj_t *kb;
static lv_obj_t *textbox1; // 声明textbox1为全局变量

// 自定义字体和样式
 lv_style_t style_big;
static lv_style_t style_mid;

// 大字体24
static void font_style_big(void)
{
    // 创建字体
    static lv_ft_info_t info;
    /*FreeType uses C standard file system, so no driver letter is required.*/
    info.name = "/usr/share/fonts/DroidSansFallback.ttf";
    info.weight = 24;
    info.style = FT_FONT_STYLE_NORMAL;
    info.mem = NULL;
    if(!lv_ft_font_init(&info)) 
    {
        LV_LOG_ERROR("create failed.");
    }

    // 创建字体样式
    lv_style_init(&style_big);
    lv_style_set_text_font(&style_big, info.font);
    lv_style_set_text_align(&style_big, LV_TEXT_ALIGN_CENTER);
}


//中字体16
static void font_style_mid(void)
{
    // 创建字体
    static lv_ft_info_t info;
    /*FreeType uses C standard file system, so no driver letter is required.*/
    info.name = "/usr/share/fonts/DroidSansFallback.ttf";
    info.weight = 16;
    info.style = FT_FONT_STYLE_NORMAL;
    info.mem = NULL;
    if(!lv_ft_font_init(&info)) 
    {
        LV_LOG_ERROR("create failed.");
    }

    // 创建字体样式
    lv_style_init(&style_mid);
    lv_style_set_text_font(&style_mid, info.font);
    lv_style_set_text_align(&style_mid, LV_TEXT_ALIGN_CENTER);



}


// 按钮事件回调函数
static void verification_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED) 
    {
        system("./q1"); // 在按钮点击时运行system函数
    }
}

// 事件回调函数：处理焦点变化和内容保存
static void ta_event_cb(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *ta = lv_event_get_target(e);

    if (code == LV_EVENT_FOCUSED) {
        lv_keyboard_set_textarea(kb, ta);
        lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
    } else if (code == LV_EVENT_DEFOCUSED) {
        lv_keyboard_set_textarea(kb, NULL);
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);

        // 检查是否为textbox1并保存内容
        if (ta == textbox1) {
            const char *text = lv_textarea_get_text(ta);
            if (text != NULL && text[0] != '\0') { // 检查文本框内容是否为空
                FILE *file = fopen("/tmp/1.txt", "w");
                if (file != NULL) {
                    fputs(text, file);
                    fclose(file);
                    printf("Text saved to /tmp/1.txt\n"); // 调试信息
                } else {
                    perror("Failed to open file /tmp/1.txt"); // 打印错误信息
                }
            } else {
                printf("Text is empty, nothing to save\n"); // 调试信息
            }
        }
    }
}

int main(void)
{
    //初始化
    lv_init();
    //初始化硬件驱动设备
    fbdev_init();

    /*A small buffer for LittlevGL to draw the screen's content*/
    static lv_color_t buf[DISP_BUF_SIZE];

    /*Initialize a descriptor for the buffer*/
    static lv_disp_draw_buf_t disp_buf;
    lv_disp_draw_buf_init(&disp_buf, buf, NULL, DISP_BUF_SIZE);

    /*Initialize and register a display driver*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.draw_buf   = &disp_buf;
    disp_drv.flush_cb   = fbdev_flush;
    disp_drv.hor_res    = 800;
    disp_drv.ver_res    = 480;
    lv_disp_drv_register(&disp_drv);

    evdev_init();
    static lv_indev_drv_t indev_drv_1;
    lv_indev_drv_init(&indev_drv_1); /*Basic initialization*/
    indev_drv_1.type = LV_INDEV_TYPE_POINTER;

    /*This function will be called periodically (by the library) to get the mouse position and state*/
    indev_drv_1.read_cb = evdev_read;
    lv_indev_t *mouse_indev = lv_indev_drv_register(&indev_drv_1);

    //案例运行
    //lv_demo_music();            /*音乐播放器*/
    //lv_demo_widgets();          /*小部件示例*/
    //lv_demo_keypad_encoder();   /*按键和编码器示例*/
    //lv_demo_benchmark();        /*性能测试*/
    //lv_demo_stress();             /*压力测试*/

    /*********************************自己写的案例***************************************/

    // // // 调用自定义函数创建字体和样式
     font_style_big();
     font_style_mid();
     
     system("./q1");
     

    

    //创建线程
   pthread_t thread_2;
   pthread_create(&thread_2, NULL, openaifuction, NULL); 
    ui_init();
    

    
    


    /*Handle LitlevGL tasks (tickless mode)*/
    while(1) 
    {
        lv_tick_inc(5);//这个函数必须调用的
        lv_timer_handler();
        usleep(5000);
    }
    return 0;
}

/*Set in lv_conf.h as `LV_TICK_CUSTOM_SYS_TIME_EXPR`*/
uint32_t custom_tick_get(void)
{
    static uint64_t start_ms = 0;
    if(start_ms == 0) {
        struct timeval tv_start;
        gettimeofday(&tv_start, NULL);
        start_ms = (tv_start.tv_sec * 1000000 + tv_start.tv_usec) / 1000;
    }

    struct timeval tv_now;
    gettimeofday(&tv_now, NULL);
    uint64_t now_ms;
    now_ms = (tv_now.tv_sec * 1000000 + tv_now.tv_usec) / 1000;

    uint32_t time_ms = now_ms - start_ms;
    return time_ms;
}
