#include <STC8.H>
#include "key.h"
#include "display.h"
#include "string.h"
#include "stdio.h"
#include "FPM10A.h"

void uart3_init()
{
	S3CON = 0x10;		//8位数据,可变波特率
	S3CON &= 0xBF;		//串口3选择定时器2为波特率发生器
	AUXR |= 0x04;		//定时器时钟1T模式
	T2L = 0x8F;		//设置定时初始值
	T2H = 0xFD;		//设置定时初始值
	AUXR |= 0x10;		//定时器2开始计时
}
void main()
{
	uart3_init();	
	OLED_Init();
	OLED_ColorTurn(0);    
	OLED_DisplayTurn(0);
	while(1)
	{	
		Key_Mode();			   //按键切换显示模式
		displaymode();		   	 //界面
		password_scan();		//密码输入函数
	}			
}
	