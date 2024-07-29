#include "ti_msp_dl_config.h"
#include "KEY.h"
#include "beep.h"
#include "control.h"
#include "encoder.h"
#include "protocol.h"


extern uint8_t angle_flag;
extern float Tg_angle;
int32_t actual_speed1;

float MotorPWM,Motor2PWM;
uint8_t Key1Num,Key2Num,Key3Num,Key4Num;	

int16_t down_num;

void Motor1_Get_Speed(void);


void TIMER_Init(void)
{
	NVIC_EnableIRQ(TIMG0_INT_IRQn);
	DL_TimerG_startCounter(TIMG0);
	
	NVIC_EnableIRQ(TIMG6_INT_IRQn);
	DL_TimerG_startCounter(TIMG6);

}

void TIMG0_IRQHandler(void)
{

	DL_GPIO_togglePins(GPIOB, DL_GPIO_PIN_22 | DL_GPIO_PIN_26);
}

void TIMER_1_INST_IRQHandler(void)
{		
	
	
	Setmotopulse();
	
	
	
	//调试速度环
			if(is_motor_en == 1)
		{
			MotorPWM = speed_pid_control();
		}			
		 if(is_motor2_en == 1) 
		 {
			 Motor2PWM  = speed2_pid_control();
		 }
		 MotorOutput(MotorPWM,Motor2PWM);

		
	//调试位置速度串级pid
//		 if(is_motor_en == 1 && is_motor2_en == 1)
//		 {
//			 Location_Speed_control();
//			 MotorPWM = speed_Outval;  
//			 Motor2PWM = speed2_Outval;
//			 MotorOutput(MotorPWM,Motor2PWM);
//		 }


//调试角度速度串级pid
//	if(angle_flag ==1)
//	{

//		 if(is_motor_en == 1 && is_motor2_en == 1)
//		 {
//			 Turn_Angle_Speed_control();
//			 MotorPWM = speed3_Outval;  
//			 Motor2PWM = speed4_Outval;
//			 MotorOutput(MotorPWM,Motor2PWM);
//		 }
//	 }

//	if(angle_flag ==1)
//	{

//		 if(is_motor_en == 1 && is_motor2_en == 1)
//		 {
//			 lind_Turn_Speed_control();
//			 MotorPWM = speed3_Outval;  
//			 Motor2PWM = speed4_Outval;
//			 MotorOutput(MotorPWM,Motor2PWM);
//		 }
//	 }


}

