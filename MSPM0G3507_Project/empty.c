/*
 * Copyright (c) 2021, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
//#include "board.h"
#include <stdio.h>
#include "bsp_tb6612.h"
#include "encorder.h"
#include "usart.h"

	char str[] = "hello\r\n";

int main(void)
{
    //�������ʼ��
    board_init();
		SYSCFG_DL_init();
		NVIC_EnableIRQ(Encoder_INT_IRQN);//ʹ���ⲿ�ж�
		//�����ʱ���жϱ�־
    NVIC_ClearPendingIRQ(TIMER_1_INST_INT_IRQN);

	//��ʱ��A��ʼ����
	DL_TimerA_startCounter(TIMER_1_INST);
	    //ʹ�ܶ�ʱ���ж�
    NVIC_EnableIRQ(TIMER_1_INST_INT_IRQN);
	
	

	while(1)
	{


		//uart0_send_char(1);
//		for(int i = 200; i <= 400; i+=100)
//		{
		//	AO_Control(1,200); // A�˵����ת �ٶ����1000��
		//	BO_Control(1, 200);
//			delay_ms(500);
//			speed1=encorder_get_speed1();
//		}
//		for(int j = 400; j >= 200; j-=100)
//		{
//			AO_Control(0, j); // A�˵����ת �ٶ����1000��
//			BO_Control(0, j);
//			delay_ms(500);
//		}
		        /* ÿ�λ�ȡ�����ֵ�����㣬��ɻ����ִ������Ϊ��λ���ٶ�ֵ */

//        delay_ms(40);
}
	}
		

/*---------------------------*/
float  Target_ChaSu;		//Ŀ�����
float Motor1_Target_Speed;	//��ߵ��Ŀ���ٶ�
float Motor2_Target_Speed;	//�ұߵ��Ŀ���ٶ�
	/*---------------------------------------------------------------------------------------*/
/*------------------------------��ʱ��A1��1ms�жϷ�����------------------------------------*/
/*-------------------------------------------------------------------------------------------*/
void TIMER_1_INST_IRQHandler(void)//��ʱ���жϷ�����
{
	static uint16_t count_10ms=0;
	static uint16_t count_100ms=0;
	static uint16_t t=0;
	
	switch (DL_TimerA_getPendingInterrupt(TIMER_1_INST)) 
	{
		 case DL_TIMERA_IIDX_ZERO:
//		 		 usart0_send_string(str);
//			 if(++count_10ms>=10)//��ʱ10ms
//			 {count_10ms=0;

				 
				 //-------------------------------PID��������---------------------------------//
				Motor1_Speed =11;
//				 MEASURE_MOTORS_SPEED();//��������ٶ�
					printf("%f",Motor1_Speed);
//				uart0_send_char(1); 
			 
			 //�ϴ��������ݣ�û�õ���

		break;
		 default:break;
	 }
}









