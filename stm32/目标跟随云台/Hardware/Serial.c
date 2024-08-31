#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>

uint8_t x;
        
                           
void Serial_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	//USART1_RX	  PA10
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode =USART_Mode_Rx;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &USART_InitStructure);
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_Cmd(USART1, ENABLE);
}

void USART1_IRQHandler(void)			 
{
		u8 com_data; 
		u8 i;
		static u8 RxCounter1=0;
		static u16 RxBuffer1[4]={0};
		static u8 RxState = 0;	
//		  com_data 用于读取STM32串口收到的数据，这个数据会被下一个数据掩盖，所以要将它用一个数组储存起来。

//        RxBuffer1[4]={0} 定义一个4个成员的数组，可以存放4个数据，刚好放下一个数据包。

//        RxCounter1 用来计次，让RxBufeer1这个数组能依次存入数据包。

//        RxState 接收状态，判断程序应该接收第一个帧头、第二个帧头、数据或帧尾。

//        com_data = USART_ReceiveData(USART1); 读取 将串口接收到的数据。
		
		
 
		if( USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)  	   //接收中断  
		{
			
				USART_ClearITPendingBit(USART1,USART_IT_RXNE);   //清除中断标志
				com_data = USART_ReceiveData(USART1);
				if(RxState==0&&com_data==0x2C)  //0x2c帧头
				{
					
					RxState=1;
					RxBuffer1[RxCounter1++]=com_data;
				}
		
				else if(RxState==1&&com_data==0x12)  //0x12帧头
				{
					RxState=2;
					RxBuffer1[RxCounter1++]=com_data;
				}
		
				else if(RxState==2)
				{
					RxBuffer1[RxCounter1++]=com_data;
 
					if(RxCounter1==4 && com_data == 0x5B)       //RxBuffer1接受满了,接收数据结束
					{
						
						x=RxBuffer1[RxCounter1-2];
						RxCounter1 = 0;
						RxState = 0;	
					}
					else if(RxCounter1 > 4)            //接收异常
					{
						RxState = 0;
						RxCounter1=0;
						for(i=0;i<4;i++)
						{
								RxBuffer1[i]=0x00;      //将存放数据数组清零
						}
					
					}
				}
				else   //接收异常
				{
						RxState = 0;
						RxCounter1=0;
						for(i=0;i<4;i++)
						{
								RxBuffer1[i]=0x00;      //将存放数据数组清零
						}
				}
 
		}
		
}
