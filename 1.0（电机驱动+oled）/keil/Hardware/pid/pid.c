#include "ti_msp_dl_config.h"
#include "pid.h"

//定义全局变量
_pid pid_speed, pid_speed2;    
_pid pid_location, pid_location2;
_pid pid_turn,pid_turn_speed;


/**
  * @brief  PID参数初始化
	*	@note 	无
  * @retval 无
  */
void PID_param_init()
{
	/* 位置相关初始化参数 */
    pid_location.target_val=0.0;				
    pid_location.actual_val=0.0;
    pid_location.err=0.0;
    pid_location.err_last=0.0;
    pid_location.integral=0.0;
  
		pid_location.Kp = 0.10;//
		pid_location.Ki = 0.0;
		pid_location.Kd = 0.0;
  
  	/* 速度相关初始化参数 */
    pid_speed.target_val=0.0;				
    pid_speed.actual_val=0.0;
    pid_speed.err=0.0;
    pid_speed.err_last=0.0;
    pid_speed.integral=0.0;
  
		pid_speed.Kp = 22.0;
		pid_speed.Ki = 5.0;
		pid_speed.Kd = 0.0;


		
			/* 位置相关初始化参数 */
    pid_location2.target_val=0.0;				
    pid_location2.actual_val=0.0;
    pid_location2.err=0.0;
    pid_location2.err_last=0.0;
    pid_location2.integral=0.0;
  
		pid_location2.Kp = 0.1;//0.1
		pid_location2.Ki = 0.0;
		pid_location2.Kd = 0.0;
  
  	/* 速度相关初始化参数 */
    pid_speed2.target_val=0.0;				
    pid_speed2.actual_val=0.0;
    pid_speed2.err=0.0;
    pid_speed2.err_last=0.0;
    pid_speed2.integral=0.0;
  
		pid_speed2.Kp = 17.0;
		pid_speed2.Ki = 5.0;
		pid_speed2.Kd = 0.0;
		
	/* 角度环相关初始化参数 */

		pid_turn.target_val=0.0;
		pid_turn.actual_val=0.0;
		pid_turn.err=0.0;
		pid_turn.err_last=0.0;
		pid_turn.integral=0.0;
		
		pid_turn.Kp=0.5;//1.0
		pid_turn.Ki=0.0;
		pid_turn.Kd=0.0;

	/* 转向速度相关初始化参数 */

		pid_turn_speed.target_val=160.0;
		pid_turn_speed.actual_val=0.0;
		pid_turn_speed.err=0.0;
		pid_turn_speed.err_last=0.0;
		pid_turn_speed.integral=0.0;
		
		pid_turn_speed.Kp=0.3;//0.3
		pid_turn_speed.Ki=0.005;
		pid_turn_speed.Kd=0.0;
//#if defined(PID_ASSISTANT_EN)
//    float pid_temp[3] = {pid.Kp, pid.Ki, pid.Kd};   //这个得传入对应的pid结构体才行
//    set_computer_value(SEND_P_I_D_CMD, CURVES_CH1, pid_temp, 3);     // 给通道 1 发送 P I D 值
//#endif
}

/**
  * @brief  设置目标值
  * @param  val		目标值
	*	@note 	无
  * @retval 无
  */
void set_pid_target(_pid *pid, float temp_val)
{
  pid->target_val = temp_val;    // 设置当前的目标值
}

/**
  * @brief  获取目标值
  * @param  无
	*	@note 	无
  * @retval 目标值
  */
float get_pid_target(_pid *pid)
{
  return pid->target_val;    // 设置当前的目标值
}

void set_p_i_d(_pid *pid, float p, float i, float d)
{
  	pid->Kp = p;    // 设置比例系数 P
		pid->Ki = i;    // 设置积分系数 I
		pid->Kd = d;    // 设置微分系数 D
}

/**
  * @brief  位置PID算法实现
  * @param  actual_val:实际值
	*	@note 	无
  * @retval 通过PID计算后的输出
  */
float location_pid_realize(_pid *pid, float actual_val)  //位置环光个Kp好像也可以
{
		/*计算目标值与实际值的误差*/
    pid->err=pid->target_val-actual_val;
  
//    /* 设定闭环死区 */   //外环死区可以不要 
    if((pid->err >= -0.1) && (pid->err <= 0.1)) 
    {
      pid->err = 0;
      pid->integral = 0;
    }
    
    pid->integral += pid->err;    // 误差累积

		/*PID算法实现*/
    pid->actual_val = pid->Kp*pid->err
		                  +pid->Ki*pid->integral
		                  +pid->Kd*(pid->err-pid->err_last);
  
		/*误差传递*/
    pid->err_last=pid->err;
    
		/*返回当前实际值*/
    return pid->actual_val;
}

/**
  * @brief  速度PID算法实现
  * @param  actual_val:实际值
	*	@note 	无
  * @retval 通过PID计算后的输出
  */
float speed_pid_realize(_pid *pid, float actual_val)
{
		/*计算目标值与实际值的误差*/
    pid->err=pid->target_val-actual_val;

    if((pid->err<0.5f ) && (pid->err>-0.5f))   //假如以最大允许速度偏差运行1分钟，输出轴最大偏差为半圈
		{
      pid->err = 0.0f;
		}
	
		
    pid->integral += pid->err;    // 误差累积
	
	
//	  /*积分限幅*/
//	   	 if (pid->integral >= 1000) {pid->integral =1000;}
//      else if (pid->integral < -1000)  {pid->integral = -1000;}

		/*PID算法实现*/
    pid->actual_val = pid->Kp*pid->err
		                  +pid->Ki*pid->integral
		                   +pid->Kd*(pid->err-pid->err_last);
  
		/*误差传递*/
    pid->err_last=pid->err;
    
		/*返回当前实际值*/
    return pid->actual_val;
}

float turn_pid_realize(_pid *pid, float actual_val)  //位置环光个Kp好像也可以
{
		/*计算目标值与实际值的误差*/
    pid->err=pid->target_val-actual_val;
  
    /* 设定闭环死区 */   //外环死区可以不要 
//    if((pid->err >= -0.5f) && (pid->err <= 0.5f)) 
//    {
//      pid->err = 0;
//      pid->integral = 0;
//    }
    
    pid->integral += pid->err;    // 误差累积

		/*PID算法实现*/
    pid->actual_val = pid->Kp*pid->err
		                  +pid->Ki*pid->integral
		                  +pid->Kd*(pid->err-pid->err_last);
  
		/*误差传递*/
    pid->err_last=pid->err;
    
		/*返回当前实际值*/
    return pid->actual_val;
}



float turn_speed_pid_realize(_pid *pid, float actual_val)
{
		/*计算目标值与实际值的误差*/
    pid->err=pid->target_val-actual_val;

    if((pid->err<1 ) && (pid->err>-1))   //假如以最大允许速度偏差运行1分钟，输出轴最大偏差为半圈
		{
      pid->err = 1;
		}
	
		
    pid->integral += pid->err;    // 误差累积
	
	
	  /*积分限幅*/
	   	 if (pid->integral >= 1000) {pid->integral =1000;}
      else if (pid->integral < -1000)  {pid->integral = -1000;}

		/*PID算法实现*/
    pid->actual_val = pid->Kp*pid->err
		                  +pid->Ki*pid->integral
		                   +pid->Kd*(pid->err-pid->err_last);
  
		/*误差传递*/
    pid->err_last=pid->err;
    
		/*返回当前实际值*/
    return pid->actual_val;
}


