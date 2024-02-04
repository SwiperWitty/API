#include "MODE_LCD_1_28.h"
#include "lcdfont.h"        // �ֿ�

U16 LCD_Back_Color = 0xFFFB; 	// ����ɫ
U16 LCD_Word_Color = LCD_GRAY;
U8 	LCD_Horizontal = USE_HORIZONTAL;

#ifdef Exist_LCD
static void LCD_Writ_Bus(U8 dat)
{
    Base_SPI_Send_Data(m_SPI_CH2,dat);

}

/******************************************************************************
	  ����˵����LCDд������
	  ������ݣ�dat д�������
	  ����ֵ��  ��
******************************************************************************/
static void LCD_WR_DATA8(U8 dat)
{
	Base_SPI_CS_Set(m_SPI_CH2,1,ENABLE);
	LCD_Writ_Bus(dat);
	Base_SPI_CS_Set(m_SPI_CH2,1,DISABLE);
}

static void LCD_WR_DATA(U16 dat)
{
	Base_SPI_CS_Set(m_SPI_CH2,1,ENABLE);
	LCD_Writ_Bus(dat >> 8);
	LCD_Writ_Bus(dat & 0X00FF);
	Base_SPI_CS_Set(m_SPI_CH2,1,DISABLE);
}

/******************************************************************************
	  ����˵����LCDд������
	  ������ݣ�dat д�������
	  ����ֵ��  ��
******************************************************************************/
void LCD_Send_Data(U8 *Data,int num)
{
	Base_SPI_CS_Set(m_SPI_CH2,1,ENABLE);
	Base_SPI_DMA_Send_Data(m_SPI_CH2,Data,num);
//	Base_SPI_CS_Set(m_SPI_CH2,1,DISABLE);
}

/******************************************************************************
	  ����˵����LCDд������
	  ������ݣ�dat д�������
	  ����ֵ��  ��
******************************************************************************/
static void LCD_WR_CMD(U8 dat)
{
    Base_SPI_CS_Set(m_SPI_CH2,1,ENABLE);
	LCD_DC_L(); //д����
	LCD_Writ_Bus(dat);
	LCD_DC_H(); //д����	Ԥ��
    Base_SPI_CS_Set(m_SPI_CH2,1,DISABLE);
}

/******************************************************************************
	  ����˵����������ʼ�ͽ�����ַ
	  ������ݣ�x1,x2 �����е���ʼ�ͽ�����ַ
				y1,y2 �����е���ʼ�ͽ�����ַ
	  ����ֵ��  ��
******************************************************************************/
static void LCD_Address_Set(U16 x1, U16 y1, U16 x2, U16 y2)
{
	u16 x_sta,y_sta,x_end,y_end;

	if (LCD_Horizontal == 0)
	{
		x_sta = (x1);
		x_end = (x2);
		y_sta = (y1);
		y_end = (y2);
	}
	else if (LCD_Horizontal == 1)
	{
		x_sta = (x1);
		x_end = (x2);
		y_sta = (y1 + 80);
		y_end = (y2 + 80);
	}
	else if (LCD_Horizontal == 2)
	{
		x_sta = (x1);
		x_end = (x2);
		y_sta = (y1);
		y_end = (y2);
	}
	else
	{
		x_sta = (x1 + 80);
		x_end = (x2 + 80);
		y_sta = (y1);
		y_end = (y2);
	}

	LCD_WR_CMD(0x2a); // �е�ַ����
	LCD_WR_DATA(x_sta);
	LCD_WR_DATA(x_end);
	LCD_WR_CMD(0x2b); // �е�ַ����
	LCD_WR_DATA(y_sta);
	LCD_WR_DATA(y_end);
	LCD_WR_CMD(0x2c); // ������д
}
#endif
//���ϲ��ṩ�������ļ�

/******************************************************************************
	  ����˵������ָ�����������ɫ
	  ������ݣ�xsta,ysta   ��ʼ����
				xend,yend   ��ֹ����
								color       Ҫ������ɫ
	  ����ֵ��  ��
******************************************************************************/
void LCD_Fill_Fun(U16 x_sta, U16 y_sta, U16 x_end, U16 y_end, U16 color)
{
#ifdef Exist_LCD
    int i = (x_end - x_sta) * (y_end - y_sta);
	LCD_Address_Set(x_sta, y_sta, x_end - 1, y_end - 1); //������ʾ��Χ
    for(;i > 0;i--)
    {
        LCD_WR_DATA(color);
    }

#endif
}

/******************************************************************************
	  ����˵����������Ļ��ʾ����
	  ������ݣ�0��1Ϊ���� 2��3Ϊ����
				���������ֵ�������Ϊ��ѯ��ǰ��Ļ����
	  ����ֵ��  ���ص�ǰ��Ļ��ʾ����
******************************************************************************/
int LCD_Set_Horizontal(char set)
{
	int retval = 0;
#ifdef Exist_LCD
	if(set < 4)
	{
		LCD_Horizontal = set;
	}
	retval = LCD_Horizontal;
#endif
	return retval;
}

/******************************************************************************
	  ����˵������ָ��λ�û���
	  ������ݣ�x,y ��������
				color �����ɫ
	  ����ֵ��  ��
******************************************************************************/
void LCD_Draw_Point(U16 x, U16 y, U16 color)
{
#ifdef Exist_LCD
	LCD_Address_Set(x, y, x, y); //���ù��λ��
	LCD_WR_DATA(color);
#endif
}

/******************************************************************************
	  ����˵��������
	  ������ݣ�x1,y1   ��ʼ����
				x2,y2   ��ֹ����
				color   �ߵ���ɫ
	  ����ֵ��  ��
******************************************************************************/
void LCD_Draw_Line(U16 x1, U16 y1, U16 x2, U16 y2, U16 color)
{
#ifdef Exist_LCD
	U16 t;
	int xerr = 0, yerr = 0, delta_x, delta_y, distance;
	int incx, incy, uRow, uCol;
	delta_x = x2 - x1; //������������
	delta_y = y2 - y1;
	uRow = x1; //�����������
	uCol = y1;
	if (delta_x > 0)
		incx = 1; //���õ�������
	else if (delta_x == 0)
		incx = 0; //��ֱ��
	else
	{
		incx = -1;
		delta_x = -delta_x;
	}
	if (delta_y > 0)
		incy = 1;
	else if (delta_y == 0)
		incy = 0; //ˮƽ��
	else
	{
		incy = -1;
		delta_y = -delta_y;
	}
	if (delta_x > delta_y)
		distance = delta_x; //ѡȡ��������������
	else
		distance = delta_y;
	for (t = 0; t < distance + 1; t++)
	{
		LCD_Draw_Point(uRow, uCol, color); //����
		xerr += delta_x;
		yerr += delta_y;
		if (xerr > distance)
		{
			xerr -= distance;
			uRow += incx;
		}
		if (yerr > distance)
		{
			yerr -= distance;
			uCol += incy;
		}
	}
#endif
}

/******************************************************************************
	  ����˵����������
	  ������ݣ�x1,y1   ��ʼ����
				x2,y2   ��ֹ����
				color   ���ε���ɫ
	  ����ֵ��  ��
******************************************************************************/
void LCD_Draw_Rectangle(U16 x1, U16 y1, U16 x2, U16 y2, U16 color)
{
	LCD_Draw_Line(x1, y1, x2, y1, color);
	LCD_Draw_Line(x1, y1, x1, y2, color);
	LCD_Draw_Line(x1, y2, x2, y2, color);
	LCD_Draw_Line(x2, y1, x2, y2, color);
}

/******************************************************************************
	  ����˵������Բ
	  ������ݣ�x0,y0   Բ������
				r       �뾶
				color   Բ����ɫ
	  ����ֵ��  ��
******************************************************************************/
void LCD_Draw_Circle(U16 x0, U16 y0, char r, U16 color)
{
	int a, b;
	a = 0;
	b = r;
	while (a <= b)
	{
		LCD_Draw_Point(x0 - b, y0 - a, color); // 3
		LCD_Draw_Point(x0 + b, y0 - a, color); // 0
		LCD_Draw_Point(x0 - a, y0 + b, color); // 1
		LCD_Draw_Point(x0 - a, y0 - b, color); // 2
		LCD_Draw_Point(x0 + b, y0 + a, color); // 4
		LCD_Draw_Point(x0 + a, y0 - b, color); // 5
		LCD_Draw_Point(x0 + a, y0 + b, color); // 6
		LCD_Draw_Point(x0 - b, y0 + a, color); // 7
		a++;
		if ((a * a + b * b) > (r * r)) //�ж�Ҫ���ĵ��Ƿ��Զ
		{
			b--;
		}
	}
}

/******************************************************************************
	  ����˵������ʾ����24x24����
	  ������ݣ�x,y��ʾ����
				*s Ҫ��ʾ�ĺ���
				fc �ֵ���ɫ
				bc �ֵı���ɫ
				sizey �ֺ�
				mode:  0�ǵ���ģʽ  1����ģʽ
	  ����ֵ��  ��
******************************************************************************/
void LCD_Show_Chinese24x24(U16 x, U16 y, char *s, U16 fc, U16 bc, char sizey, char mode)
{
#ifdef STRING_CHN
	char i, j, m = 0;
	U16 k;
	U16 HZnum;		 //������Ŀ
	U16 TypefaceNum; //һ���ַ���ռ�ֽڴ�С
	U16 x0 = x;
	TypefaceNum = (sizey / 8 + ((sizey % 8) ? 1 : 0)) * sizey;
	HZnum = sizeof(tfont24) / sizeof(typFNT_GB24); //ͳ�ƺ�����Ŀ
	for (k = 0; k < HZnum; k++)
	{
		if ((tfont24[k].Index[0] == *(s)) && (tfont24[k].Index[1] == *(s + 1)))
		{
			LCD_Address_Set(x, y, x + sizey - 1, y + sizey - 1);
			for (i = 0; i < TypefaceNum; i++)
			{
				for (j = 0; j < 8; j++)
				{
					if (!mode) //�ǵ��ӷ�ʽ
					{
						if (tfont24[k].Msk[i] & (0x01 << j))
							LCD_WR_DATA(fc);
						else
							LCD_WR_DATA(bc);
						m++;
						if (m % sizey == 0)
						{
							m = 0;
							break;
						}
					}
					else //���ӷ�ʽ
					{
						if (tfont24[k].Msk[i] & (0x01 << j))
							LCD_Draw_Point(x, y, fc); //��һ����
						x++;
						if ((x - x0) == sizey)
						{
							x = x0;
							y++;
							break;
						}
					}
				}
			}
		}
		continue; //���ҵ���Ӧ�����ֿ������˳�����ֹ��������ظ�ȡģ����Ӱ��
	}
#endif
}

/******************************************************************************
	  ����˵������ʾ����32x32����
	  ������ݣ�x,y��ʾ����
				*s Ҫ��ʾ�ĺ���
				fc �ֵ���ɫ
				bc �ֵı���ɫ
				sizey �ֺ�
				mode:  0�ǵ���ģʽ  1����ģʽ
	  ����ֵ��  ��
******************************************************************************/
void LCD_Show_Chinese32x32(U16 x, U16 y, char *s, U16 fc, U16 bc, char sizey, char mode)
{
#ifdef STRING_CHN
	char i, j, m = 0;
	U16 k;
	U16 HZnum;		 //������Ŀ
	U16 TypefaceNum; //һ���ַ���ռ�ֽڴ�С
	U16 x0 = x;
	TypefaceNum = (sizey / 8 + ((sizey % 8) ? 1 : 0)) * sizey;
	HZnum = sizeof(tfont32) / sizeof(typFNT_GB32); //ͳ�ƺ�����Ŀ
	for (k = 0; k < HZnum; k++)
	{
		if ((tfont32[k].Index[0] == *(s)) && (tfont32[k].Index[1] == *(s + 1)))
		{
			LCD_Address_Set(x, y, x + sizey - 1, y + sizey - 1);
			for (i = 0; i < TypefaceNum; i++)
			{
				for (j = 0; j < 8; j++)
				{
					if (!mode) //�ǵ��ӷ�ʽ
					{
						if (tfont32[k].Msk[i] & (0x01 << j))
							LCD_WR_DATA(fc);
						else
							LCD_WR_DATA(bc);
						m++;
						if (m % sizey == 0)
						{
							m = 0;
							break;
						}
					}
					else //���ӷ�ʽ
					{
						if (tfont32[k].Msk[i] & (0x01 << j))
							LCD_Draw_Point(x, y, fc); //��һ����
						x++;
						if ((x - x0) == sizey)
						{
							x = x0;
							y++;
							break;
						}
					}
				}
			}
		}
		continue; //���ҵ���Ӧ�����ֿ������˳�����ֹ��������ظ�ȡģ����Ӱ��
	}
#endif
}

/******************************************************************************
	  ����˵������ʾ�����ַ�
	  ������ݣ�x,y��ʾ����
				num Ҫ��ʾ���ַ�
				fc �ֵ���ɫ
				bc �ֵı���ɫ
				sizey �ֺ�
				mode:  0�ǵ���ģʽ  1����ģʽ
	  ����ֵ��  ��
******************************************************************************/
void LCD_Show_Char(U16 x, U16 y, char num, U16 fc, U16 bc, char sizey, char mode)
{
#ifdef STRING_ASC
	char temp, sizex, t, m = 0;
	U16 i, TypefaceNum; //һ���ַ���ռ�ֽڴ�С
	U16 x0 = x;
	sizex = sizey / 2;
	TypefaceNum = (sizex / 8 + ((sizex % 8) ? 1 : 0)) * sizey;
	num = num - ' ';									 //�õ�ƫ�ƺ��ֵ
	LCD_Address_Set(x, y, x + sizex - 1, y + sizey - 1); //���ù��λ��
	for (i = 0; i < TypefaceNum; i++)
	{
		if (sizey == 16)
		{temp = ascii_1608[num][i];} //����8x16����
		else if (sizey == 24)
		{temp = ascii_2412[num][i];} //����12x24����
		else if (sizey == 32)
		{temp = ascii_3216[num][i];} //����16x32����
		else
		{return;}
		for (t = 0; t < 8; t++)
		{
			if (!mode) //�ǵ���ģʽ
			{
				if (temp & (0x01 << t))
				{LCD_WR_DATA(fc);}
				else
				{LCD_WR_DATA(bc);}
				m++;
				if (m % sizex == 0)
				{
					m = 0;
					break;
				}
			}
			else //����ģʽ
			{
				if (temp & (0x01 << t))
				{LCD_Draw_Point(x, y, fc);} //��һ����
				x++;
				if ((x - x0) == sizex)
				{
					x = x0;
					y++;
					break;
				}
			}
		}
	}
#endif
}
/*    ����Ϊ������С��Ԫ      */

/******************************************************************************
	  ����˵������ʾ���ִ�
	  ������ݣ�x,y��ʾ����
				*s Ҫ��ʾ�ĺ��ִ�
				fc �ֵ���ɫ
				bc �ֵı���ɫ
				sizey �ֺ� ��ѡ 24 32
				mode:  0�ǵ���ģʽ  1����ģʽ
	  ����ֵ��  ��
******************************************************************************/
void LCD_Show_Chinese(U16 x, U16 y, char *s, U16 fc, U16 bc, char sizey, char mode)
{
	while (*s != 0)
	{
		if (sizey == 24)
		{LCD_Show_Chinese24x24(x, y, s, fc, bc, sizey, mode);}
		else if (sizey == 32)
		{LCD_Show_Chinese32x32(x, y, s, fc, bc, sizey, mode);}
		else
		{return;}
		s += 2;
		x += sizey;
	}
}

/******************************************************************************
	  ����˵������ʾ�ַ���
	  ������ݣ�x,y��ʾ����
				*p Ҫ��ʾ���ַ���
				fc �ֵ���ɫ
				bc �ֵı���ɫ
				sizey �ֺ�
				mode:  0�ǵ���ģʽ  1����ģʽ
	  ����ֵ��  ��
******************************************************************************/
void LCD_Show_String(U16 x, U16 y, const char *p, U16 fc, U16 bc, char sizey)
{
	if (sizey == 16 || sizey == 24 || sizey == 32)
	{
		x *= (sizey / 2);
		y *= (sizey);
		if (x > LCD_W)
		{x = LCD_W;}
		if (y > LCD_H)
		{y = LCD_W;}
	}
	else
		return;

	while (*p != '\0')
	{
		LCD_Show_Char(x, y, *p, fc, bc, sizey, 0);
		x += sizey / 2;
		p++;
	}
}

/******************************************************************************
	  ����˵������ʾͼƬ
	  ������ݣ�x,y�������
				length ͼƬ����
				width  ͼƬ���
				pic[]  ͼƬ����
	  ����ֵ��  ��
******************************************************************************/
void LCD_Show_Picture(U16 x,U16 y,U16 length,U16 width,const U8 pic[])
{
#ifdef Exist_LCD
	u16 i,j;
	u32 k = 0;
	LCD_Address_Set(x,y,(x+length-1),(y+width-1));
	for(i=0;i<length;i++)
	{
		for(j=0;j<width;j++)
		{
			LCD_WR_DATA8(pic[k*2]);
			LCD_WR_DATA8(pic[k*2+1]);
			k++;
		}
		
	}
#endif
}

#ifdef Exist_LCD
static void LCD_Delay(int time)
{
	SYS_Base_Delay(time,10000);
}
#endif

int MODE_LCD_Init(int Set)
{
    int retval = 0;
#ifdef Exist_LCD
	LCD_GPIO_Init(Set);
    Base_SPI_Init(m_SPI_CH2,8,Set);
	LCD_Delay(500);
	
	LCD_WR_DATA8(0x00);
	LCD_Delay(500); // �ȴ���·��λ���

	#ifdef LCD_RES_L
	LCD_RES_L();
	LCD_Delay(200); //
	LCD_RES_H();
	LCD_Delay(100);
	#endif
	LCD_Set_Horizontal(USE_HORIZONTAL);

//************* Start Initial Sequence **********// 
//	LCD_BLK_Set();  //�򿪱���
//    delay_ms(100);
	
	LCD_WR_CMD(0xEF);
	LCD_WR_CMD(0xEB);
	LCD_WR_DATA8(0x14); 
	
    LCD_WR_CMD(0xFE);			 
	LCD_WR_CMD(0xEF); 

	LCD_WR_CMD(0xEB);	
	LCD_WR_DATA8(0x14); 

	LCD_WR_CMD(0x84);			
	LCD_WR_DATA8(0x40); 

	LCD_WR_CMD(0x85);			
	LCD_WR_DATA8(0xFF); 

	LCD_WR_CMD(0x86);			
	LCD_WR_DATA8(0xFF); 

	LCD_WR_CMD(0x87);			
	LCD_WR_DATA8(0xFF);

	LCD_WR_CMD(0x88);			
	LCD_WR_DATA8(0x0A);

	LCD_WR_CMD(0x89);			
	LCD_WR_DATA8(0x21); 

	LCD_WR_CMD(0x8A);			
	LCD_WR_DATA8(0x00); 

	LCD_WR_CMD(0x8B);			
	LCD_WR_DATA8(0x80); 

	LCD_WR_CMD(0x8C);			
	LCD_WR_DATA8(0x01); 

	LCD_WR_CMD(0x8D);			
	LCD_WR_DATA8(0x01); 

	LCD_WR_CMD(0x8E);			
	LCD_WR_DATA8(0xFF); 

	LCD_WR_CMD(0x8F);			
	LCD_WR_DATA8(0xFF); 


	LCD_WR_CMD(0xB6);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x20);

	LCD_WR_CMD(0x36);

	switch (LCD_Horizontal)
	{
	case 0:
		LCD_WR_DATA8(0x08);
		break;
	case 1:
		LCD_WR_DATA8(0xC8);
		break;
	case 2:
		LCD_WR_DATA8(0x68);
		break;
	default:
		LCD_WR_DATA8(0xA8);
		break;
	}
	LCD_WR_CMD(0x3A);			
	LCD_WR_DATA8(0x05); 


	LCD_WR_CMD(0x90);			
	LCD_WR_DATA8(0x08);
	LCD_WR_DATA8(0x08);
	LCD_WR_DATA8(0x08);
	LCD_WR_DATA8(0x08); 

	LCD_WR_CMD(0xBD);			
	LCD_WR_DATA8(0x06);
	
	LCD_WR_CMD(0xBC);			
	LCD_WR_DATA8(0x00);	

	LCD_WR_CMD(0xFF);			
	LCD_WR_DATA8(0x60);
	LCD_WR_DATA8(0x01);
	LCD_WR_DATA8(0x04);

	LCD_WR_CMD(0xC3);			
	LCD_WR_DATA8(0x13);
	LCD_WR_CMD(0xC4);			
	LCD_WR_DATA8(0x13);

	LCD_WR_CMD(0xC9);			
	LCD_WR_DATA8(0x22);

	LCD_WR_CMD(0xBE);			
	LCD_WR_DATA8(0x11); 

	LCD_WR_CMD(0xE1);			
	LCD_WR_DATA8(0x10);
	LCD_WR_DATA8(0x0E);

	LCD_WR_CMD(0xDF);			
	LCD_WR_DATA8(0x21);
	LCD_WR_DATA8(0x0c);
	LCD_WR_DATA8(0x02);

	LCD_WR_CMD(0xF0);   
	LCD_WR_DATA8(0x45);
	LCD_WR_DATA8(0x09);
	LCD_WR_DATA8(0x08);
	LCD_WR_DATA8(0x08);
	LCD_WR_DATA8(0x26);
 	LCD_WR_DATA8(0x2A);

 	LCD_WR_CMD(0xF1);    
 	LCD_WR_DATA8(0x43);
 	LCD_WR_DATA8(0x70);
 	LCD_WR_DATA8(0x72);
 	LCD_WR_DATA8(0x36);
 	LCD_WR_DATA8(0x37);  
 	LCD_WR_DATA8(0x6F);


 	LCD_WR_CMD(0xF2);   
 	LCD_WR_DATA8(0x45);
 	LCD_WR_DATA8(0x09);
 	LCD_WR_DATA8(0x08);
 	LCD_WR_DATA8(0x08);
 	LCD_WR_DATA8(0x26);
 	LCD_WR_DATA8(0x2A);

 	LCD_WR_CMD(0xF3);   
 	LCD_WR_DATA8(0x43);
 	LCD_WR_DATA8(0x70);
 	LCD_WR_DATA8(0x72);
 	LCD_WR_DATA8(0x36);
 	LCD_WR_DATA8(0x37); 
 	LCD_WR_DATA8(0x6F);

	LCD_WR_CMD(0xED);	
	LCD_WR_DATA8(0x1B); 
	LCD_WR_DATA8(0x0B); 

	LCD_WR_CMD(0xAE);			
	LCD_WR_DATA8(0x77);
	
	LCD_WR_CMD(0xCD);			
	LCD_WR_DATA8(0x63);		


	LCD_WR_CMD(0x70);			
	LCD_WR_DATA8(0x07);
	LCD_WR_DATA8(0x07);
	LCD_WR_DATA8(0x04);
	LCD_WR_DATA8(0x0E); 
	LCD_WR_DATA8(0x0F); 
	LCD_WR_DATA8(0x09);
	LCD_WR_DATA8(0x07);
	LCD_WR_DATA8(0x08);
	LCD_WR_DATA8(0x03);

	LCD_WR_CMD(0xE8);			
	LCD_WR_DATA8(0x34);

	LCD_WR_CMD(0x62);			
	LCD_WR_DATA8(0x18);
	LCD_WR_DATA8(0x0D);
	LCD_WR_DATA8(0x71);
	LCD_WR_DATA8(0xED);
	LCD_WR_DATA8(0x70); 
	LCD_WR_DATA8(0x70);
	LCD_WR_DATA8(0x18);
	LCD_WR_DATA8(0x0F);
	LCD_WR_DATA8(0x71);
	LCD_WR_DATA8(0xEF);
	LCD_WR_DATA8(0x70); 
	LCD_WR_DATA8(0x70);

	LCD_WR_CMD(0x63);			
	LCD_WR_DATA8(0x18);
	LCD_WR_DATA8(0x11);
	LCD_WR_DATA8(0x71);
	LCD_WR_DATA8(0xF1);
	LCD_WR_DATA8(0x70); 
	LCD_WR_DATA8(0x70);
	LCD_WR_DATA8(0x18);
	LCD_WR_DATA8(0x13);
	LCD_WR_DATA8(0x71);
	LCD_WR_DATA8(0xF3);
	LCD_WR_DATA8(0x70); 
	LCD_WR_DATA8(0x70);

	LCD_WR_CMD(0x64);			
	LCD_WR_DATA8(0x28);
	LCD_WR_DATA8(0x29);
	LCD_WR_DATA8(0xF1);
	LCD_WR_DATA8(0x01);
	LCD_WR_DATA8(0xF1);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x07);

	LCD_WR_CMD(0x66);			
	LCD_WR_DATA8(0x3C);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0xCD);
	LCD_WR_DATA8(0x67);
	LCD_WR_DATA8(0x45);
	LCD_WR_DATA8(0x45);
	LCD_WR_DATA8(0x10);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x00);

	LCD_WR_CMD(0x67);			
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x3C);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x01);
	LCD_WR_DATA8(0x54);
	LCD_WR_DATA8(0x10);
	LCD_WR_DATA8(0x32);
	LCD_WR_DATA8(0x98);

	LCD_WR_CMD(0x74);			
	LCD_WR_DATA8(0x10);	
	LCD_WR_DATA8(0x85);	
	LCD_WR_DATA8(0x80);
	LCD_WR_DATA8(0x00); 
	LCD_WR_DATA8(0x00); 
	LCD_WR_DATA8(0x4E);
	LCD_WR_DATA8(0x00);					
	
    LCD_WR_CMD(0x98);			
	LCD_WR_DATA8(0x3e);
	LCD_WR_DATA8(0x07);

	LCD_WR_CMD(0x35);	
	LCD_WR_CMD(0x21);

	LCD_WR_CMD(0x11);
	LCD_Delay(120);
	LCD_WR_CMD(0x29);
	LCD_Delay(20);
	LCD_Fill_Fun (0, 0, LCD_W, LCD_H, LCD_Back_Color);
    retval = 1;
#endif
    return retval;
}
