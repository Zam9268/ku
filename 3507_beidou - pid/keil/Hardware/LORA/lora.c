#include "ti_msp_dl_config.h"
#include "lora.h"
#include "protocol.h"

uint8_t task =0;

unsigned char bufflora[5];

void LORA_Init(void)
{
	  NVIC_ClearPendingIRQ(UART_1_INST_INT_IRQN);
		NVIC_EnableIRQ(UART_1_INST_INT_IRQN);
		DL_UART_clearInterruptStatus(UART_1_INST,DL_UART_INTERRUPT_RX);//清除中断标志位

	
}

void UART_1_INST_IRQHandler(void)
{
	
	//野火上位机接受函数不用时注释即可
	if(DL_UART_getEnabledInterruptStatus(UART_1_INST,DL_UART_INTERRUPT_RX) == DL_UART_INTERRUPT_RX)
  {
		uint8_t uart_data;
		uart_data =DL_UART_receiveData(UART_1_INST);	//读取接收到的数据
		protocol_data_recv(&uart_data, 1);//将数据放入到环形缓冲区

		DL_UART_clearInterruptStatus(UART_1_INST,DL_UART_INTERRUPT_RX);//清除中断标志位
  }

	//LORA接受函数
//	  uint8_t i_UartReceiveData;
//    i_UartReceiveData = DL_UART_receiveData(UART_1_INST);
//		task = i_UartReceiveData;
//		lora_Data(i_UartReceiveData);

}

//LORA数据接收
void lora_Data(uint8_t com_data)
{ 
	
	      if(com_data==0x01)  
        {
					DL_GPIO_clearPins(GPIOA,DL_GPIO_PIN_0);
        }

        else if(com_data==0x02)  
        {
        }

}
//LORA发送
void loraSendArray(unsigned char *array,int lenth)
{ 
	unsigned char i;
	
	for(i = 0;i<lenth;i++)
	{
		 DL_UART_Main_transmitDataBlocking(UART_1_INST, array[i]);

	}
}

uint8_t HAL_UART_Transmit( uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
	uint8_t  *pdata8bits;
	uint8_t TxXferCount;
    pdata8bits  = pData;
	TxXferCount = Size;
    while(TxXferCount > 0U)
    {
		if(pdata8bits != NULL)
		{
			DL_UART_Main_transmitDataBlocking(UART_1_INST, *pdata8bits);
			pdata8bits++;
		}
		TxXferCount--;
		while((UART_STAT_TXFE_MASK & (1 << UART_STAT_TXFF_OFS)) != 0);
    }
    return 1;
}

