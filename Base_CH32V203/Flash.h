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
    #define FLASH_AREA          //Flash��ʼ������

    #define FLASH_DATA      FLASH_AREA      //Flash��ŵ��籣��������
    #define FLASH_DATA_END  (FLASH_DATA + 1024)

    #define FLASH_CODE      FLASH_DATA_END  //Flash���APP�Ĵ�����
    #define FLASH_CODE_END  (FLASH_CODE + 64 * 1024)
#endif

typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

#endif
