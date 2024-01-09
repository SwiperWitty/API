/*
 * Caven_event_frame.c
 *
 *  Created on: 2024
 */
#include "Caven_event_frame.h"

/*
 * Caven_new_event_Fun
 * 1.��������и�events
 * 2.���Ͻṹ������ָ��
 * 3.�����0xEExx˵������even,�����¼������events�����λ0x80��������жϱ�׼��
 */
int Caven_new_event_Fun(Caven_event_Type *events,D_pFun event_pFun,int *handle)
{
    int retval = 0;
    Caven_event_Type temp_events;
    memcpy(&temp_events,events,sizeof(Caven_event_Type));

    if (events == NULL || event_pFun == NULL)
    {
        retval = (-1);
        return retval;
    }
    if (temp_events.events_num >= CAVEN_EVENTS_MAX)
    {
        retval = (-2);
    }
    else
    {
        temp_events.events_num ++;
        *handle = temp_events.events_num | 0xEE00;              // �о����˵���¼�����
        temp_events.events[temp_events.events_num] = 0x80;      // ���λΪ1��˵���¼�����
        temp_events.events_pFun[temp_events.events_num] = event_pFun;
        memcpy(events,&temp_events,sizeof(Caven_event_Type));
    }

    return retval;
}

int Caven_delete_event_Fun(Caven_event_Type *events,int *handle)
{
    int retval = 0;
    Caven_event_Type temp_events;
    int temp_num;
    memcpy(&temp_events,events,sizeof(Caven_event_Type));

    if (events == NULL)
    {
        retval = (-1);
        return retval;
    }
    if (temp_events.events_num >= CAVEN_EVENTS_MAX)
    {
        retval = (-2);
    }
    else
    {
        temp_num = *handle;
        temp_num &= 0xff;
        temp_events.events_pFun[temp_num] = NULL;
        temp_events.events[temp_num] = 0x00;
        *handle = 0;
        temp_events.events_num --;
        memcpy(events,&temp_events,sizeof(Caven_event_Type));
    }

    return retval;
}

int Caven_trigger_event_Fun(Caven_event_Type *events,int const handle,char data)
{
    int retval = 0;
    Caven_event_Type temp_events;
    int temp_num;
    memcpy(&temp_events,events,sizeof(Caven_event_Type));

    if (events == NULL)
    {
        retval = (-1);
        return retval;
    }
    if (handle & 0xee00)              // �о����˵���¼�����
    {
        temp_num = handle;
        temp_num &= 0xff;
        temp_events.events[temp_num] |= ((data & 0x3f) + 0x40);     // �����¼������ݱ���
        memcpy(events,&temp_events,sizeof(Caven_event_Type));
    }
    else
    {
        retval = (-2);
    }

    return retval;
}

/*
 * Caven_handle_event_Fun
 * 1.ʹ��ǰ��Ҫ�ȵ���Caven_new_event_Fun
 * 2.Caven_handle_event_Fun����Ӧ�÷���״̬�������ַ�����
 * 3.events�����events_pFun��������������
 * 4.ͨ��Caven_trigger_event_Fun���data�Ὣ������events���棬events_pFun������Ҫ��data��0��������ǰ������
 */
int Caven_handle_event_Fun(Caven_event_Type *events)
{
    int retval = 0;
    int temp;
    unsigned char temp_num = events->events_num;

    if (events == NULL)
    {
        retval = (-1);
        return retval;
    }

    if (temp_num > CAVEN_EVENTS_MAX)
    {
        retval = (-2);
        return retval;
    }
    for (int i = 0; i <= temp_num; ++i)
    {
        temp = events->events[i] & 0xff;
        if (temp & 0x80)        /* ���ھ��  */
        {
            if (temp & 0x40)    /* ���ڴ���  */
            {
                temp &= 0x3F;
                if (events->events_pFun[i] != NULL)
                {
                    events->events_pFun[i](&temp);          /* ִ��ָ�뺯��  */
                }
                if (temp == 0)
                {
                    events->events[i] &= 0x80;              /* ����������  */
                }
            }
        }
    }
    return retval;
}




