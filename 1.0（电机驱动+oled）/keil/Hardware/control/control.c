#include "ti_msp_dl_config.h"
#include "control.h"
#include "pid.h"
#include "encoder.h"
#include "jy62.h"
#include "protocol.h"
#include "stdio.h"
#include "openmv.h"


AngleData yaw;

//float  MotorPWM =0.0, Motor2PWM =0.0;
uint8_t is_motor_en = 0, is_motor2_en = 0;            // 电机使能
unsigned char location_control_count = 0;  //执行频率不需要那么高的用这个事件计数，用在中断中
unsigned char turn_control_count = 0;  //执行频率不需要那么高的用这个事件计数，用在中断中
float speed_Outval, location_Outval;
float speed2_Outval, location2_Outval;
float speed3_Outval, turn_Outval;
float speed4_Outval;
static uint16_t    dutyfactor = 0;             // 记录电机占空比
static motor_dir_t direction  = MOTOR_FWD;     // 记录电机方向
//static uint16_t    dutyfactor = 0;             // 记录电机占空比
static motor_dir_t direction2  = MOTOR_FWD;     // 记录电机2方向
static uint16_t    dutyfactor2 = 0;             // 记录电机2占空比
float g_fTargetJourney = 0;  //存放小车左右轮所走路程和 ， 单位cm，需要在下一阶段任务中设置


/**
 * @brief 绝对值函数
 * @param  处理值
 * @retval  |p|
 **/
int myAbs(int p)
{
	int q;
	q = p > 0 ? p : (-p);
	return q;
}


/**
 * @brief 直立环（位置式）
 * @note 调节到超调后乘以0.6后引入速度环
 * @param  期望角度 真实角度 真实角速度
 * @retval  直立环输出
 **/
int verticalPid(float Med_Angle, float Now_Angle, float gyro_y)
{
	int PWM_OUT;
	PWM_OUT = Vertical_Kp * (Now_Angle - Med_Angle) + Vertical_Kd * (gyro_y);
	return PWM_OUT;
}

/**
 * @brief 速度环（位置式）
 * @note kp = 1/200 ki
 * @param  期望速度 真实速度
 * @retval  速度环输出
 **/
int velocityPid(int Target_Speed, int Now_Speed)
{
	static int Speed_Sum,		  //速度积分
		Speed_Error,			  //速度偏差
		Speed_Error_Lowpass,	  //速度低通滤波值
		Speed_Error_Lowpass_Last, //上次速度低通滤波值
		Speed_Pwm_Out;			  //速度环输出

	float a = 0.7;

	Speed_Error = Now_Speed - Target_Speed;

	Speed_Error_Lowpass = (1 - a) * Speed_Error + a * Speed_Error_Lowpass_Last;
	Speed_Error_Lowpass_Last = Speed_Error_Lowpass;

	Speed_Sum += Speed_Error_Lowpass;
	Speed_Sum = Speed_Sum > 10000 ? 10000 : (Speed_Sum < (-10000) ? (-10000) : Speed_Sum);

	Speed_Pwm_Out = velocityKp * Speed_Error_Lowpass + velocityKi * Speed_Sum;

	return Speed_Pwm_Out;
}





/**
 * @brief 循迹PID
 * @param 当前车身角度；目标车身角度
 * @retval PWM
 */
int linePid(int rho, int Taget_rho)
{
	static float PWM_out, error;
	static float last_error = 0, error_int = 0;

	error = rho - Taget_rho;

	PWM_out = lineKp * error + lineKd * (error - last_error);

	last_error = error;
	error_int += error;

	return PWM_out;
}



/**
 * @brief 主控制函数
 * @param None
 * @retval None
 **/
void mainControl(void)
{

	
}


//位置速度串级pid  位置外环的输入是速度内环的输入
void Location_Speed_control(void)          
{
			 if (is_motor_en == 1 || is_motor2_en == 1)     // 电机在使能状态下才进行控制处理
			 {
					 location_control_count++;
				  if(location_control_count >= 2)
					{
						location_control_count = 0; 
						//外环输出
						location_Outval = location_pid_control();
						location2_Outval = location2_pid_control();
					}
					//将外环输入给到内环速度
					set_pid_target(&pid_speed, location_Outval); //每次都必须有位置环的值    
					set_pid_target(&pid_speed2, location2_Outval); //每次都必须有位置环的值
				 //内环速度输出给到电机
           speed_Outval = speed_pid_control();    
					 speed2_Outval = speed2_pid_control();  
				}

}
//角度速度串级pid  角度外环的输出给到速度内环
void Turn_Angle_Speed_control(void)          
{
			 if (is_motor_en == 1 || is_motor2_en == 1)     // 电机在使能状态下才进行控制处理
			 {

					 turn_control_count++;
				  if(turn_control_count >= 2)
					{
						turn_control_count = 0; 
						//角度外环输出 输出一个值就可以给速度内环一正一负就可以实现转向
						turn_Outval = turn_angle_pid_control();
					}
				//	内环值给到内环速度
					set_pid_target(&pid_speed, turn_Outval); 
					set_pid_target(&pid_speed2, -turn_Outval); 
           speed3_Outval = speed_pid_control();   
					 speed4_Outval = speed2_pid_control();  
				}

}

//巡线串级pid
void lind_Turn_Speed_control(void)          
{
			 if (is_motor_en == 1 || is_motor2_en == 1)     // 电机在使能状态下才进行控制处理
			 {

					 turn_control_count++;
				  if(turn_control_count >= 2)
					{
						turn_control_count = 0; 
						
						turn_Outval = turn_speed_pid_control();
					}
					//这个的100是基础的速度加减turn_Outval实现差速
					set_pid_target(&pid_speed, 100-turn_Outval); 
					set_pid_target(&pid_speed2, 100+turn_Outval); 
           speed3_Outval = speed_pid_control();   
					 speed4_Outval = speed2_pid_control();  
				}

}


float location_pid_control(void)  
{
	float cont_val = 0.0; 
	int32_t actual_location;
	
	
	  actual_location =  g_lMotorPulseSigma;   //1圈 = 1456个脉冲 = 28*13*4  。

    cont_val = location_pid_realize(&pid_location, actual_location);   
	  
	    
     	/* 目标速度上限处理 */
      if (cont_val > TARGET_SPEED_MAX)
      {
        cont_val = TARGET_SPEED_MAX;
      }
      else if (cont_val < -TARGET_SPEED_MAX)
      {
        cont_val = -TARGET_SPEED_MAX;
      }

//		#if defined(PID_ASSISTANT_EN)
//    set_computer_value(SEND_FACT_CMD, CURVES_CH1, &actual_location, 1);                // 给通道 1 发送实际值
//  #endif

	return cont_val;
}
float speed_pid_control(void)  
{
   
    float cont_val = 0.0;                       // 当前控制值
    int32_t actual_speed;
	
	  actual_speed = (((float)g_nMotorPulse*1000.0*60.0)/(ENCODER_TOTAL_RESOLUTION*REDUCTION_RATIO*SPEED_PID_PERIOD));
    cont_val =  speed_pid_realize(&pid_speed, actual_speed);    // 进行 PID 计算
	
//  #if defined(PID_ASSISTANT_EN)
//    set_computer_value(SEND_FACT_CMD, CURVES_CH1, &actual_speed, 1);                // 给通道 1 发送实际值
//	
//  #endif
	
	return cont_val;
}


float location2_pid_control(void)  
{
	float cont_val = 0.0; 
	int32_t actual_location;
	
	  actual_location =  g_lMotor2PulseSigma;   

    cont_val = location_pid_realize(&pid_location2, actual_location);   
	  
	
	//目标速度限幅
	    	/* 目标速度上限处理 */
      if (cont_val > TARGET_SPEED_MAX)
      {
        cont_val = TARGET_SPEED_MAX;
      }
      else if (cont_val < -TARGET_SPEED_MAX)
      {
        cont_val = -TARGET_SPEED_MAX;
      }
	
	
//	  #if defined(PID_ASSISTANT_EN)
//    set_computer_value(SEND_FACT_CMD, CURVES_CH1, &actual_location, 1);                // 给通道 1 发送实际值
//  #endif
	
	return cont_val;
}


float speed2_pid_control(void)  
{
   
    float cont_val = 0.0;                       // 当前控制值
    int32_t actual_speed;    
	
	  actual_speed = ((float)g_nMotor2Pulse*1000.0*60.0)/(ENCODER_TOTAL_RESOLUTION*REDUCTION_RATIO*SPEED_PID_PERIOD);

	
    cont_val = speed_pid_realize(&pid_speed2, actual_speed);    // 进行 PID 计算
//    
//  #if defined(PID_ASSISTANT_EN)
//    set_computer_value(SEND_FACT_CMD, CURVES_CH1, &actual_speed, 1);                // 给通道 1 发送实际值
//  #else
////    printf("实际值：%d. 目标值：%.0f\n", actual_speed, get_pid_target());      // 打印实际值和目标值
//  #endif
	
	return cont_val;
	
}

float turn_angle_pid_control(void)  
{
	float cont_val = 0.0; 
	int32_t actual_angle;
	

	  actual_angle = Yaw;  

    cont_val = turn_pid_realize(&pid_turn, actual_angle);   
	  
	    
     	/* 目标速度上限处理 */
      if (cont_val > TARGET_SPEED_MAX)
      {
        cont_val = TARGET_SPEED_MAX;
      }
      else if (cont_val < -TARGET_SPEED_MAX)
      {
        cont_val = -TARGET_SPEED_MAX;
      }

	
	return cont_val;
}

float turn_speed_pid_control(void)  
{
   
    float cont_val = 0.0;                       // 当前控制值
    int32_t actual_speed;    
	//这里的实际值我给的是openmv巡线的值 如果需要红外传感器巡线可以把传感器的值送进去
	  actual_speed = line_err;

	
    cont_val = turn_speed_pid_realize(&pid_turn_speed, actual_speed);    // 进行 PID 计算
    
	
	return cont_val;
	
}





/*****************电机的控制函数***************/

void MotorOutput(int nMotorPwm,int nMotor2Pwm)//
{
		if (nMotorPwm >= 0)    // 判断电机方向         
		{
			direction =MOTOR_FWD;
		//AIN1  AIN2根据自己引脚改就可以  方向不对的话取反
		DL_GPIO_setPins(GPIOA, PORTA_AIN1_PIN);
		DL_GPIO_clearPins(GPIOB, PORTA_AIN2_PIN);
		}
		else
		{
			nMotorPwm = -nMotorPwm;
			direction = MOTOR_REV;
			DL_GPIO_clearPins(GPIOA, PORTA_AIN1_PIN);
			DL_GPIO_setPins(GPIOB, PORTA_AIN2_PIN);


		}
		nMotorPwm = (nMotorPwm > PWM_MAX_PERIOD_COUNT) ? PWM_MAX_PERIOD_COUNT : nMotorPwm;    // 速度上限处理
		
		
		if (nMotor2Pwm >= 0)    // 判断电机方向         
		{
			direction2 =MOTOR_FWD;

		//BIN1  BIN2根据自己引脚改就可以  方向不对的话取反

		DL_GPIO_clearPins(GPIOA, PORTA_BIN1_PIN);
		DL_GPIO_setPins(GPIOA, PORTA_BIN2_PIN);
		}
		else
		{
			nMotor2Pwm = -nMotor2Pwm;
						direction2 =MOTOR_REV;


		DL_GPIO_clearPins(GPIOA, PORTA_BIN2_PIN);
		DL_GPIO_setPins(GPIOA, PORTA_BIN1_PIN);
		}
		
		nMotor2Pwm = (nMotor2Pwm > PWM_MAX_PERIOD_COUNT) ? PWM_MAX_PERIOD_COUNT : nMotor2Pwm;    // 速度上限处理
		
		set_motor_speed(nMotorPwm);        // 设置 PWM 占空比
		set_motor2_speed(nMotor2Pwm);      // 设置 PWM 占空比
 }

 void set_motor_speed(uint16_t v)    
{ 
	//PWMA
	dutyfactor = v;
	DL_TimerG_setCaptureCompareValue(PWM_0_INST, dutyfactor, GPIO_PWM_0_C0_IDX);
}



/**
  * @brief  使能电机
  * @param  无
  * @retval 无
  */
void set_motor_enable(void)   //这俩个使能和禁用的函数对于双极性控制来说还有效吗？
{
	is_motor_en  = 1;
  MOTOR_ENABLE();
}

/*****************电机2的控制函数***************/
/**
  * @brief  设置电机2速度
  * @param  v: 速度（占空比）
  * @retval 无
  */
void set_motor2_speed(uint16_t v)
{
	//PWMB
		dutyfactor2 = v;  
		DL_TimerG_setCaptureCompareValue(PWM_0_INST, dutyfactor2, GPIO_PWM_0_C1_IDX);


}


/**
  * @brief  使能电机2
  * @param  无
  * @retval 无
  */
void set_motor2_enable(void)
{
	is_motor2_en  = 1;
  MOTOR_ENABLE();
}

/**
  * @brief  禁用电机2
  * @param  无
  * @retval 无
  */
void set_motor2_disable(void)
{
	is_motor2_en  = 0;
//  MOTOR_DISABLE();
}


//另一种思路控制小车转向通过计算电机走过的脉冲值控制电机转固定距离实现转90度180度
void spin_Turn(spin_dir_t zhuanxiang)   //传入小车的轮距(mm) 143mm  
{
		float spin90_val;
		float Car_Turn_val;
		spin90_val = 0.25*3.1416*LUN_JU;
		
		if(zhuanxiang == left_90)  
		{
			Car_Turn_val = ( spin90_val / (6.5 * 3.142) ) *   (28*4*13) ; 
			Car_Turn_val = 0.99* Car_Turn_val;   //90*0.94 = 84.6   //惯性影响，导致转弯比理论设定的多。
			
		}
		else if(zhuanxiang == right_90)  
		{
			Car_Turn_val = -(spin90_val / (6.5 * 3.142) ) *   (28*4*13); 
			Car_Turn_val = 0.99 * Car_Turn_val;  //90*0.96 = 86.4    //惯性影响，导致转弯比理论设定的多。 
		}
		else if(zhuanxiang == back_180)
		{
			Car_Turn_val = -(spin90_val / (6.5 * 3.142) ) *   (28*4*13);
			Car_Turn_val = 0.99 * Car_Turn_val;   //同理
			Car_Turn_val = 2*Car_Turn_val;      //
		}
		
			set_pid_target(&pid_location, -Car_Turn_val);   
			set_pid_target(&pid_location2, Car_Turn_val);
		
			g_lMotorPulseSigma = 0;    
			g_lMotor2PulseSigma = 0; 
		
			set_motor_enable();   //使能电机控制PWM输出    
		  set_motor2_enable();   //使能电机2控制PWM输出

}


//将要走的距离转化为电机脉冲数用位置速度环精准控制
void Car_go(int32_t location_cm)   //直走函数     /
{
	float Car_location;
	
	g_fTargetJourney = location_cm;   //防止长时间PID控制用
	
	
	Car_location   = ( location_cm / (6.5 * 3.14) ) *   (28*4*13) ;   //Car_location 将  location_cm 转换为对应的脉冲数  
											//后面括号是电机减速比倍频分辨率，改成自己电机的参数
	
	  set_pid_target(&pid_location, Car_location);   
	  set_pid_target(&pid_location2, Car_location);
	
	  set_motor_enable();   //使能电机控制PWM输出    
    set_motor2_enable();   //使能电机2控制PWM输出
	 
	  g_lMotorPulseSigma = 0;    
	  g_lMotor2PulseSigma = 0; 
	
		
}


