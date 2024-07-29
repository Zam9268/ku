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
uint8_t is_motor_en = 0, is_motor2_en = 0;            // ���ʹ��
unsigned char location_control_count = 0;  //ִ��Ƶ�ʲ���Ҫ��ô�ߵ�������¼������������ж���
unsigned char turn_control_count = 0;  //ִ��Ƶ�ʲ���Ҫ��ô�ߵ�������¼������������ж���
float speed_Outval, location_Outval;
float speed2_Outval, location2_Outval;
float speed3_Outval, turn_Outval;
float speed4_Outval;
static uint16_t    dutyfactor = 0;             // ��¼���ռ�ձ�
static motor_dir_t direction  = MOTOR_FWD;     // ��¼�������
//static uint16_t    dutyfactor = 0;             // ��¼���ռ�ձ�
static motor_dir_t direction2  = MOTOR_FWD;     // ��¼���2����
static uint16_t    dutyfactor2 = 0;             // ��¼���2ռ�ձ�
float g_fTargetJourney = 0;  //���С������������·�̺� �� ��λcm����Ҫ����һ�׶�����������


/**
 * @brief ����ֵ����
 * @param  ����ֵ
 * @retval  |p|
 **/
int myAbs(int p)
{
	int q;
	q = p > 0 ? p : (-p);
	return q;
}


/**
 * @brief ֱ������λ��ʽ��
 * @note ���ڵ����������0.6�������ٶȻ�
 * @param  �����Ƕ� ��ʵ�Ƕ� ��ʵ���ٶ�
 * @retval  ֱ�������
 **/
int verticalPid(float Med_Angle, float Now_Angle, float gyro_y)
{
	int PWM_OUT;
	PWM_OUT = Vertical_Kp * (Now_Angle - Med_Angle) + Vertical_Kd * (gyro_y);
	return PWM_OUT;
}

/**
 * @brief �ٶȻ���λ��ʽ��
 * @note kp = 1/200 ki
 * @param  �����ٶ� ��ʵ�ٶ�
 * @retval  �ٶȻ����
 **/
int velocityPid(int Target_Speed, int Now_Speed)
{
	static int Speed_Sum,		  //�ٶȻ���
		Speed_Error,			  //�ٶ�ƫ��
		Speed_Error_Lowpass,	  //�ٶȵ�ͨ�˲�ֵ
		Speed_Error_Lowpass_Last, //�ϴ��ٶȵ�ͨ�˲�ֵ
		Speed_Pwm_Out;			  //�ٶȻ����

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
 * @brief ѭ��PID
 * @param ��ǰ����Ƕȣ�Ŀ�공��Ƕ�
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
 * @brief �����ƺ���
 * @param None
 * @retval None
 **/
void mainControl(void)
{

	
}


//λ���ٶȴ���pid  λ���⻷���������ٶ��ڻ�������
void Location_Speed_control(void)          
{
			 if (is_motor_en == 1 || is_motor2_en == 1)     // �����ʹ��״̬�²Ž��п��ƴ���
			 {
					 location_control_count++;
				  if(location_control_count >= 2)
					{
						location_control_count = 0; 
						//�⻷���
						location_Outval = location_pid_control();
						location2_Outval = location2_pid_control();
					}
					//���⻷��������ڻ��ٶ�
					set_pid_target(&pid_speed, location_Outval); //ÿ�ζ�������λ�û���ֵ    
					set_pid_target(&pid_speed2, location2_Outval); //ÿ�ζ�������λ�û���ֵ
				 //�ڻ��ٶ�����������
           speed_Outval = speed_pid_control();    
					 speed2_Outval = speed2_pid_control();  
				}

}
//�Ƕ��ٶȴ���pid  �Ƕ��⻷����������ٶ��ڻ�
void Turn_Angle_Speed_control(void)          
{
			 if (is_motor_en == 1 || is_motor2_en == 1)     // �����ʹ��״̬�²Ž��п��ƴ���
			 {

					 turn_control_count++;
				  if(turn_control_count >= 2)
					{
						turn_control_count = 0; 
						//�Ƕ��⻷��� ���һ��ֵ�Ϳ��Ը��ٶ��ڻ�һ��һ���Ϳ���ʵ��ת��
						turn_Outval = turn_angle_pid_control();
					}
				//	�ڻ�ֵ�����ڻ��ٶ�
					set_pid_target(&pid_speed, turn_Outval); 
					set_pid_target(&pid_speed2, -turn_Outval); 
           speed3_Outval = speed_pid_control();   
					 speed4_Outval = speed2_pid_control();  
				}

}

//Ѳ�ߴ���pid
void lind_Turn_Speed_control(void)          
{
			 if (is_motor_en == 1 || is_motor2_en == 1)     // �����ʹ��״̬�²Ž��п��ƴ���
			 {

					 turn_control_count++;
				  if(turn_control_count >= 2)
					{
						turn_control_count = 0; 
						
						turn_Outval = turn_speed_pid_control();
					}
					//�����100�ǻ������ٶȼӼ�turn_Outvalʵ�ֲ���
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
	
	
	  actual_location =  g_lMotorPulseSigma;   //1Ȧ = 1456������ = 28*13*4  ��

    cont_val = location_pid_realize(&pid_location, actual_location);   
	  
	    
     	/* Ŀ���ٶ����޴��� */
      if (cont_val > TARGET_SPEED_MAX)
      {
        cont_val = TARGET_SPEED_MAX;
      }
      else if (cont_val < -TARGET_SPEED_MAX)
      {
        cont_val = -TARGET_SPEED_MAX;
      }

//		#if defined(PID_ASSISTANT_EN)
//    set_computer_value(SEND_FACT_CMD, CURVES_CH1, &actual_location, 1);                // ��ͨ�� 1 ����ʵ��ֵ
//  #endif

	return cont_val;
}
float speed_pid_control(void)  
{
   
    float cont_val = 0.0;                       // ��ǰ����ֵ
    int32_t actual_speed;
	
	  actual_speed = (((float)g_nMotorPulse*1000.0*60.0)/(ENCODER_TOTAL_RESOLUTION*REDUCTION_RATIO*SPEED_PID_PERIOD));
    cont_val =  speed_pid_realize(&pid_speed, actual_speed);    // ���� PID ����
	
//  #if defined(PID_ASSISTANT_EN)
//    set_computer_value(SEND_FACT_CMD, CURVES_CH1, &actual_speed, 1);                // ��ͨ�� 1 ����ʵ��ֵ
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
	  
	
	//Ŀ���ٶ��޷�
	    	/* Ŀ���ٶ����޴��� */
      if (cont_val > TARGET_SPEED_MAX)
      {
        cont_val = TARGET_SPEED_MAX;
      }
      else if (cont_val < -TARGET_SPEED_MAX)
      {
        cont_val = -TARGET_SPEED_MAX;
      }
	
	
//	  #if defined(PID_ASSISTANT_EN)
//    set_computer_value(SEND_FACT_CMD, CURVES_CH1, &actual_location, 1);                // ��ͨ�� 1 ����ʵ��ֵ
//  #endif
	
	return cont_val;
}


float speed2_pid_control(void)  
{
   
    float cont_val = 0.0;                       // ��ǰ����ֵ
    int32_t actual_speed;    
	
	  actual_speed = ((float)g_nMotor2Pulse*1000.0*60.0)/(ENCODER_TOTAL_RESOLUTION*REDUCTION_RATIO*SPEED_PID_PERIOD);

	
    cont_val = speed_pid_realize(&pid_speed2, actual_speed);    // ���� PID ����
//    
//  #if defined(PID_ASSISTANT_EN)
//    set_computer_value(SEND_FACT_CMD, CURVES_CH1, &actual_speed, 1);                // ��ͨ�� 1 ����ʵ��ֵ
//  #else
////    printf("ʵ��ֵ��%d. Ŀ��ֵ��%.0f\n", actual_speed, get_pid_target());      // ��ӡʵ��ֵ��Ŀ��ֵ
//  #endif
	
	return cont_val;
	
}

float turn_angle_pid_control(void)  
{
	float cont_val = 0.0; 
	int32_t actual_angle;
	

	  actual_angle = Yaw;  

    cont_val = turn_pid_realize(&pid_turn, actual_angle);   
	  
	    
     	/* Ŀ���ٶ����޴��� */
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
   
    float cont_val = 0.0;                       // ��ǰ����ֵ
    int32_t actual_speed;    
	//�����ʵ��ֵ�Ҹ�����openmvѲ�ߵ�ֵ �����Ҫ���⴫����Ѳ�߿��԰Ѵ�������ֵ�ͽ�ȥ
	  actual_speed = line_err;

	
    cont_val = turn_speed_pid_realize(&pid_turn_speed, actual_speed);    // ���� PID ����
    
	
	return cont_val;
	
}





/*****************����Ŀ��ƺ���***************/

void MotorOutput(int nMotorPwm,int nMotor2Pwm)//
{
		if (nMotorPwm >= 0)    // �жϵ������         
		{
			direction =MOTOR_FWD;
		//AIN1  AIN2�����Լ����ŸľͿ���  ���򲻶ԵĻ�ȡ��
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
		nMotorPwm = (nMotorPwm > PWM_MAX_PERIOD_COUNT) ? PWM_MAX_PERIOD_COUNT : nMotorPwm;    // �ٶ����޴���
		
		
		if (nMotor2Pwm >= 0)    // �жϵ������         
		{
			direction2 =MOTOR_FWD;

		//BIN1  BIN2�����Լ����ŸľͿ���  ���򲻶ԵĻ�ȡ��

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
		
		nMotor2Pwm = (nMotor2Pwm > PWM_MAX_PERIOD_COUNT) ? PWM_MAX_PERIOD_COUNT : nMotor2Pwm;    // �ٶ����޴���
		
		set_motor_speed(nMotorPwm);        // ���� PWM ռ�ձ�
		set_motor2_speed(nMotor2Pwm);      // ���� PWM ռ�ձ�
 }

 void set_motor_speed(uint16_t v)    
{ 
	//PWMA
	dutyfactor = v;
	DL_TimerG_setCaptureCompareValue(PWM_0_INST, dutyfactor, GPIO_PWM_0_C0_IDX);
}



/**
  * @brief  ʹ�ܵ��
  * @param  ��
  * @retval ��
  */
void set_motor_enable(void)   //������ʹ�ܺͽ��õĺ�������˫���Կ�����˵����Ч��
{
	is_motor_en  = 1;
  MOTOR_ENABLE();
}

/*****************���2�Ŀ��ƺ���***************/
/**
  * @brief  ���õ��2�ٶ�
  * @param  v: �ٶȣ�ռ�ձȣ�
  * @retval ��
  */
void set_motor2_speed(uint16_t v)
{
	//PWMB
		dutyfactor2 = v;  
		DL_TimerG_setCaptureCompareValue(PWM_0_INST, dutyfactor2, GPIO_PWM_0_C1_IDX);


}


/**
  * @brief  ʹ�ܵ��2
  * @param  ��
  * @retval ��
  */
void set_motor2_enable(void)
{
	is_motor2_en  = 1;
  MOTOR_ENABLE();
}

/**
  * @brief  ���õ��2
  * @param  ��
  * @retval ��
  */
void set_motor2_disable(void)
{
	is_motor2_en  = 0;
//  MOTOR_DISABLE();
}


//��һ��˼·����С��ת��ͨ���������߹�������ֵ���Ƶ��ת�̶�����ʵ��ת90��180��
void spin_Turn(spin_dir_t zhuanxiang)   //����С�����־�(mm) 143mm  
{
		float spin90_val;
		float Car_Turn_val;
		spin90_val = 0.25*3.1416*LUN_JU;
		
		if(zhuanxiang == left_90)  
		{
			Car_Turn_val = ( spin90_val / (6.5 * 3.142) ) *   (28*4*13) ; 
			Car_Turn_val = 0.99* Car_Turn_val;   //90*0.94 = 84.6   //����Ӱ�죬����ת��������趨�Ķࡣ
			
		}
		else if(zhuanxiang == right_90)  
		{
			Car_Turn_val = -(spin90_val / (6.5 * 3.142) ) *   (28*4*13); 
			Car_Turn_val = 0.99 * Car_Turn_val;  //90*0.96 = 86.4    //����Ӱ�죬����ת��������趨�Ķࡣ 
		}
		else if(zhuanxiang == back_180)
		{
			Car_Turn_val = -(spin90_val / (6.5 * 3.142) ) *   (28*4*13);
			Car_Turn_val = 0.99 * Car_Turn_val;   //ͬ��
			Car_Turn_val = 2*Car_Turn_val;      //
		}
		
			set_pid_target(&pid_location, -Car_Turn_val);   
			set_pid_target(&pid_location2, Car_Turn_val);
		
			g_lMotorPulseSigma = 0;    
			g_lMotor2PulseSigma = 0; 
		
			set_motor_enable();   //ʹ�ܵ������PWM���    
		  set_motor2_enable();   //ʹ�ܵ��2����PWM���

}


//��Ҫ�ߵľ���ת��Ϊ�����������λ���ٶȻ���׼����
void Car_go(int32_t location_cm)   //ֱ�ߺ���     /
{
	float Car_location;
	
	g_fTargetJourney = location_cm;   //��ֹ��ʱ��PID������
	
	
	Car_location   = ( location_cm / (6.5 * 3.14) ) *   (28*4*13) ;   //Car_location ��  location_cm ת��Ϊ��Ӧ��������  
											//���������ǵ�����ٱȱ�Ƶ�ֱ��ʣ��ĳ��Լ�����Ĳ���
	
	  set_pid_target(&pid_location, Car_location);   
	  set_pid_target(&pid_location2, Car_location);
	
	  set_motor_enable();   //ʹ�ܵ������PWM���    
    set_motor2_enable();   //ʹ�ܵ��2����PWM���
	 
	  g_lMotorPulseSigma = 0;    
	  g_lMotor2PulseSigma = 0; 
	
		
}


