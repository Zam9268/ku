/***
	*******************************************************************************************************************************************************************
	* @file    usart.c
	* @version V2.1
	* @date    2024-7-22
	* @author  御龙	
	* @brief   MSPM0G3507小车PID调试通用模板
   *************************************************************************************************
   *  @description
	*	
	*  接口配置可以使用Sysconfig看
   *
>>>>> 其他说明：未经允许不可擅自转发、售卖本套代码，大家都是我国的有为青年，请保持好自己的初心，在此，向你表达我的感谢
	*************************************************************************************************************************************************************
***/

//#include "usart.h"
//#include "stdio.h"
//#include "encorder.h"
//#include "board.h"
///*-----------------*/

//#include "ti_msp_dl_config.h"

//volatile unsigned int delay_times = 0;
//volatile unsigned char uart_data = 0;

//void delay_ms(unsigned int ms);
//void uart0_send_char(char ch);
//void uart0_send_string(char* str);

//void usart_init(void)
//{
//   // SYSCFG_DL_init();
//    //清除串口中断标志
//    NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN);
//    //使能串口中断
//		NVIC_EnableIRQ(UART_0_INST_INT_IRQN);
////		printf("Board Init [[ ** LCKFB ** ]]\r\n");
//}

////搭配滴答定时器实现的精确ms延时
//void delay_ms(unsigned int ms)
//{
//    delay_times = ms;
//    while( delay_times != 0 );
//}
////串口发送单个字符
//void uart0_send_char(char ch)
//{
//    //当串口0忙的时候等待，不忙的时候再发送传进来的字符
//    while( DL_UART_isBusy(UART_0_INST) == true );
//    //发送单个字符
//    DL_UART_Main_transmitData(UART_0_INST, ch);
//}
////串口发送字符串
//void uart0_send_string(char* str)
//{
//    //当前字符串地址不在结尾 并且 字符串首地址不为空
//    while(*str!=0&&str!=0)
//    {
//        //发送字符串首地址中的字符，并且在发送完成之后首地址自增
//        uart0_send_char(*str++);
//    }
//}

////滴答定时器的中断服务函数
//void SysTick_Handler(void)
//{
//    if( delay_times != 0 )
//    {
//        delay_times--;
//    }
//}

////串口的中断服务函数
//void UART_0_INST_IRQHandler(void)
//{
//    //如果产生了串口中断
//    switch( DL_UART_getPendingInterrupt(UART_0_INST) )
//    {
//        case DL_UART_IIDX_RX://如果是接收中断
//            //接发送过来的数据保存在变量中
//            uart_data = DL_UART_Main_receiveData(UART_0_INST);
//            //将保存的数据再发送出去
//            uart0_send_char(uart_data);
//            break;

//        default://其他的串口中断
//            break;
//    }
//		
//		
//}
//void usart0_send_byte(char byte)
//{
//	while(DL_UART_isBusy(UART_0_INST) ==true);
//	DL_UART_Main_transmitData(UART_0_INST, byte);
//}

//void usart0_send_string(char * byte)
//{
//	while(*byte!=0 && byte !=0)
//		usart0_send_byte(*byte ++);
//	
//}



////void usart0_send_byte(unsigned char byte)
////{
////	DL_UART_Main_transmitDataBlocking(UART_0_INST, byte);
////}
//void usart0_send_bytes(unsigned char *buf, int len)
//{
//  while(len--)
//  {
//		DL_UART_Main_transmitDataBlocking(UART_0_INST, *buf);
//    buf++;
//  }
//}
//unsigned int HAL_UART_Transmit( unsigned int *pData, unsigned int Size, unsigned int Timeout)
//{
//	unsigned int  *pdata8bits;
//	unsigned int TxXferCount;
//    pdata8bits  = pData;
//	TxXferCount = Size;
//    while(TxXferCount > 0U)
//    {
//		if(pdata8bits != NULL)
//		{
//			DL_UART_Main_transmitDataBlocking(UART_0_INST, *pdata8bits);
//			pdata8bits++;
//		}
//		TxXferCount--;
//		// 等待传输寄存器为空   
//		while((UART_STAT_TXFE_MASK & (1 << UART_STAT_TXFF_OFS)) != 0);
//    }
//    return 1;
//}

//int fputc(int ch, FILE *f)
//{
////	uart0_send_char(ch);
//  DL_UART_Main_transmitDataBlocking(UART_0_INST, ch);
//  return ch;
//}


///*-------------------------------------------------------------------------------------------*/
///*----------------------也可以使用VOFA+观察波形，选择JustFloat协议---------------------------*/
///*-------------------------------------------------------------------------------------------*/
///*
//要点提示:
//1. float和unsigned long具有相同的数据结构长度
//2. union据类型里的数据存放在相同的物理空间
//*/
////typedef union{
////    float fdata;
////    unsigned long ldata;
////} FloatLongType;
////void JustFloat_SendArray(uint8_t *string,uint8_t length)
////{
////	while(length--)
////	{
////	DL_UART_Main_transmitDataBlocking(UART_0_INST, *string++);
////	}
////}
/////*将浮点数f转化为4个字节数据存放在byte[4]中*/
////void Float_to_Byte(float f,unsigned char byte[]){
////    FloatLongType fl;
////    fl.fdata=f;
////    byte[0]=(unsigned char)fl.ldata;
////    byte[1]=(unsigned char)(fl.ldata>>8);
////    byte[2]=(unsigned char)(fl.ldata>>16);
////    byte[3]=(unsigned char)(fl.ldata>>24);
////}
////void JustFloat_Test(void)	//justfloat 数据协议测试
////{
////    float a=1,b=2;	//发送的数据 两个通道
////	
////	u8 byte[4]={0};		//float转化为4个字节数据
////	u8 tail[4]={0x00, 0x00, 0x80, 0x7f};	//帧尾
////	
////	//向上位机发送两个通道数据
////	Float_to_Byte(a,byte);
////	//u1_printf("%f\r\n",a);
////	JustFloat_SendArray(byte,4);	//1转化为4字节数据 就是  0x00 0x00 0x80 0x3F
////	
////	Float_to_Byte(b,byte);
////	JustFloat_SendArray(byte,4);	//2转换为4字节数据 就是  0x00 0x00 0x00 0x40 
////	
////	//发送帧尾
////	JustFloat_SendArray(tail,4);	//帧尾为 0x00 0x00 0x80 0x7f

////}
//////向vofa发送数据  三个数据  三个通道  可视化显示  帧尾
////void vofa_sendData(float a,float b,float c){
////    u8 byte[4]= {0};//float转化为4个字节数据
////    u8 tail[4]= {0x00, 0x00, 0x80, 0x7f};//帧尾

////    //向上位机发送通道数据
////    Float_to_Byte(a,byte);
////    JustFloat_SendArray(byte,4);	

////    Float_to_Byte(b,byte);
////    JustFloat_SendArray(byte,4);	

////    Float_to_Byte(c,byte);
////    JustFloat_SendArray(byte,4);
////    //发送帧尾
////    JustFloat_SendArray(tail,4);	//帧尾为 0x00 0x00 0x80 0x7f
////}

////void UART_0_INST_IRQHandler(void)
////{
////  if(DL_UART_getEnabledInterruptStatus(UART_0_INST,DL_UART_INTERRUPT_RX) == DL_UART_INTERRUPT_RX)
////  {
////		uint8_t uart_data;

////		uart_data =DL_UART_receiveData(UART_0_INST);	//读取接收到的数据
////		protocol_data_recv(&uart_data, 1);//将数据放入到环形缓冲区
////		DL_UART_clearInterruptStatus(UART_0_INST,DL_UART_INTERRUPT_RX);//清除中断标志位
////  }
////}
