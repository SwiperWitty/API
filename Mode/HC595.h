#ifndef _HC595_H_
#define _HC595_H_

#include "Base.h"
#include "Caven.h"

/*
	���ĵ����� Otavia���� ���� Zeno�� 74CH595��������������˼�������������������
    �ܽŶ����� base_sys_time �ļ�
*/

struct HC595_
{
    void (*Set_DATA) (const unsigned char *Dat,char num);
};

void HC595_Init (int SET);
void Set_DATA (const unsigned char *Dat,char num);


#endif
