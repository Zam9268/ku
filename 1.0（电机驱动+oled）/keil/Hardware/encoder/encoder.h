#ifndef _SYSTEM_H  
#define _SYSTEM_H



extern  int32_t g_nMotorPulse,g_nMotor2Pulse;
extern int32_t moto1_exti,moto2_exti;
extern int16_t _encoder_0_count,_encoder_1_count;
static long g_lMotorPulseSigma;
static long g_lMotor2PulseSigma;

void GetMotorPulse(void);
void Setmotopulse(void);
long get_sigama1(void);
long get_sigama2(void);
void clear_sigama2(void);
void clear_sigama1(void);
#endif