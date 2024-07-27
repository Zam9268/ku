#ifndef _BEEP_H  
#define _BEEP_H

#include <stdint.h>

typedef struct
{
	uint16_t times;				 //Ԥ����˸�ܴ���
	uint8_t  reset;				 //��˸���̸�λ��־
	uint16_t cnt;					 //��˸���Ƽ�����
	uint16_t times_cnt;		 //��¼����˸����
	uint8_t  end;					 //��˸��ɱ�־λ
	GPIO_Regs *port;		   //��˸���ڵĶ˿�
	uint32_t pin;					 //��˸���ڵ�GPIO
	uint32_t period;			 //��˸����
	float light_on_percent;//���������ڵ���ʱ��ٷֱ�
}_laser_light;

extern _laser_light beep;

extern uint8_t beep_flag;
extern uint8_t beep_time;
extern uint8_t beep_actime;

void BEEP_Init(void);
void laser_light_work(_laser_light *light);
void buzzer_setup(uint32_t _period, uint16_t _times);



#endif