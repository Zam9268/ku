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
#include "oled.h"

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
float Init_angle,Tg_angle;
uint8_t angle_flag;

int main(void)
{
    /* Power on GPIO, initialize pins as digital outputs */
  SYSCFG_DL_init();
	OLED_Init();
	TIMER_Init();
	EXTI_Init();
	PWM_Init();
	jy62_Init();
	LORA_Init();
	Openmv_Init();
	protocol_init();
	PID_param_init();
//	MPU6050_Init();
	DL_GPIO_setPins(GPIOA,DL_GPIO_PIN_0);
	set_motor_enable();
	set_motor2_enable();
//	BEEP_Init();	

   while (1) 
	{             
//		key_num = Key_GetNum();
//		if(key_num ==2)
//		{			
//			//走固定距离100cm
//					Car_go(100);
			
			
				//设定目标角度
		//Init_angle = Yaw;
		Init_angle = -90;
		Tg_angle = Init_angle +90;
		set_pid_target(&pid_turn, Tg_angle); 
		angle_flag = 1;
	set_pid_target(&pid_turn_speed, 200);
//		set_pid_target(&pid_turn,200);


//		}
//		receiving_process();//野火上位机接受处理数据调试pid时解除注释
//		display_6_8_number_f1(5,5,Yaw);
//		display_6_8_number_f1(5,1,Tg_angle);
			DL_GPIO_setPins(GPIOB, DL_GPIO_PIN_22 | DL_GPIO_PIN_26);
//			MotorOutput(1500,1500);
			
			OLED_ShowString(100,0*16,"abc",OLED_8X16);
			OLED_ShowString(100,1*16,"abc",OLED_8X16);
			OLED_ShowString(100,2*16,"abc",OLED_8X16);
			OLED_ShowString(100,3*16,"abc",OLED_8X16);
		//	OLED_ShowNum(2,1,250,4,OLED_8X16);
			OLED_Update(); 
//long a,b;

	OLED_ShowFloatNum(0, 1*16, pid_location.target_val, 4, 4, OLED_8X16);//编码器测试
	OLED_ShowFloatNum(0, 2*16, pid_location.actual_val, 4, 4, OLED_8X16);
	OLED_ShowFloatNum(0, 3*16, pid_location.err, 4, 4, OLED_8X16);
		//OLED_ShowNum(2,1, g_lMotorPulseSigma,4, OLED_8X16);//g_lMotorPulseSigma
		//	OLED_ShowNum(2,31, a,4, OLED_8X16);
		//	OLED_ShowNum(2,47, b,4, OLED_8X16);
    }
}
