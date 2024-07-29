#ifndef _LORA_H  
#define _LORA_H

#include <stdint.h>


void LORA_Init(void);
void lora_Data(uint8_t com_data);

void loraSendArray(unsigned char *array,int lenth);
uint8_t HAL_UART_Transmit( uint8_t *pData, uint16_t Size, uint32_t Timeout);

extern unsigned char bufflora[5];



#endif