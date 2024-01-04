/*
 * Caven_event_frame.h
 *
 *  Created on: 2024
 */

#ifndef CAVEN_EVENT_FRAME_H_
#define CAVEN_EVENT_FRAME_H_

#ifdef CAVEN    /* Ԥ���� */
#include "Caven_Type.h"
#else
#include "stdint.h"
#include "string.h"
#include "stddef.h"
#include "stdio.h"
#endif

#define CAVEN_EVENTS_MAX    20

/*
    �˽ṹ�����ָ����������Դ˽ṹ����Ҫ��ʼ�����е�ָ�롣
*/
typedef struct
{
    int events_num;
    unsigned char events[CAVEN_EVENTS_MAX];
    D_pFun events_pFun[CAVEN_EVENTS_MAX];

}Caven_event_Type;


int Caven_new_event_Fun(Caven_event_Type *events,D_pFun event_pFun,int *handle);
int Caven_delete_event_Fun(Caven_event_Type *events,int *handle);

int Caven_trigger_event_Fun(Caven_event_Type *events,int const handle,char data);

int Caven_handle_event_Fun(Caven_event_Type *events);

#endif /* CAVEN_EVENT_FRAME_H_ */
