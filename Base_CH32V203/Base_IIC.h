#ifndef _IIC__H_
#define _IIC__H_

#if DEFAULT
#include "Items.h"              //默认功能
#else
#include "User_items.h"         //自行设置功能，一般出现在本地文件的User中
#endif

/*
 * 标准软件模拟IIC
 * MAX  36kHZ(8bit+ACK)
 * MAX  33kHZ(8bit+WaitASK-YES)
 * MAX  19kHZ(8bit+WaitASK-NO)
 * MAX-Pro  142kHZ(8bit+ACK)
 */

//配置
#ifdef Exist_IIC
#define IIC_Base_Speed  12
#define IIC_Mode_IN     GPIO_Mode_IPU
#define IIC_Mode_OUT    GPIO_Mode_Out_PP


//IIC_GPIO

#define IIC_SCL        GPIO_Pin_10
#define IIC_SDA        GPIO_Pin_11
#define GPIO_IIC       GPIOB

#define IIC_SDA_H() GPIO_IIC->BSHR = IIC_SDA        //置高电平
#define IIC_SDA_L() GPIO_IIC->BCR = IIC_SDA         //置低电平
#define IIC_SCL_H() GPIO_IIC->BSHR = IIC_SCL
#define IIC_SCL_L() GPIO_IIC->BCR = IIC_SCL

#define IIC_SDA_IN() GPIO_IIC->INDR & IIC_SDA      //读取引脚电平
#endif
//

void IIC_Init(int SET);
char IIC_Send_DATA(char Addr,const char *Data,char ACK,int Length,int Speed);
char IIC_Receive_DATA(char Addr,const char *Data,char *Target,char ACK,int Length,int Speed);



#endif
