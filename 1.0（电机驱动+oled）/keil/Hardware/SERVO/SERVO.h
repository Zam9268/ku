#ifndef _SERVO_H  
#define _SERVO_H

#include <stdint.h>

void Servo_Init(void);
void Set_Servo_Angle(unsigned int angle);
unsigned int Get_Servo_Angle(void);

	
//void Servo_SetAngle(float Angle);

#endif