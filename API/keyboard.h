/*
 * keyboard.h
 *
 *  Created on: 2022��7��22��
 *      Author: gxwl
 *      ���̱�
 */

#ifndef API_KEYBOARD_H_
#define API_KEYBOARD_H_

#include "Caven.h"

struct USB_FUN_
{
    void (*Send)(char Temp,char * DATA);
    void (*Delay)(int num);

};

char ASCII_TO_Keyboard(const char *Source,char *Target);
void Keyboard_Send (char *Source,struct USB_FUN_ *FUN,char *Target);

#endif /* API_KEYBOARD_H_ */
