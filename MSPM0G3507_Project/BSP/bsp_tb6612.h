/*
 * 立创开发板软硬件资料与相关扩展板软硬件资料官网全部开源
 * 开发板官网：www.lckfb.com
 * 技术支持常驻论坛，任何技术问题欢迎随时交流学习
 * 立创论坛：https://oshwhub.com/forum
 * 关注bilibili账号：【立创开发板】，掌握我们的最新动态！
 * 不靠卖板赚钱，以培养中国工程师为己任
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
