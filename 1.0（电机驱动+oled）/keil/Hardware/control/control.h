#ifndef __CONTROL_H
#define __CONTROL_H
#include <stdint.h>


#define PWM_PERIOD_COUNT     (4000)     //可以尝试把这个变大，这样PID控制可以更顺滑
#define PWM2_PERIOD_COUNT     (4000)


/* 最大比较值 */
#define PWM_MAX_PERIOD_COUNT              (PWM_PERIOD_COUNT - 30)    //如果PWM弄成了满的，一些驱动板就会出现问题（硬件上的原因）
#define PWM2_MAX_PERIOD_COUNT              (PWM2_PERIOD_COUNT - 30)


//#define SET_COMPAER(ChannelPulse)        	DL_TimerA_setCaptureCompareValue(GPIO_PWM_0_C0_PORT,ChannelPulse,GPIO_PWM_0_C0_IDX);



//#define SET2_COMPAER(ChannelPulse)      	DL_TimerA_setCaptureCompareValue(GPIO_PWM_0_C1_PORT,ChannelPulse,GPIO_PWM_0_C1_IDX);
   
/* 使能输出 */
#define MOTOR_ENABLE()      DL_TimerA_startCounter(PWM_0_INST);


/* 禁用输出 */
#define MOTOR_DISABLE()     DL_TimerG_disableClock(PWM_0_INST);

/* 编码器物理分辨率 */
#define ENCODER_RESOLUTION                     13

/* 经过倍频之后的总分辨率 */
#define ENCODER_TOTAL_RESOLUTION             (ENCODER_RESOLUTION * 4)  /* 4倍频后的总分辨率 */

/* 减速电机减速比 */
#define REDUCTION_RATIO  28

#define SPEED_PID_PERIOD  20    //定时器的中断周期
#define TARGET_SPEED_MAX   50  //原200，试改小；试改范围0-100

#define LUN_JU 14.3   //单位cm
#define HeadToWheelCM 13


/*直立环*/
#define Vertical_Kp 0
#define Vertical_Kd 0

/*速度环(位置式)*/
#define velocityKp 0
#define velocityKi 0

/*速度环(增量式)*/
#define VelocityKp 0
#define VelocityKi 0
#define VelocityKd 0


/*转向环*/
#define turnKp 5

/*循迹*/
#define lineKp 0
#define lineKd 0




typedef enum
{
  left_90,
	right_90,
	back_180
}spin_dir_t;



/* 电机方向控制枚举 */
typedef enum
{
  MOTOR_FWD = 0,
  MOTOR_REV,
}motor_dir_t;


typedef struct {
    float current;  // 当前角度
    float previous; // 上一个角度
} AngleData;

extern AngleData yaw;

extern float speed_Outval, location_Outval;
extern float speed2_Outval, location2_Outval;
extern  uint8_t is_motor_en, is_motor2_en;            // 电机使能
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
void MotorOutput(int nMotorPwm,int nMotor2Pwm);//设置电机电压和方向
void set_motor_enable(void);   //这俩个使能和禁用的函数对于双极性控制来说还有效吗？
void set_motor2_enable(void);
void spin_Turn(spin_dir_t zhuanxiang);   
void Car_go(int32_t location_cm);   //直走函数     //连续两次的直行好像会让巡线补偿失效
int turnPid(float Target_gyro, float Now_gyro);
float turn_speed_pid_control(void);  
void lind_Turn_Speed_control(void);          

void mainControl(void);

void Turn_Angle_Speed_control(void);          



#endif