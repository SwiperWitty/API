#ifndef _VOFA_INFO__H_
#define _VOFA_INFO__H_

/*
    Vofa_info.h
    C���Ի�����������
    2024.1.1

*/

#ifdef CAVEN    /* Ԥ���� */
#include "Caven_Type.h"
#else
#include "stdint.h"
#include "string.h"
#include "stddef.h"
#include "stdio.h"
#endif

int Vofa_JustFloat_Init_Fun (char ch_num,Send_pFun send_fun);
int Vofa_JustFloat_Show_Fun (float *f_num);

#endif
