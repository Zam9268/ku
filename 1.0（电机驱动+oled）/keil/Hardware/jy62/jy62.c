#include "ti_msp_dl_config.h"
#include "jy62.h"
#include "protocol.h"

static uint8_t buffer[10];
static volatile uint8_t flags = 0;
static uint8_t counter = 0;
float Pitch,Roll,Yaw;


void jy62_Init(void)
{
	  NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN);
		NVIC_EnableIRQ(UART_0_INST_INT_IRQN);
		DL_UART_clearInterruptStatus(UART_0_INST,DL_UART_INTERRUPT_RX);//清除中断标志位

}

void UART_0_INST_IRQHandler(void)
{

		uint8_t ch = DL_UART_receiveData(UART_0_INST);
		jy62_Receive_Data(ch);
	
}


void jy62_Receive_Data(uint8_t com_data)
{
	  buffer[counter] =   com_data;
	   if(buffer[0] != 0x53) counter = 0;
    else
    {
        counter++;
        flags = 0x00;
    }

    if(counter == 10)
    {
        counter = 0;
        buffer[0] = 0x00;
        Roll = ((float) ((uint16_t) buffer[2] << 8 | (uint16_t) buffer[1])) / 32768.0f * 180.0f;
        Pitch = ((float) ((uint16_t) buffer[4] << 8 | (uint16_t) buffer[3])) / 32768.0f * 180.0f;
        Yaw = ((float) ((uint16_t) buffer[6] << 8 | (uint16_t) buffer[5])) / 32768.0f * 180.0f;
        flags = 0x01;
    }

}
