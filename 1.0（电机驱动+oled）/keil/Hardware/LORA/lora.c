#include "ti_msp_dl_config.h"
#include "lora.h"
#include "protocol.h"

uint8_t task =0;

unsigned char bufflora[5];

void LORA_Init(void)
{
	  NVIC_ClearPendingIRQ(UART_1_INST_INT_IRQN);
		NVIC_EnableIRQ(UART_1_INST_INT_IRQN);
		DL_UART_clearInterruptStatus(UART_1_INST,DL_UART_INTERRUPT_RX);//����жϱ�־λ

	
}

void UART_1_INST_IRQHandler(void)
{
	
	//Ұ����λ�����ܺ�������ʱע�ͼ���
	if(DL_UART_getEnabledInterruptStatus(UART_1_INST,DL_UART_INTERRUPT_RX) == DL_UART_INTERRUPT_RX)
  {
		uint8_t uart_data;
		uart_data =DL_UART_receiveData(UART_1_INST);	//��ȡ���յ�������
		protocol_data_recv(&uart_data, 1);//�����ݷ��뵽���λ�����

		DL_UART_clearInterruptStatus(UART_1_INST,DL_UART_INTERRUPT_RX);//����жϱ�־λ
  }

	//LORA���ܺ���
//	  uint8_t i_UartReceiveData;
//    i_UartReceiveData = DL_UART_receiveData(UART_1_INST);
//		task = i_UartReceiveData;
//		lora_Data(i_UartReceiveData);

}

//LORA���ݽ���
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
//LORA����
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

