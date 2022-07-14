#ifndef _ITEMS__H_
#define _ITEMS__H_

#include "ch32v20x.h"

/*
    SDK->Items->GPIO(Exist_GPIO)->BASE->
                                         \\
                                          -->[XXX]->MODE
                                         //
                    C(Lib)->Caven->API->
*/

                                                        /*  �����������ʵ�ֵĹ���    */
#define Exist_SYS_TIME
//#define Exist_PWM
//#define Exist_ENCODE

#define Exist_KEY
#define Exist_LED
//#define Exist_BZZ

//#define Exist_ADC
//#define Exist_DAC

#define Exist_UART
//#define Exist_IIC
//#define Exist_SPI
//#define Exist_CAN

//#define Exist_FLASH
                                                        /*  ֻ��Ҫ�����߼����ܵĹ���    */
//#define Exist_LCD
//#define Exist_OLED    //һ���������Ƕ�ѡһ��ռ�õĶ���SPI��

//#define Exist_38
//#define Exist_595

//#define Exist_Ultrasonic
//#define Exist_FindLine

//#define Exist_Voice

#define Exist_Motor
#define Exist_Steering_Engine

//#define Exist_MLX90614



/*  ��һ�����߼���ϵ    */
#ifdef Exist_LCD
    #ifndef Exist_SPI
        #define Exist_SPI
    #endif
#endif

#ifdef Exist_OLED
    #ifndef Exist_SPI
        #define Exist_SPI
    #endif
#endif

#ifdef Exist_Voice
    #ifndef Exist_UART
        #define Exist_UART
    #endif
#endif

#ifdef Exist_Motor
    #ifndef Exist_PWM
        #define Exist_PWM
    #endif
    #ifndef Exist_ENCODE
        #define Exist_ENCODE
    #endif
#endif

#ifdef Exist_Steering_Engine
    #ifndef Exist_PWM
        #define Exist_PWM
    #endif
#endif

#ifdef Exist_MLX90614
    #ifndef Exist_IIC
        #define Exist_IIC
    #endif
#endif

#endif
