#ifndef __Exist_GPIO__H_
#define __Exist_GPIO__H_

#include "Items.h"

/*
                GPIO_Init(Exist_GPIO)->
    SDK->Items->                       BASE->
                Peripheral(UART��ADC)->      \\
                                              -->[XXX]->MODE
                                             //
                        C(Lib)->Caven->API->
*/

/*
        ���ļ���������ϵͼ������ ��GPIO_Init��
         �����ŵ��ǡ�ֻʹ��GPIO���衿���ܵĳ�ʼ����KEY��LED��BZZ���������ȣ���
         �������ܵĳ�ʼ��������UART��IIC���������ȳ�ʼ����GPIO���衿��Ҫ���������衿�����ֹ��ܵĳ�ʼ��GPIO�����ڱ��ļ���Χ�ڡ�
         IIC������汾��Ӳ���汾����������GPIO�����ļ��޹ء�
         ����LCD��������SPIЭ���DC��IO���ӿ���ɣ���ô���IO�ӿ��ɱ��ļ��ṩ��

                                                                     ��������202207.14
 */

#ifdef Exist_LCD
    #define LCD_DC_Clr() GPIOA->BRR = GPIO_Pin_10    //DC_GPIO
    #define LCD_DC_Set() GPIOA->BSRR = GPIO_Pin_10   //PA10
//    #define LCD_RES_Clr()                                     //RES               //Caven ʹ��Ӳ����λ
//    #define LCD_RES_Set()
#endif

#ifdef Exist_OLED

    #define OLED_DC_Clr() GPIOA->BRR = GPIO_Pin_10    //DC_GPIO
    #define OLED_DC_Set() GPIOA->BSRR = GPIO_Pin_10   //PA10

//    #define LCD_RES_Clr()                                     //RES               //Caven ʹ��Ӳ����λ
//    #define LCD_RES_Set()
#endif

#ifdef Exist_LED
    #define LED_Clr() GPIOB->BRR = GPIO_Pin_11    //LED
    #define LED_Set() GPIOB->BSRR = GPIO_Pin_11   //PB011
#endif
#ifdef Exist_BZZ
    #define BZZ_Clr() GPIOB->BRR = GPIO_Pin_5    //BZZ
    #define BZZ_Set() GPIOB->BSRR = GPIO_Pin_5   //PB05
#endif

#ifdef Exist_KEY
    #define KEY_Read() GPIOA->IDR & GPIO_Pin_0     //KEY,��
#endif
#ifdef Exist_Ultrasonic
    #define Trig_Clr() GPIOB->BRR = GPIO_Pin_4     //Ultrasonic
    #define Trig_Set() GPIOB->BSRR = GPIO_Pin_4
    #define Echo_Read() GPIOB->INDR & GPIO_Pin_5
#endif

/*  Init-Function    */

void LCD_GPIO_Init(int SET);

void LED_GPIO_Init(int SET);
void BZZ_GPIO_Init(int SET);

void KEY_GPIO_Init(int SET);
void Ultrasonic_GPIO_Init(int SET);

#endif
