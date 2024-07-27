#ifndef _SYSTEM_H  
#define _SYSTEM_H



extern int32_t g_nMotorPulse,g_nMotor2Pulse;
extern int32_t moto1_exti,moto2_exti;

extern long g_lMotorPulseSigma;
extern long g_lMotor2PulseSigma;

void GetMotorPulse(void);
void Setmotopulse(void);


#endif