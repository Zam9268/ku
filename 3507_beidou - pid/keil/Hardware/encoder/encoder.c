#include "ti_msp_dl_config.h"
#include "encoder.h"
long g_lMotorPulseSigma =0;
long g_lMotor2PulseSigma=0;
uint32_t gpio_interrup;
static uint8_t x,y, z, sum;
int16_t _encoder_0_count,_encoder_1_count = 0;
static uint8_t QEI0_Flag, QEI1_Flag = 0;

int32_t g_nMotorPulse=0,g_nMotor2Pulse=0;//全局变量， 保存电机脉冲数值
int8_t motor1_dir,motor2_dir;
int32_t moto1_exti=0,moto2_exti=0;

void QEI1_IRQHandler(void);

void QEI0_IRQHandler(void);



//放在20ms的中断里
void Setmotopulse(void)
{
	//累加脉冲数
	g_lMotorPulseSigma+=g_nMotorPulse;
	g_lMotor2PulseSigma+=g_nMotor2Pulse;
	
	
	g_nMotorPulse = _encoder_0_count;
	g_nMotor2Pulse= _encoder_1_count;
	_encoder_0_count =0;
	_encoder_1_count =0;
	
}

void GROUP1_IRQHandler(void)
{
	
		switch(DL_Interrupt_getPendingGroup(DL_INTERRUPT_GROUP_1)) 
	{
		case PORTB_INT_IIDX:
            if (DL_GPIO_getEnabledInterruptStatus(GPIOB, PORTB_AC1_PIN))
            {
                QEI0_Flag = 1;
                QEI0_IRQHandler();
                DL_GPIO_clearInterruptStatus(GPIOB, PORTB_AC1_PIN);
            }
            if (DL_GPIO_getEnabledInterruptStatus(GPIOB, PORTB_AC2_PIN))
            {
                QEI0_Flag = 2;
                QEI0_IRQHandler();
                DL_GPIO_clearInterruptStatus(GPIOB, PORTB_AC2_PIN);
            }
            if (DL_GPIO_getEnabledInterruptStatus(GPIOB, PORTB_BC1_PIN))
            {
                QEI1_Flag = 1;
                QEI1_IRQHandler();
                DL_GPIO_clearInterruptStatus(GPIOB, PORTB_BC1_PIN);
            }
            if (DL_GPIO_getEnabledInterruptStatus(GPIOB, PORTB_BC2_PIN))
            {
                QEI1_Flag = 2;
                QEI1_IRQHandler();
                DL_GPIO_clearInterruptStatus(GPIOB, PORTB_BC2_PIN);
            }
            break;
    }

	

}

//获取电机A编码器脉冲
void QEI0_IRQHandler(void)
{
	if (QEI0_Flag==1)
    {
        x = 1; 

        if (DL_GPIO_readPins(GPIOB, PORTB_AC1_PIN))
            y = 1;
        else
            y = 0;
     
        if (DL_GPIO_readPins(GPIOB, PORTB_AC2_PIN))
            z = 1;
        else
            z = 0;

        sum = x + y + z; 
        if (sum == 0 || sum == 2)
            _encoder_0_count++;
        else
            _encoder_0_count--;
    }

    if (QEI0_Flag == 2)
    {
        x=0;
       
        if (DL_GPIO_readPins(GPIOB, PORTB_AC1_PIN))
            y = 1;
        else y=0;
      
        if (DL_GPIO_readPins(GPIOB, PORTB_AC2_PIN))
            z = 1;
        else z=0;

        sum=x+y+z;
        if(sum==0||sum==2) _encoder_0_count++;
        else _encoder_0_count--;
    }

}
//获取电机B编码器脉冲
void QEI1_IRQHandler(void)
{
    if (QEI1_Flag == 1)
    {
        x = 1; 
      
        if (DL_GPIO_readPins(GPIOB, PORTB_BC1_PIN))
            y = 1;
        else
            y = 0;
    
        if (DL_GPIO_readPins(GPIOB, PORTB_BC2_PIN))
            z = 1;
        else
            z = 0;

        sum = x + y + z; 
        if (sum == 0 || sum == 2)
            _encoder_1_count--;
        else
            _encoder_1_count++;
    }

    if (QEI1_Flag == 2)
    {
        x = 0; 
        if (DL_GPIO_readPins(GPIOB, PORTB_BC1_PIN))
            y = 1;
        else
            y = 0;
        if (DL_GPIO_readPins(GPIOB, PORTB_BC2_PIN))
            z = 1;
        else
            z = 0;

        sum = x + y + z; 
        if (sum == 0 || sum == 2)
            _encoder_1_count--;
        else
            _encoder_1_count++;
    }
}

