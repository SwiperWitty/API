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

#ifdef Exist_OLED

    #define LCD_DC_Clr() GPIOA->BCR = GPIO_Pin_10    //DC_GPIO
    #define LCD_DC_Set() GPIOA->BSHR = GPIO_Pin_10   //PA10

//    #define LCD_RES_Clr()                                     //RES               //Caven ʹ��Ӳ����λ
//    #define LCD_RES_Set()
#endif

#ifdef Exist_OLED

    #define OLED_DC_Clr() GPIOA->BCR = GPIO_Pin_10    //DC_GPIO
    #define OLED_DC_Set() GPIOA->BSHR = GPIO_Pin_10   //PA10

//    #define LCD_RES_Clr()                                     //RES               //Caven ʹ��Ӳ����λ
//    #define LCD_RES_Set()
#endif

#ifdef Exist_KEY
    #define KEY_Clr() GPIOA->BCR = GPIO_Pin_0    //KEY
    #define KEY_Set() GPIOA->BSHR = GPIO_Pin_0   //PA00
#endif

#ifdef Exist_LED
    #define LED_Clr() GPIOA->BCR = GPIO_Pin_1    //LED
    #define LED_Set() GPIOA->BSHR = GPIO_Pin_1   //PA01
#endif

#ifdef Exist_BZZ

#endif

#ifdef Exist_Ultrasonic

#endif

/*  Init-Function    */

void KEY_GPIO_Init(int SET);
void LED_GPIO_Init(int SET);

#endif
