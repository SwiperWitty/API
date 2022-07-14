#include "Exist_GPIO.h"

void LCD_GPIO_Init(int SET)
{
#ifdef Exist_LCD
    GPIO_InitTypeDef  GPIO_InitStructure;
    if (SET)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);   //ʹ��A�˿�ʱ��
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
        GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_15;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;         //�������
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�50MHz
        GPIO_Init(GPIOB, &GPIO_InitStructure);    //��ʼ��GPIOB

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
        GPIO_Init(GPIOA, &GPIO_InitStructure);    //��ʼ��GPIOA
    }
    else
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_15;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
        GPIO_Init(GPIOB, &GPIO_InitStructure);    //��ʼ��GPIOB

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
        GPIO_Init(GPIOA, &GPIO_InitStructure);    //��ʼ��GPIOA
    }
#endif
}

void KEY_GPIO_Init(int SET)
{
#ifdef Exist_KEY
    GPIO_InitTypeDef GPIO_InitStructure;
    if (SET) {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }
    else {
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }

#endif
}

void LED_GPIO_Init(int SET)
{
#ifdef Exist_LED
    GPIO_InitTypeDef GPIO_InitStructure;
    if (SET) {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }
    else {
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }
#endif
}


