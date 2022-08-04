/*
 * Flash.h
 *
 *  Created on: 2022��8��1��
 *      Author: gxwl
 */

#ifndef __FLASH_H_
#define __FLASH_H_

#include "Items.h"

#ifdef Exist_FLASH
    #define FLASH_PAGE_SIZE ((uint32_t)256)         //һҳ�Ĵ�С
    #define FLASH_AREA_SIZE (FLASH_PAGE_SIZE*16)    //����С
    #define FLASH_SIZE  ((uint32_t)(64*1024))       //Flash��С64K

    #define FLASH_DATA_END  ((uint32_t)0x08009000)              //���籣�桾��������������ַ
    #define FLASH_DATA      (FLASH_DATA_END - FLASH_PAGE_SIZE)  //���籣�桾��������ֻ��һҳ(��ȷ�����λ�ò��ڳ����)

    #define FLASH_CODE      FLASH_DATA_END              //Flash��š�APP�Ĵ�������
    #define FLASH_CODE_END  (0x08000000 + FLASH_SIZE)   //Flash��š�APP�Ĵ�������һֱ�����Flash

    #define FLASH_END       FLASH_CODE_END              //Flash���յ�ַ
#endif

typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;
#define Fast_Flash(x)   *(__IO uint16_t*)(x)

struct _Flash_DATA
{
    int addr;
    char information;
    char version;
    char baud;
    char IP;
    char GPIO;
};

extern const struct _Flash_DATA Flash_DATA;

int Read_Flash(int Address);
char Clear_Flash_Page(int Addr);
char Clear_Flash_Area(int addr_start,int addr_end);

char Save_Flash(int Addr,const uint16_t *Data,int Lenght);

#endif
