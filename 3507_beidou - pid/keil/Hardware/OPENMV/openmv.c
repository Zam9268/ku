#include "ti_msp_dl_config.h"
#include "openmv.h"
#include <stdint.h>
#include "stdio.h"

int GetOpenmvDataCount  = 0;

uint16_t corner_site[4][2]={0};
uint8_t line_err;
unsigned char sendBuf[4];

//openmv��ʼ��
void Openmv_Init(void)
{
	  NVIC_ClearPendingIRQ(UART_2_INST_INT_IRQN);
		NVIC_EnableIRQ(UART_2_INST_INT_IRQN);
		DL_UART_clearInterruptStatus(UART_2_INST,DL_UART_INTERRUPT_RX);//����жϱ�־λ

}

//openmv���ڽ��շ�����
void UART_2_INST_IRQHandler(void)
{
		  uint8_t i_UartReceiveData;
    i_UartReceiveData = DL_UART_receiveData(UART_2_INST);

	
		Openmv_Receive_Data(i_UartReceiveData);
}



void Openmv_Receive_Data(uint8_t com_data)
{
		uint8_t i;
		static uint8_t RxCounter1=0;//����
		static uint16_t RxBuffer1[10]={0};   //һ������յ�һ�����õ�����
		static uint8_t RxState = 0;	
		static uint8_t RxFlag1 = 0;
		

	if(RxState==0&&com_data==0x1A)  //0x1A֡ͷ 
	{
//			LED2_TOGGLE   

		RxState=1;
		RxBuffer1[RxCounter1++]=com_data;   //һ������£�RxBuffer1[0] ��š�<bbhhhhhb��,Ȼ��RxBuffer1[1]�ŵľ���0x1A
	}

	else if(RxState==1&&com_data==0x2B)  //0x2B֡ͷ
	{
		RxState=2;
		RxBuffer1[RxCounter1++]=com_data;
	}
	
	else if(RxState==2)
	{
		 
		RxBuffer1[RxCounter1++]=com_data;
		if(RxCounter1>=7||com_data == 0x3C)       //RxBuffer1��������,�������ݽ���
		{
			RxState=3;
			RxFlag1=1;
			line_err =  RxBuffer1[RxCounter1-2]; 
			
			
		}
	}

	else if(RxState==3)		//����Ƿ���ܵ�������־
	{
			if(RxBuffer1[RxCounter1-1] == 0x3C)
			{
						
						RxFlag1 = 0;
						RxCounter1 = 0;
						RxState = 0;
					
			}
			else   //���մ���
			{
						RxState = 0;
						RxCounter1=0;
						for(i=0;i<10;i++)
						{
								RxBuffer1[i]=0x00;      //�����������������
						}
			}
	} 

	else   //�����쳣
	{
			RxState = 0;
			RxCounter1=0;
			for(i=0;i<10;i++)
			{
					RxBuffer1[i]=0x00;      //�����������������
			}
	}
	
	
	}

void SendDataToOpenmv(void)
{
	uint8_t i;
		for(i = 0; i <= 4; i++)   
		{
			sprintf((char *)sendBuf, "*%d", line_err);
			DL_UART_Main_transmitDataBlocking(UART_1_INST, sendBuf[i]);
		}

}