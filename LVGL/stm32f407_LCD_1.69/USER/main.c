#include "includes.h"
#include "tim.h"

// ������
int main(void)
{
    // ��ʼ��lvgl
    lv_init();
	Usart1_Init(115200);
    // ��ʼ��lvgl��ʾ�豸
    lv_port_disp_init();

    // ��ʼ��lvgl�����豸
    lv_port_indev_init();



    // tim3��ʼ������ʱ����Ϊ1ms
    Tim3_Init();
    // Եʼۯlvgl demo
    lv_demo_widgets();
    while (1)
    {
        lv_task_handler();
		delay_ms(5);
    }

    return 0;
}

//��ʱ��1ms�жϷ�����
void TIM3_IRQHandler(void)
{
    /* ���ʱ������жϵı�־λ�Ƿ���λ */
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)
    {
        /* ϵͳʱ����ǰ�ƽ�һ����λ��ʱ���� */
        lv_tick_inc(1);  //lv_tick_inc������Χ��1~10

        /* ��ձ�־λ */
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
    }

}

