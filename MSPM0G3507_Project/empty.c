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
    //开发板初始化
    board_init();
		SYSCFG_DL_init();
		NVIC_EnableIRQ(Encoder_INT_IRQN);//使能外部中断
		//清除定时器中断标志
    NVIC_ClearPendingIRQ(TIMER_1_INST_INT_IRQN);

	//定时器A开始计数
	DL_TimerA_startCounter(TIMER_1_INST);
	    //使能定时器中断
    NVIC_EnableIRQ(TIMER_1_INST_INT_IRQN);
	
	

	while(1)
	{


		//uart0_send_char(1);
//		for(int i = 200; i <= 400; i+=100)
//		{
		//	AO_Control(1,200); // A端电机正转 速度最大1000；
		//	BO_Control(1, 200);
//			delay_ms(500);
//			speed1=encorder_get_speed1();
//		}
//		for(int j = 400; j >= 200; j-=100)
//		{
//			AO_Control(0, j); // A端电机反转 速度最大1000；
//			BO_Control(0, j);
//			delay_ms(500);
//		}
		        /* 每次获取完计数值后清零，则可获得以执行周期为单位的速度值 */

//        delay_ms(40);
}
	}
		

/*---------------------------*/
float  Target_ChaSu;		//目标差速
float Motor1_Target_Speed;	//左边电机目标速度
float Motor2_Target_Speed;	//右边电机目标速度
	/*---------------------------------------------------------------------------------------*/
/*------------------------------定时器A1的1ms中断服务函数------------------------------------*/
/*-------------------------------------------------------------------------------------------*/
void TIMER_1_INST_IRQHandler(void)//定时器中断服务函数
{
	static uint16_t count_10ms=0;
	static uint16_t count_100ms=0;
	static uint16_t t=0;
	
	switch (DL_TimerA_getPendingInterrupt(TIMER_1_INST)) 
	{
		 case DL_TIMERA_IIDX_ZERO:
//		 		 usart0_send_string(str);
//			 if(++count_10ms>=10)//定时10ms
//			 {count_10ms=0;

				 
				 //-------------------------------PID处理数据---------------------------------//
				Motor1_Speed =11;
//				 MEASURE_MOTORS_SPEED();//测量电机速度
					printf("%f",Motor1_Speed);
//				uart0_send_char(1); 
			 
			 //上传波形数据（没用到）

		break;
		 default:break;
	 }
}









