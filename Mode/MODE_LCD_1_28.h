#ifndef _MODE_LCD_1_28_H_
#define _MODE_LCD_1_28_H_

#include "Base.h"
#include "Caven_Type.h"

/*
    GC9A01оƬ��Բ��
    
*/

#define USE_HORIZONTAL 0 // ����Ĭ�Ϻ�������������ʾ 0��1Ϊ���� 2��3Ϊ����
#define LCD_W 240        // X MAX 240
#define LCD_H 240        // Y MAX 240

#ifndef LCD_CMD
#define LCD_CMD 0	// д����
#define LCD_DATA 1	// д����
#endif

extern U16  LCD_Back_Color; // ����ɫ
extern U16  LCD_Word_Color; // ����ɫ
extern U8   LCD_Horizontal; // ���ú�����������

//������ɫ
#define LCD_WHITE            0xFFFF
#define LCD_BLACK            0x0000
#define LCD_BLUE             0x001F
#define LCD_BRED             0XF81F
#define LCD_GRED             0XFFE0
#define LCD_GBLUE            0X07FF
#define LCD_RED              0xF800
#define LCD_MAGENTA          0xF81F
#define LCD_GREEN            0x07E0
#define LCD_CYAN             0x7FFF
#define LCD_YELLOW           0xFFE0
#define LCD_BROWN            0XBC40 //��ɫ
#define LCD_BRRED            0XFC07 //�غ�ɫ
#define LCD_GRAY             0X8430 //��ɫ
#define LCD_DARKBLUE         0X01CF //����ɫ
#define LCD_LIGHTBLUE        0X7D7C //ǳ��ɫ
#define LCD_GRAYBLUE         0X5458 //����ɫ
#define LCD_LIGHTGREEN       0X841F //ǳ��ɫ
#define LCD_LGRAY            0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ
#define LCD_LGRAYBLUE        0XA651 //ǳ����ɫ(�м����ɫ)
#define LCD_LBBLUE           0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)

typedef struct
{
    void (*Fill_pFun)(U16 x_sta, U16 y_sta, U16 x_end, U16 y_end, U16 color); //ָ�����������ɫ

    void (*Draw_Point_pFun)(U16 x, U16 y, U16 color);                       //��ָ��λ�û�һ����
    void (*Draw_Line_pFun)(U16 x1, U16 y1, U16 x2, U16 y2, U16 color);      //��ָ��λ�û�һ����
    void (*Draw_Circle_pFun)(U16 x0, U16 y0, char r, U16 color);            //��ָ��λ�û�һ��Բ
    void (*Draw_Rectangle_pFun)(U16 x1, U16 y1, U16 x2, U16 y2, U16 color); //��ָ��λ�û�һ������

    void (*Show_String_pFun)(U16 x, U16 y, const char *p, U16 coloer, U16 b_coloer, char Size);       //��ʾ�ַ���
    void (*Show_Chinese_pFun)(U16 x, U16 y, char *s, U16 coloer, U16 b_coloer, char Size, char mode); //��ʾ���ִ�
    void (*Show_Picture_pFun)(U16 x, U16 y, U16 length, U16 width, const unsigned char pic[]);        //��ʾͼƬ

    int (*Set_Direction_pFun)(char set);
}MODE_LCD_Way;

void LCD_Fill_Fun (U16 x_sta, U16 y_sta, U16 x_end, U16 y_end, U16 color); //ָ�����������ɫ
void LCD_Draw_Point(U16 x, U16 y, U16 color);                         //��ָ��λ�û�һ����
void LCD_Draw_Line(U16 x1, U16 y1, U16 x2, U16 y2, U16 color);        //��ָ��λ�û�һ����
void LCD_Draw_Circle(U16 x0, U16 y0, char r, U16 color);              //��ָ��λ�û�һ��Բ
void LCD_Draw_Rectangle(U16 x1, U16 y1, U16 x2, U16 y2, U16 color);   //��ָ��λ�û�һ������

void LCD_Show_String(U16 x, U16 y, const char *p, U16 coloer, U16 b_coloer, char Size);       //��ʾ�ַ���
void LCD_Show_Chinese(U16 x, U16 y, char *s, U16 coloer, U16 b_coloer, char Size, char mode); //��ʾ���ִ�
void LCD_Show_Picture(U16 x, U16 y, U16 length, U16 width, const unsigned char pic[]);        //��ʾͼƬ

int LCD_Set_Horizontal(char set);

int MODE_LCD_Init(int Sse); // LCD��ʼ��


#endif
