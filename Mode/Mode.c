#include "Mode.h"

struct _Mode_Init Mode_Init;
struct _Mode_Use Mode_Use;    //结构体实体

extern u32 MODE_Get_Button_STATE (char Channel);
static void Mode_Use_index(void)		//索引 功能函数 本体
{
    Mode_Use.Debug_Out_Way = Debug_Out;
#ifdef Exist_LCD
    Mode_Use.LCD.Fill_pFun = LCD_Fill_Fun;

    Mode_Use.LCD.Draw_Point_pFun = LCD_Draw_Point;
    Mode_Use.LCD.Draw_Line_pFun = LCD_Draw_Line;
    Mode_Use.LCD.Draw_Circle_pFun = LCD_Draw_Circle;
    Mode_Use.LCD.Draw_Rectangle_pFun = LCD_Draw_Rectangle;
    
    Mode_Use.LCD.Show_String_pFun = LCD_Show_String;
    Mode_Use.LCD.Show_Chinese_pFun = LCD_Show_Chinese;
    Mode_Use.LCD.Show_Picture_pFun = LCD_Show_Picture;

    Mode_Use.LCD.Set_Direction_pFun = LCD_Set_Horizontal;
#endif

#ifdef Exist_SYS_TIME
    Mode_Use.TIME.Delay_Us = MODE_Delay_Us;
    Mode_Use.TIME.Delay_Ms = MODE_Delay_Ms;
    Mode_Use.TIME.Delay_S = MODE_Delay_S;
	

    Mode_Use.TIME.Get_Date_pFun = MODE_TIME_Get_Date_Fun;
    Mode_Use.TIME.Get_Watch_pFun = MODE_TIME_Get_Watch_Fun;

    Mode_Use.TIME.Set_Date_pFun = MODE_TIME_Set_Date_Fun;
    Mode_Use.TIME.Set_Watch_pFun = MODE_TIME_Set_Watch_Fun;

#endif

#ifdef Exist_LED
    Mode_Use.LED.RGB_pFun = MODE_LED_RGB_Fun;
    Mode_Use.LED.SET_pFun = MODE_LED_SET_Fun;

#endif
#ifdef Exist_BZZ
    Mode_Use.BZZ.SET_pFun = MODE_BZZ_SET_Fun;
#endif
#ifdef Exist_HC595
    Mode_Use.HC595.Set_DATA = HC595_Set_DATA_Fun;
#endif
#ifdef Exist_HC138
    Mode_Use.HC138.Set_DATA = HC138_Set_Data_Fun;
#endif
#ifdef Exist_DS18B20
    Mode_Use.DS18B20.Get_Temp = DS18B20_Get_Temp_Fun;
#endif

#ifdef Exist_UART
    Mode_Use.UART.Send_Data_pFun = MODE_UART_Send_Data_Fun;
    Mode_Use.UART.Send_String_pFun = MODE_UART_Send_String_Fun;
    Mode_Use.UART.Receive_Bind_pFun = MODE_UART_Receive_Bind_Fun;
#endif

#ifdef Exist_USB
    Mode_Use.USB_HID.Keyboard_Send_Data = USB_Keyboard_Send_Data;
    Mode_Use.USB_HID.Keyboard_Send_String = USB_Keyboard_Send_String;
    Mode_Use.USB_HID.Custom_Send = USB_Buffer_Send;
    Mode_Use.USB_HID.Custom_Receive = USB_Buffer_Receive;
#endif

#ifdef Exist_BUTTON
    Mode_Use.Button.State_pFun = MODE_Get_Button_State_Fun;
#endif
#ifdef Exist_Ultrasonic
    Mode_Use.Ultrasonic.Distance = Distance;
#endif

#ifdef Exist_Voice
    Mode_Use.MP3.Voice = Voice;
#endif
#ifdef Exist_Steering_Engine
    Mode_Use.Steering_Engine.Set_Angle = MODE_Steering_Engine_Angle_Fun;
    Mode_Use.Steering_Engine.Set_360_Sport = MODE_Steering_Engine_360_Sport_Fun;
#endif  

#ifdef Exist_ADC
    Mode_Use.USER_ADC.Get_MCU_Temperature_pFun = ADC_Get_MCU_Temperature_Fun;
    Mode_Use.USER_ADC.Conversion_Vol_pFun = ADC_Conversion_Vol_Fun; 
    Mode_Use.USER_ADC.Receive_Bind_pFun = ADC_Quick_Get_Bind_Fun;
#endif

}   //  Mode_Use 

void Mode_Index(void) 
{
    Mode_Use_index();
    memset(&Mode_Init,0,sizeof(Mode_Init));
#ifdef Exist_SYS_TIME
    Mode_Init.TIME = MODE_TIME_Init;
#endif

#ifdef Exist_UART
    Mode_Init.UART = MODE_UART_Init;
#endif
#ifdef Exist_USB
    Mode_Init.USB = USB_User_init;      // 来自Base
#endif
    
#ifdef Exist_LED
    Mode_Init.LED = MODE_LED_Init;
#endif
#ifdef Exist_LCD
    Mode_Init.LCD = MODE_LCD_Init;
#endif
#ifdef Exist_BZZ
    Mode_Init.BZZ = MODE_BZZ_Init;
#endif

#ifdef Exist_HC595
    Mode_Init.HC_595 = MODE_HC595_Init;
#endif
#ifdef Exist_HC138
    Mode_Init.HC_138 = MODE_HC138_Init;
#endif
#ifdef Exist_DS18B20
    Mode_Init.DS18B20 = MODE_DS18B20_Init;
#endif

#ifdef Exist_BUTTON
    Mode_Init.Button = MODE_Button_Init;
#endif
#ifdef Exist_Ultrasonic
    Mode_Init.Ultrasonic = MODE_Ultrasonic_Init;
#endif

#ifdef Exist_Voice
    Mode_Init.Voice = MODE_Voice_Init;
#endif
#ifdef Exist_Steering_Engine
    Mode_Init.Steering_Engine = MODE_Steering_Engine_Init;
#endif  

#ifdef Exist_ADC
    Mode_Init.User_ADC = Base_ADC_Init;
#endif

}   // Mode_Index

//--------------------------------//

void Debug_Out(uint8_t *data,int Length)        //选一个通信接口为Debug
{
#ifdef Exist_UART
    #ifdef DEBUG_OUT
    MODE_UART_Send_Data_Fun(DEBUG_OUT, data, Length);
    #endif

#endif
}
