#include <stdint.h>
#include "ti_msp_dl_config.h"
#include "LED_RGB.h"
#include "KEY.h"
#include "drv_oled.h"
#include "TIME.h"
#include "EXTI.h"
#include "PWM.h"
#include "SERVO.h"
#include "beep.h"
#include "key.h"
#include "jy62.h"
#include "lora.h"
#include "stdio.h"
#include "encoder.h"
#include "control.h"
#include "protocol.h"
#include "pid.h"
#include "openmv.h"
#include "bsp_mpu6050.h"

/*
串口0：jy62陀螺仪
串口1： LORA无线通信模块（野火上位机的发送接受也在里面）
串口3： openmv
mpu6050：MPU6050_Init()把这个函数初始化 根据我配置的引脚配置接线就可以
protocol：这个文件是野火上位机的协议文件
两个电机的四个引脚都开了中断4倍频 AC1 AC2是A电机的A相B相   BC1 BC2是B电机的A相B相 直接跟着引脚配置就可以用





*/
int16_t i;
int angle;
uint8_t key_num;
uint8_t str_buff1[64];
uint8_t str_buff2[64];
uint8_t str_buff3[64];
float Init_angle, Tg_angle;
uint8_t angle_flag;

int main(void)
{
	/* Power on GPIO, initialize pins as digital outputs */
	SYSCFG_DL_init();
//	oled_init();
//	TIMER_Init();
//	EXTI_Init();
//	PWM_Init();
//	jy62_Init();
//	LORA_Init();
//	Openmv_Init();
//	protocol_init();
//	PID_param_init();
//	MPU6050_Init();
	
//	set_motor_enable();
//	set_motor2_enable();
//	BEEP_Init();

	while (1)
	{
		DL_GPIO_setPins(GPIOA, DL_GPIO_PIN_14);
		// key_num = Key_GetNum();
		// if(key_num ==2)
		// {
		//			//走固定距离100cm
		//					Car_go(100);

		// 设定目标角度
		//		Init_angle = Yaw;
		//		Tg_angle = Init_angle +90;
		//		set_pid_target(&pid_turn, Tg_angle);
		//		angle_flag = 1;
		//		set_pid_target(&pid_turn_speed, 160);

		// }
		//		receiving_process();//野火上位机接受处理数据调试pid时解除注释
		// display_6_8_number_f1(5,5,Yaw);
		// display_6_8_number_f1(5,1,Tg_angle);
		//
	}
}

/*定时器2中断服务函数，配置为1s的周期*/
void TIMER_0_INST_IRQHandler(void)
{
	switch(DL_TimerG_getPendingInterrupt(TIMER_0_INST))
	{
		case DL_TIMER_IIDX_ZERO:
		{
			DL_GPIO_togglePins(GPIOA,DL_GPIO_PIN_14);
		}break;
		
		default:break;
	}
}
