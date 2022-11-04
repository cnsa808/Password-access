#include "key.h"
unsigned char Disxs[8];
static unsigned char BZ_1=0;
unsigned char password[8]={0,1,2,3,4,5,6,7};
extern unsigned char Not_Keymode;
unsigned char count=0,y=108;				  //count表示密码位数
code unsigned char seven_seg[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
code unsigned char p2k[]={0x7f,0xbf,0xdf,0xef};
code unsigned char sixteen[]={0xee,0xde,0xbe,0x7e,0xed,0xdd,0xbd,0x7d,0xeb,0xdb,0xbb,0x7b,0xe7,0xd7,0xb7,0x77};
unsigned char button_scan()
{
	unsigned char i,j,n;
	P2=0xff;
	for(i=0;i<=3;i++)
	{	
		P2=p2k[i];
		if(P2!=p2k[i])
		{	
			if(P2!=p2k[i])
			{
			  	for(j=0;j<16;j++)
				{
					if(P2==sixteen[j])
					{
						delay_ms(50);
						while(P2!=p2k[i]);	
						n=j;
					}
				}
			}	
		}			
	}
	return(n);		          	
}
void password_scan()
{
	unsigned char x=0;								/*将x定义为局部变量，当函数运行结束时，编译器为函数中的变量在栈上存储的数据得到释放，从而x会被清除。*/						
	x=button_scan();
	if(x<10&&Not_Keymode==1)
	{
		 Disxs[count]=x;
		 count++;
		 OLED_ShowString(y,6,"*",16);
		 y-=8;
	}
	if(x<10)
	{
		if(Disxs[0]==password[0])
		{
			if(Disxs[1]==password[1])
			{
				if(Disxs[2]==password[2])
				{
					if(Disxs[3]==password[3])
					{
						if(Disxs[4]==password[4])
						{
							if(Disxs[5]==password[5])
							{
								if(Disxs[6]==password[6])
								{
									if(Disxs[7]==password[7]&&BZ_1<1)
									{
										OLED_Clear();BZ_1++;						 //BZ_1的作用和not_keymode的作用一样，都是标志位，只让显示屏显示特定界面一次，避免多次刷新而闪烁
										OLED_ShowChinese(0,0,21,16);//密
										OLED_ShowChinese(37,0,22,16);//码
										OLED_ShowChinese(75,0,23,16);//正
										OLED_ShowChinese(112,0,24,16);//确
										OLED_ShowChinese(2,2,27,16);//长
										OLED_ShowChinese(18,2,28,16);//按
										OLED_ShowChinese(36,2,31,16);//可
										OLED_ShowChinese(54,2,29,16);//修
										OLED_ShowChinese(72,2,30,16);//改
										OLED_ShowChinese(90,2,21,16);//密
										OLED_ShowChinese(108,2,22,16);//码
										OLED_ShowString(32,5,">",16);
										OLED_ShowChinese(40,5,51,16);
										OLED_ShowChinese(56,5,52,16);
										OLED_ShowChinese(72,5,53,16);
										OLED_ShowString(86,5,"<",16);
										delay_ms(2000);
										Not_Keymode=2;
									}
								}
							}
						}
					}
				}
			}
		}
	}																/*为了避免输到第八位密码时直接显示密码错误，加一个BZ_1标志位。*/
	if(count>=8&&BZ_1==0)											/*当第八位密码输入后，如果判断正确，那么由上述判断程序可知BZ_1=1；接下来程序便无法执行 密码错误语句，从而消除了第八位时显示两种界面的bug。*/
	{
		OLED_Clear();
		OLED_ShowChinese(0,0,21,16);	   //密
		OLED_ShowChinese(37,0,22,16);	   //码 
		OLED_ShowChinese(75,0,32,16);	   //错
		OLED_ShowChinese(112,0,33,16);	   //误
		count=0;
		y=108;
		delay_ms(2000);
		Not_Keymode=0;	
	}	
}

void Key_Mode()				  //按键切换模式
{
	unsigned char key_get;
	key_get=button_scan();
	if(key_get==10)
	{
			
	}
}
   















		    