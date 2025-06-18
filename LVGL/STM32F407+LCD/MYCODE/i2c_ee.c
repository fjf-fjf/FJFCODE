#include "i2c_ee.h"
#include "usart.h"


/*******************************************
I2C1_SCL --- PB8
I2C1_SDA -- PB9
ʹ��I2C1
 *****************************************/
void I2C_GPIO_Config(void)
{

  GPIO_InitTypeDef  GPIO_InitStructure; 
  I2C_InitTypeDef  I2C_InitStructure; 


  //GPIOB��ʼ��
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
  //IICʱ��ʹ��
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);

  /* Connect PXx to I2C_SCL*/
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_I2C1);
  /* Connect PXx to I2C_SDA*/
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_I2C1);  
  
  /*!< Configure EEPROM_I2C pins: SCL */   
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;		//����
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;	//��© ����һ��д��©
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  

  /* I2C ���� */
  I2C_InitStructure.I2C_Mode 		= I2C_Mode_I2C;			//I2Cģʽ
  I2C_InitStructure.I2C_DutyCycle 	= I2C_DutyCycle_2;		/* �ߵ�ƽ�����ȶ����͵�ƽ���ݱ仯 SCL ʱ���ߵ�ռ�ձ� */
  I2C_InitStructure.I2C_OwnAddress1 = 0x11; 				//ָ�������I2C�豸��ַ �����ĵ�ַ�ǲ�����ӻ���ͬ����
  I2C_InitStructure.I2C_Ack 		= I2C_Ack_Enable ;		//Ackʹ��		
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;	/* I2C��Ѱַģʽ */
  I2C_InitStructure.I2C_ClockSpeed 		= 400000;	                            /* ͨ������  ���ֻ����400Kbps  */
  
  I2C_Init(I2C1, &I2C_InitStructure);	                                      /* I2C1 ��ʼ�� */
  
  
  I2C_Cmd(I2C1, ENABLE);  	                                                /* ʹ�� I2C1 */

  //Ӧ��ʹ��
  //I2C_AcknowledgeConfig(I2C1, ENABLE);   
  
}

//AT24C02д����
uint32_t I2C_EE_PageWrite(u8 WriteAddr, u8* pBuffer,  u8 NumByteToWrite)
{
	
	//�ȴ����߿���
  while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));  


  //�����ź�
  I2C_GenerateSTART(I2C1, ENABLE);
  //�ȴ���������
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));/*EV5,��ģʽ*/
 
  /* Send EEPROM address for write */
  //�����豸��ַ����ִ��д����
  I2C_Send7bitAddress(I2C1, 0xA0, I2C_Direction_Transmitter);
  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)); 

  /* Send the EEPROM's internal address to write to */    
	//����д���ݵ���ʼ��ַ
  I2C_SendData(I2C1, WriteAddr);  
  /* Test on EV8 and clear it */
  while(! I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)); 

  /* While there is data to be written */
  while(NumByteToWrite--)  
  {
    /* Send the current byte */
    I2C_SendData(I2C1, *pBuffer); 
    /* Test on EV8 and clear it */
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	  
    /* Point to the next byte to be written */
    pBuffer++; 	  

  }

  /* Send STOP condition */
  I2C_GenerateSTOP(I2C1, ENABLE);
  
  return 1;
}

/**
  * @brief   ��EEPROM�����ȡһ������ 
  * @param   
  *		@arg pBuffer:��Ŵ�EEPROM��ȡ�����ݵĻ�����ָ��
  *		@arg WriteAddr:�������ݵ�EEPROM�ĵ�ַ
  *     @arg NumByteToWrite:Ҫ��EEPROM��ȡ���ֽ���
  * @retval  ��
  */
uint32_t I2C_EE_BufferRead(u8 ReadAddr, u8* pBuffer, u16 NumByteToRead)
{  


  //�ȴ����߿���
    while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));   

  /* Send START condition */
  I2C_GenerateSTART(I2C1, ENABLE);
  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));


  /* Send EEPROM address for write */
  I2C_Send7bitAddress(I2C1, 0xA0, I2C_Direction_Transmitter);
  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)); 
  /* Clear EV6 by setting again the PE bit */

  //�������Ͷ����ݵ���ʼ��ַ
  I2C_SendData(I2C1, ReadAddr);  
  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
  
  //�����ź�
  /* Send STRAT condition a second time */  
  I2C_GenerateSTART(I2C1, ENABLE);
  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
  

//�����豸��ַ��ִ�ж�����
  I2C_Send7bitAddress(I2C1, 0xA1, I2C_Direction_Receiver);
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
  
  
  /* While there is data to be read */
  while(NumByteToRead--)  
  {


	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED)==0);  	
	/* Read a byte from the device */
	*pBuffer = I2C_ReceiveData(I2C1);

	/* Point to the next location where the byte read will be saved */
	pBuffer++; 


	
    if(NumByteToRead > 0)
    {
		//������Ч�ź�
		  I2C_AcknowledgeConfig(I2C1, ENABLE);
		 
    }	
			
				
  }

  /* Enable Acknowledgement to be ready for another reception */
  //������ЧӦ��
  I2C_AcknowledgeConfig(I2C1, DISABLE);
  
  /* Send STOP Condition */
  I2C_GenerateSTOP(I2C1, ENABLE);  
  
  return 0;
}

