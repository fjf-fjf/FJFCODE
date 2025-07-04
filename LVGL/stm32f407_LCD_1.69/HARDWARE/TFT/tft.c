#include "includes.h"

uint32_t g_lcd_width =LCD_WIDTH;
uint32_t g_lcd_height=LCD_HEIGHT;
uint32_t g_lcd_direction=0;

void spi1_send_byte(uint8_t byte)
{
#if LCD_SOFT_SPI_ENABLE
  unsigned char counter;

  for (counter = 0; counter < 8; counter++)
  {
    SPI_SCK_0;
    if ((byte & 0x80) == 0)
    {
      SPI_SDA_0;
    }
    else
      SPI_SDA_1;
    byte = byte << 1;
    SPI_SCK_1;
  }
  SPI_SCK_0;	
	
#else
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET)
		;
	SPI_I2S_SendData(SPI1, byte);

	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET)
		;
	SPI_I2S_ReceiveData(SPI1);	
	
#endif

}

void lcd_send_cmd(uint8_t cmd)
{
	SPI_CS_0;
	LCD_DC_0;
	spi1_send_byte(cmd);
	SPI_CS_1;
}

// 向液晶屏写一个8位数据
void lcd_send_data(uint8_t dat)
{
	SPI_CS_0;
	LCD_DC_1;
	spi1_send_byte(dat);
	SPI_CS_1;
}

void lcd_addr_set(uint32_t x_s, uint32_t y_s, uint32_t x_e, uint32_t y_e)
{
	/* 部分tft屏需要偏移量 */
	
	if(lcd_get_direction()==0 || lcd_get_direction()==2)
	{
		y_s=y_s+Y_OFFSET;
		y_e=y_e+Y_OFFSET;		
	}
	
	if(lcd_get_direction()==1 || lcd_get_direction()==3)
	{
		x_s=x_s+X_OFFSET;
		x_e=x_e+X_OFFSET;	
		
	}		


	
	lcd_send_cmd(0x2a);	 		// 列地址设置
	lcd_send_data(x_s>> 8); 	// 起始列
	lcd_send_data(x_s);
	lcd_send_data(x_e >> 8); 	// 结束列
	lcd_send_data(x_e);

	lcd_send_cmd(0x2b);	 		// 行地址设置
	lcd_send_data(y_s>> 8); 	// 起始行
	lcd_send_data(y_s);
	lcd_send_data(y_e >> 8); 	// 结束行
	lcd_send_data(y_e);
	lcd_send_cmd(0x2C); 		// 写显存
}

void lcd_fill(uint32_t x_s, uint32_t y_s, uint32_t x_len, uint32_t y_len,uint32_t color)
{
	uint32_t x, y;
	
	lcd_addr_set(x_s,y_s,x_s+x_len-1,y_s+y_len - 1);

	for (y = y_s; y < y_s+y_len; y++) 
	{
		for (x = x_s; x < x_s+x_len; x++) 
		{

			lcd_send_data(color >> 8);
			lcd_send_data(color);
		}
	}
}

void lcd_clear(uint32_t color)
{
	lcd_fill(0,0,g_lcd_width,g_lcd_height,color);
}

void lcd_draw_picture(uint32_t x_s, uint32_t y_s, uint32_t width, uint32_t height, const uint8_t *pic)
{

	const uint8_t *p = pic;
	uint32_t i = 0;
	
	lcd_addr_set(x_s, y_s, x_s+width-1, y_s+height-1);

	for (i = 0; i <width*height*2; i += 2) 
	{
		lcd_send_data(p[i]);	
		lcd_send_data(p[i + 1]); 
	}
}

void lcd_show_char(uint32_t x, uint32_t y,uint8_t ch,uint32_t fc,uint32_t bc,uint32_t font_size,uint32_t mode)
{

	u8 temp,sizex,t,m=0;
	u16 i,TypefaceNum;						//一个字符所占字节大小
	
	u16 x0=x;
	
	sizex=font_size/2;
	
	TypefaceNum=(sizex/8+((sizex%8)?1:0))*font_size;
	
	ch=ch-' ';    						//得到偏移后的值
	
	lcd_addr_set(x,y,x+sizex-1,y+font_size-1);  //设置光标位置 
	
	for(i=0;i<TypefaceNum;i++)
	{ 
		if(font_size==12)temp=ascii_1206[ch][i];		      //调用6x12字体
		else if(font_size==16)temp=ascii_1608[ch][i];		 //调用8x16字体
		else if(font_size==24)temp=ascii_2412[ch][i];		 //调用12x24字体
		else if(font_size==32)temp=ascii_3216[ch][i];		 //调用16x32字体
		else return;
		for(t=0;t<8;t++)
		{
			if(!mode)//非叠加模式
			{
				if(temp&(0x01<<t))
				{
					lcd_send_data(fc>>8);
					lcd_send_data(fc);
				}
				else 
				{
					lcd_send_data(bc>>8);
					lcd_send_data(bc);
				}
				m++;
				if(m%sizex==0)
				{
					m=0;
					break;
				}
			}
			else//叠加模式
			{
				if(temp&(0x01<<t))lcd_draw_point(x,y,fc);//画一个点
				x++;
				if((x-x0)==sizex)
				{
					x=x0;
					y++;
					break;
				}
			}
		}
	}  
}

void lcd_show_string(u16 x,u16 y,const u8 *p,u16 fc,u16 bc,u8 font_size,u8 mode)
{         
	while(*p!='\0')
	{       
		lcd_show_char(x,y,*p,fc,bc,font_size,mode);
		x+=font_size/2;
		p++;
	}  
}

/******************************************************************************
*函数说明：显示数字
*入口数据：m底数，n指数
*返回值：  无
******************************************************************************/
u32 mypow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;
	return result;
}


/******************************************************************************
*函数说明：显示整数变量
*入口数据：x,y显示坐标
	num 要显示整数变量
	len 要显示的位数
	fc 字的颜色
	bc 字的背景色
	font_size 字号
*返回值：  无
******************************************************************************/
void lcd_show_integer(uint32_t x,uint32_t y,uint32_t num,uint32_t len,uint32_t fc,uint32_t bc,uint32_t font_size)
{         	
	u8 t,temp;
	u8 enshow=0;
	u8 sizex=font_size/2;
	for(t=0;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				lcd_show_char(x+t*sizex,y,' ',fc,bc,font_size,0);
				continue;
			}else enshow=1; 
		 	 
		}
	 	lcd_show_char(x+t*sizex,y,temp+48,fc,bc,font_size,0);
	}
} 


/******************************************************************************
*函数说明：显示两位小数变量
*入口数据：x,y显示坐标
		num 要显示小数变量
		len 要显示的位数
		fc 字的颜色
		bc 字的背景色
		font_size 字号
*返回值：  无
******************************************************************************/
void lcd_show_float(uint32_t x,uint32_t y,float num,uint32_t len,uint32_t fc,uint32_t bc,uint32_t font_size)
{         	
	uint32_t t,temp,sizex;
	uint32_t num1;
	sizex=font_size/2;
	num1=num*100;
	for(t=0;t<len;t++)
	{
		temp=(num1/mypow(10,len-t-1))%10;
		if(t==(len-2))
		{
			lcd_show_char(x+(len-2)*sizex,y,'.',fc,bc,font_size,0);
			t++;
			len+=1;
		}
	 	lcd_show_char(x+t*sizex,y,temp+48,fc,bc,font_size,0);
	}
}



void lcd_init(void) ////ST7789V2
{
	
	GPIO_InitTypeDef	GPIO_InitStructure;
	SPI_InitTypeDef  	SPI_InitStructure;
#if LCD_SOFT_SPI_ENABLE
	
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE, ENABLE);

	// 引脚的配置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;      // 输出模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; // 速度设置更高
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     // 推挽输出，Push Pull，使能了PMOS还有NMOS管
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;   // 不使能上下拉电阻
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7| GPIO_Pin_9|GPIO_Pin_11|GPIO_Pin_13|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;      // 输出模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; // 速度设置更高
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     // 推挽输出，Push Pull，使能了PMOS还有NMOS管
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;   // 不使能上下拉电阻
	GPIO_Init(GPIOE, &GPIO_InitStructure);

#else
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

	// SCK=PB3,  MOSI=PB5
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	 //复用功能模式
	GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed; //引脚高速工作，收到指令立即工作；缺点：功耗高
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	 //增加输出电流的能力
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //不需要上下拉电阻
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;	 //输出模式
	GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed; //引脚高速工作，收到指令立即工作；缺点：功耗高
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	 //增加输出电流的能力
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //不需要上下拉电阻
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7 | GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;	 //输出模式
	GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed; //引脚高速工作，收到指令立即工作；缺点：功耗高
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	 //增加输出电流的能力
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //不需要上下拉电阻
	GPIO_Init(GPIOG, &GPIO_InitStructure);

	// PB3 PB5连接到SPI1硬件
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_SPI1);

	//关闭SPI1
	SPI_Cmd(SPI1, DISABLE);

	//设置SPI
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; //全双工收发
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;					   //设为主机
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;				   // 8位帧结构
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;						   //空闲时时钟为低
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;					   //第1个时钟沿捕获数据
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;						   // CS由SSI位控制（自控）
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2; //波特率为2分频
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;				   //高位先传送
	SPI_InitStructure.SPI_CRCPolynomial = 0;						   //不使用CRC
	SPI_Init(SPI1, &SPI_InitStructure);								   //初始化SPI1

	//启动SPI1
	SPI_Cmd(SPI1, ENABLE);
	
#endif

	//该1.69英寸屏幕背光为低电平点亮
	LCD_BLK_1;
	
	SPI_SCK_0;

	SPI_SCK_1; // 特别注意！！
	LCD_RST_0;
	delay_ms(100);
	LCD_RST_1;
	delay_ms(100);
	lcd_send_cmd(0x11); // Sleep Out
	delay_ms(120);		// DELAY120ms
	//-----------------------ST7789V Frame rate setting-----------------//
	//************************************************
	lcd_send_cmd(0x3A); // 65k mode
	lcd_send_data(0x05);
	lcd_send_cmd(0xC5); // VCOM
	lcd_send_data(0x1A);
	lcd_send_cmd(0x36); // 屏幕显示方向设置
	lcd_send_data(0x00);
	//-------------ST7789V Frame rate setting-----------//
	lcd_send_cmd(0xb2); // Porch Setting
	lcd_send_data(0x05);
	lcd_send_data(0x05);
	lcd_send_data(0x00);
	lcd_send_data(0x33);
	lcd_send_data(0x33);

	lcd_send_cmd(0xb7);	 // Gate Control
	lcd_send_data(0x05); // 12.2v   -10.43v
	//--------------ST7789V Power setting---------------//
	lcd_send_cmd(0xBB); // VCOM
	lcd_send_data(0x3F);

	lcd_send_cmd(0xC0); // Power control
	lcd_send_data(0x2c);

	lcd_send_cmd(0xC2); // VDV and VRH Command Enable
	lcd_send_data(0x01);

	lcd_send_cmd(0xC3);	 // VRH Set
	lcd_send_data(0x0F); // 4.3+( vcom+vcom offset+vdv)

	lcd_send_cmd(0xC4);	 // VDV Set
	lcd_send_data(0x20); // 0v

	lcd_send_cmd(0xC6);	 // Frame Rate Control in Normal Mode
	lcd_send_data(0X01); // 111Hz

	lcd_send_cmd(0xd0); // Power Control 1
	lcd_send_data(0xa4);
	lcd_send_data(0xa1);

	lcd_send_cmd(0xE8); // Power Control 1
	lcd_send_data(0x03);

	lcd_send_cmd(0xE9); // Equalize time control
	lcd_send_data(0x09);
	lcd_send_data(0x09);
	lcd_send_data(0x08);
	//---------------ST7789V gamma setting-------------//
	lcd_send_cmd(0xE0); // Set Gamma
	lcd_send_data(0xD0);
	lcd_send_data(0x05);
	lcd_send_data(0x09);
	lcd_send_data(0x09);
	lcd_send_data(0x08);
	lcd_send_data(0x14);
	lcd_send_data(0x28);
	lcd_send_data(0x33);
	lcd_send_data(0x3F);
	lcd_send_data(0x07);
	lcd_send_data(0x13);
	lcd_send_data(0x14);
	lcd_send_data(0x28);
	lcd_send_data(0x30);

	lcd_send_cmd(0XE1); // Set Gamma
	lcd_send_data(0xD0);
	lcd_send_data(0x05);
	lcd_send_data(0x09);
	lcd_send_data(0x09);
	lcd_send_data(0x08);
	lcd_send_data(0x03);
	lcd_send_data(0x24);
	lcd_send_data(0x32);
	lcd_send_data(0x32);
	lcd_send_data(0x3B);
	lcd_send_data(0x14);
	lcd_send_data(0x13);
	lcd_send_data(0x28);
	lcd_send_data(0x2F);

	lcd_send_cmd(0x21); // 反显

	lcd_send_cmd(0x29); // 开启显示
	
}

void lcd_show_chn(uint32_t x, uint32_t y,uint8_t no, uint32_t fc, uint32_t bc,uint32_t font_size)
{
	uint32_t i,j;
	uint8_t tmp;

	lcd_addr_set(x, y, x + font_size-1, y + font_size-1);

	for (i = 0; i < (font_size*font_size/8); i++) // column loop
	{
		if(font_size==16)tmp = chinese_tbl_16[no][i];
		if(font_size==24)tmp = chinese_tbl_24[no][i];	
		if(font_size==32)tmp = chinese_tbl_32[no][i];
		
		for (j = 0;j < 8; j++)
		{
			if (tmp & (1<<j))
			{
				lcd_send_data(fc >> 8);
				lcd_send_data(fc);
			}
			
			else
			{
				lcd_send_data(bc);
				lcd_send_data(bc);
			}
		}
	}
}

void lcd_draw_point(uint32_t x, uint32_t y, uint32_t color)
{
	lcd_addr_set(x, y, x, y);

	lcd_send_data(color >> 8);
	lcd_send_data(color);
}


void lcd_draw_line(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color)
{
	uint16_t t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance;
	int incx,incy,uRow,uCol;
	delta_x=x2-x1; //计算坐标增量 
	delta_y=y2-y1;
	uRow=x1;//画线起点坐标
	uCol=y1;
	if(delta_x>0)incx=1; //设置单步方向 
	else if (delta_x==0)incx=0;//垂直线 
	else {incx=-1;delta_x=-delta_x;}
	if(delta_y>0)incy=1;
	else if (delta_y==0)incy=0;//水平线 
	else {incy=-1;delta_y=-delta_y;}
	if(delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
	else distance=delta_y;
	for(t=0;t<distance+1;t++)
	{
		lcd_draw_point(uRow,uCol,color);//画点
		xerr+=delta_x;
		yerr+=delta_y;
		if(xerr>distance)
		{
			xerr-=distance;
			uRow+=incx;
		}
		if(yerr>distance)
		{
			yerr-=distance;
			uCol+=incy;
		}
	}
}

void lcd_draw_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color)
{
	lcd_draw_line(x1,y1,x2,y1,color);
	lcd_draw_line(x1,y1,x1,y2,color);
	lcd_draw_line(x1,y2,x2,y2,color);
	lcd_draw_line(x2,y1,x2,y2,color);
}

void lcd_draw_circle(uint16_t x0,uint16_t y0,uint8_t r,uint16_t color)
{
	int a,b;
	
	a=0;b=r;
	
	while(a<=b)
	{
		lcd_draw_point(x0-b,y0-a,color);             //3           
		lcd_draw_point(x0+b,y0-a,color);             //0           
		lcd_draw_point(x0-a,y0+b,color);             //1                
		lcd_draw_point(x0-a,y0-b,color);             //2             
		lcd_draw_point(x0+b,y0+a,color);             //4               
		lcd_draw_point(x0+a,y0-b,color);             //5
		lcd_draw_point(x0+a,y0+b,color);             //6 
		lcd_draw_point(x0-b,y0+a,color);             //7
		a++;
		if((a*a+b*b)>(r*r))//判断要画的点是否过远
		{
			b--;
		}
	}
}


void lcd_set_direction(uint32_t dir)
{
	g_lcd_direction = dir;
	
	/* 0°*/
	if(dir==0)
	{
		lcd_send_cmd(0x36);
		lcd_send_data(0x00);
		g_lcd_width=LCD_WIDTH;
		g_lcd_height=LCD_HEIGHT;
	}
	
	/* 90°*/
	if(dir==1)
	{
		lcd_send_cmd(0x36);
		lcd_send_data((1<<6)|(1<<5)|(1<<4));
		g_lcd_width=LCD_HEIGHT;
		g_lcd_height=LCD_WIDTH;
	
	}	
	
	/* 180°*/
	if(dir==2)
	{
		lcd_send_cmd(0x36);
		lcd_send_data((1<<7)|(1<<6));
		g_lcd_width=LCD_WIDTH;
		g_lcd_height=LCD_HEIGHT;
	
	}
	
	/* 270°*/
	if(dir==3)
	{
		lcd_send_cmd(0x36);
		lcd_send_data((1<<7)|(0<<6)|(1<<5)|(1<<4));
		g_lcd_width=LCD_HEIGHT;
		g_lcd_height=LCD_WIDTH;
	
	}		

}

uint32_t lcd_get_direction(void)
{
	return g_lcd_direction;
}

void spi1_tx_dma_init(uint32_t DMA_Memory0BaseAddr, uint16_t DMA_BufferSize, uint32_t DMA_MemoryDataSize, uint32_t DMA_MemoryInc)
{
	NVIC_InitTypeDef 	NVIC_InitStructure;		
	DMA_InitTypeDef 		DMA_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE); // DMA2时钟使能

	DMA_DeInit(DMA2_Stream3);

	// 等待DMA2_Stream1可配置
	while (DMA_GetCmdStatus(DMA2_Stream3) != DISABLE)
		;

	/* 配置 DMA Stream */
	DMA_InitStructure.DMA_Channel = DMA_Channel_3;							// 通道3 SPI1通道
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&SPI1->DR;			// 外设地址为:SPI1->DR
	DMA_InitStructure.DMA_Memory0BaseAddr = DMA_Memory0BaseAddr;			// DMA 存储器0地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;					// 存储器到外设模式
	DMA_InitStructure.DMA_BufferSize = DMA_BufferSize;						// 数据传输量
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;		// 外设非增量模式
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc;						// 存储器增量模式
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; // 外设数据长度:8位
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize;				// 存储器数据长度:8位
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;							// 正常模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;						// 高优先级
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;					// 禁用FIFO模式
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;			//
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;				// 外设突发单次传输
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;		// 存储器突发单次传输
	DMA_Init(DMA2_Stream3, &DMA_InitStructure);

	DMA_ClearFlag(DMA2_Stream3, DMA_FLAG_TCIF3);
	
	DMA_Cmd(DMA2_Stream3, ENABLE);
	
	
	/* 开启传输完成中断  */		
    DMA_ITConfig(DMA2_Stream3,DMA_IT_TC,ENABLE);

    // 中断初始化 
    /* DMA发送中断源 */  
    NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream3_IRQn;	
    /* 抢断优先级 */  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    /* 响应优先级 */  
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;				
    /* 使能外部中断通道 */ 
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;						 
    /* 配置NVIC */		
    NVIC_Init(&NVIC_InitStructure);

}

void spi1_tx_dma_start(void)
{
	DMA_Cmd(DMA2_Stream3, ENABLE);
}

void spi1_tx_dma_stop(void)
{
	DMA_Cmd(DMA2_Stream3, DISABLE);
}




void DMA2_Stream3_IRQHandler(void)
{
    // DMA 发送完成
    if(DMA_GetITStatus(DMA2_Stream3, DMA_IT_TCIF3))	
    {
        // 清除DMA发送完成标志
        DMA_ClearITPendingBit(DMA2_Stream3, DMA_IT_TCIF3);	
		
        // 片选拉高，数据发送完毕	
        SPI_CS_1;	
    }
	
}



