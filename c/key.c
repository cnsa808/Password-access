#include "key.h"
unsigned char Disxs[8];
static unsigned char BZ_1=0;
unsigned char password[8]={0,1,2,3,4,5,6,7};
extern unsigned char Not_Keymode;
unsigned char count=0,y=108;				  //count��ʾ����λ��
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
	unsigned char x=0;								/*��x����Ϊ�ֲ����������������н���ʱ��������Ϊ�����еı�����ջ�ϴ洢�����ݵõ��ͷţ��Ӷ�x�ᱻ�����*/						
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
										OLED_Clear();BZ_1++;						 //BZ_1�����ú�not_keymode������һ�������Ǳ�־λ��ֻ����ʾ����ʾ�ض�����һ�Σ�������ˢ�¶���˸
										OLED_ShowChinese(0,0,21,16);//��
										OLED_ShowChinese(37,0,22,16);//��
										OLED_ShowChinese(75,0,23,16);//��
										OLED_ShowChinese(112,0,24,16);//ȷ
										OLED_ShowChinese(2,2,27,16);//��
										OLED_ShowChinese(18,2,28,16);//��
										OLED_ShowChinese(36,2,31,16);//��
										OLED_ShowChinese(54,2,29,16);//��
										OLED_ShowChinese(72,2,30,16);//��
										OLED_ShowChinese(90,2,21,16);//��
										OLED_ShowChinese(108,2,22,16);//��
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
	}																/*Ϊ�˱����䵽�ڰ�λ����ʱֱ����ʾ������󣬼�һ��BZ_1��־λ��*/
	if(count>=8&&BZ_1==0)											/*���ڰ�λ�������������ж���ȷ����ô�������жϳ����֪BZ_1=1��������������޷�ִ�� ���������䣬�Ӷ������˵ڰ�λʱ��ʾ���ֽ����bug��*/
	{
		OLED_Clear();
		OLED_ShowChinese(0,0,21,16);	   //��
		OLED_ShowChinese(37,0,22,16);	   //�� 
		OLED_ShowChinese(75,0,32,16);	   //��
		OLED_ShowChinese(112,0,33,16);	   //��
		count=0;
		y=108;
		delay_ms(2000);
		Not_Keymode=0;	
	}	
}

void Key_Mode()				  //�����л�ģʽ
{
	unsigned char key_get;
	key_get=button_scan();
	if(key_get==10)
	{
			
	}
}
   















		    