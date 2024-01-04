#include "HC595.h"

void HC595_Init (int Set)
{
#ifdef Exist_HC595
    HC595_GPIO_Init(Set);
	HC595_Data_L();
    HC595_SCK_L();
    HC595_RCK_L();
#endif
}

#ifdef Exist_HC595
static void HC595_Delay (int time)
{
    Base_SYS_Delay (time,5);
}
#endif

static void Send_HC595 (const unsigned char Dat)
{
#ifdef Exist_HC595
	char n;
    HC595_SCK_L();
    HC595_RCK_L();
    for(n = 0;n < 8;n++)
    {
        if((Dat << n) & 0x80) HC595_Data_H();
        else       			  HC595_Data_L();
        HC595_SCK_H();
        HC595_Delay (10);
		HC595_SCK_L();
        HC595_Delay (10);
    }
#endif
}

static void HC595_END (void)
{
#ifdef Exist_HC595
    HC595_RCK_L();
    HC595_Delay (10);
	HC595_RCK_H();
    HC595_Delay (10);
	HC595_RCK_L();
#endif
}

void HC595_Set_DATA (const unsigned char *Dat,char num)
{
	char m;
	for(m = 0; m < num;m++)
	{
		Send_HC595 (*(Dat+m));
	}
    HC595_END ();
}
