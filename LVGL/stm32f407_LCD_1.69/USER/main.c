#include "includes.h"
#include "tim.h"

// 主函数
int main(void)
{
    // 初始化lvgl
    lv_init();
	Usart1_Init(115200);
    // 初始化lvgl显示设备
    lv_port_disp_init();

    // 初始化lvgl输入设备
    lv_port_indev_init();



    // tim3初始化，定时周期为1ms
    Tim3_Init();
    // 缘始郫lvgl demo
    lv_demo_widgets();
    while (1)
    {
        lv_task_handler();
		delay_ms(5);
    }

    return 0;
}

//定时器1ms中断服务函数
void TIM3_IRQHandler(void)
{
    /* 检测时间更新中断的标志位是否置位 */
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)
    {
        /* 系统时间向前推进一个单位的时间间隔 */
        lv_tick_inc(1);  //lv_tick_inc参数范围：1~10

        /* 清空标志位 */
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
    }

}

