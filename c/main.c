#include <STC8.H>
#include "key.h"
#include "display.h"
#include "string.h"
#include "stdio.h"
#include "FPM10A.h"

void uart3_init()
{
	S3CON = 0x10;		//8λ����,�ɱ䲨����
	S3CON &= 0xBF;		//����3ѡ��ʱ��2Ϊ�����ʷ�����
	AUXR |= 0x04;		//��ʱ��ʱ��1Tģʽ
	T2L = 0x8F;		//���ö�ʱ��ʼֵ
	T2H = 0xFD;		//���ö�ʱ��ʼֵ
	AUXR |= 0x10;		//��ʱ��2��ʼ��ʱ
}
void main()
{
	uart3_init();	
	OLED_Init();
	OLED_ColorTurn(0);    
	OLED_DisplayTurn(0);
	while(1)
	{	
		Key_Mode();			   //�����л���ʾģʽ
		displaymode();		   	 //����
		password_scan();		//�������뺯��
	}			
}
	