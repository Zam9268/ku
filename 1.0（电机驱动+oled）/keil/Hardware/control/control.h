#ifndef __CONTROL_H
#define __CONTROL_H
#include <stdint.h>


#define PWM_PERIOD_COUNT     (4000)     //���Գ��԰�����������PID���ƿ��Ը�˳��
#define PWM2_PERIOD_COUNT     (4000)


/* ���Ƚ�ֵ */
#define PWM_MAX_PERIOD_COUNT              (PWM_PERIOD_COUNT - 30)    //���PWMŪ�������ģ�һЩ������ͻ�������⣨Ӳ���ϵ�ԭ��
#define PWM2_MAX_PERIOD_COUNT              (PWM2_PERIOD_COUNT - 30)


//#define SET_COMPAER(ChannelPulse)        	DL_TimerA_setCaptureCompareValue(GPIO_PWM_0_C0_PORT,ChannelPulse,GPIO_PWM_0_C0_IDX);



//#define SET2_COMPAER(ChannelPulse)      	DL_TimerA_setCaptureCompareValue(GPIO_PWM_0_C1_PORT,ChannelPulse,GPIO_PWM_0_C1_IDX);
   
/* ʹ����� */
#define MOTOR_ENABLE()      DL_TimerA_startCounter(PWM_0_INST);


/* ������� */
#define MOTOR_DISABLE()     DL_TimerG_disableClock(PWM_0_INST);

/* ����������ֱ��� */
#define ENCODER_RESOLUTION                     13

/* ������Ƶ֮����ֱܷ��� */
#define ENCODER_TOTAL_RESOLUTION             (ENCODER_RESOLUTION * 4)  /* 4��Ƶ����ֱܷ��� */

/* ���ٵ�����ٱ� */
#define REDUCTION_RATIO  28

#define SPEED_PID_PERIOD  20    //��ʱ�����ж�����
#define TARGET_SPEED_MAX   50  //ԭ200���Ը�С���Ըķ�Χ0-100

#define LUN_JU 14.3   //��λcm
#define HeadToWheelCM 13


/*ֱ����*/
#define Vertical_Kp 0
#define Vertical_Kd 0

/*�ٶȻ�(λ��ʽ)*/
#define velocityKp 0
#define velocityKi 0

/*�ٶȻ�(����ʽ)*/
#define VelocityKp 0
#define VelocityKi 0
#define VelocityKd 0


/*ת��*/
#define turnKp 5

/*ѭ��*/
#define lineKp 0
#define lineKd 0




typedef enum
{
  left_90,
	right_90,
	back_180
}spin_dir_t;



/* ����������ö�� */
typedef enum
{
  MOTOR_FWD = 0,
  MOTOR_REV,
}motor_dir_t;


typedef struct {
    float current;  // ��ǰ�Ƕ�
    float previous; // ��һ���Ƕ�
} AngleData;

extern AngleData yaw;

extern float speed_Outval, location_Outval;
extern float speed2_Outval, location2_Outval;
extern  uint8_t is_motor_en, is_motor2_en;            // ���ʹ��
extern float speed3_Outval, turn_Outval;
extern float speed4_Outval;


float turn_angle_pid_control(void); 

float location_pid_control(void);
void Location_Speed_control(void);          
float speed_pid_control(void);
float location2_pid_control(void);  
float speed2_pid_control(void);  
 void set_motor_speed(uint16_t v);    
void set_motor2_speed(uint16_t v);
void set_motor_direction(motor_dir_t dir);  
void set_motor2_direction(motor_dir_t dir);  
void MotorOutput(int nMotorPwm,int nMotor2Pwm);//���õ����ѹ�ͷ���
void set_motor_enable(void);   //������ʹ�ܺͽ��õĺ�������˫���Կ�����˵����Ч��
void set_motor2_enable(void);
void spin_Turn(spin_dir_t zhuanxiang);   
void Car_go(int32_t location_cm);   //ֱ�ߺ���     //�������ε�ֱ�к������Ѳ�߲���ʧЧ
int turnPid(float Target_gyro, float Now_gyro);
float turn_speed_pid_control(void);  
void lind_Turn_Speed_control(void);          

void mainControl(void);

void Turn_Angle_Speed_control(void);          



#endif