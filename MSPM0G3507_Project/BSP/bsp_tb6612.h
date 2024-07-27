/*
 * ������������Ӳ�������������չ����Ӳ�����Ϲ���ȫ����Դ
 * �����������www.lckfb.com
 * ����֧�ֳ�פ��̳���κμ������⻶ӭ��ʱ����ѧϰ
 * ������̳��https://oshwhub.com/forum
 * ��עbilibili�˺ţ������������塿���������ǵ����¶�̬��
 * ��������׬Ǯ���������й�����ʦΪ����
 * Change Logs:
 * Date           Author       Notes
 * 2024-07-08     LCKFB-LP    first version
 */

#ifndef _BSP_TB6612_H
#define _BSP_TB6612_H

#include "board.h"


#define AIN1_OUT(X)  ( (X) ? (DL_GPIO_setPins(GPIO_PORT,GPIO_AIN1_PIN)) : (DL_GPIO_clearPins(GPIO_PORT,GPIO_AIN1_PIN)) )
#define AIN2_OUT(X)  ( (X) ? (DL_GPIO_setPins(GPIO_PORT,GPIO_AIN2_PIN)) : (DL_GPIO_clearPins(GPIO_PORT,GPIO_AIN2_PIN)) )

#define BIN1_OUT(X)  ( (X) ? (DL_GPIO_setPins(GPIO_1_PORT,GPIO_1_BIN1_PIN)) : (DL_GPIO_clearPins(GPIO_1_PORT,GPIO_1_BIN1_PIN)) )
#define BIN2_OUT(X)  ( (X) ? (DL_GPIO_setPins(GPIO_1_PORT,GPIO_1_BIN2_PIN)) : (DL_GPIO_clearPins(GPIO_1_PORT,GPIO_1_BIN2_PIN)) )

void AO_Control(uint8_t dir, uint32_t speed);
void BO_Control(uint8_t dir, uint32_t speed);

#endif  /* _BSP_TB6612_H */
