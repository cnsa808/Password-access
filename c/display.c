#include "STC8.H"
#include "key.h"  
#include "display.h"
#include "displayfont.h"  	 
unsigned char Not_Keymode; 	   				   //非按键切换模式，用来给非按键操控界面添加标志位。让某一界面只运行一次，从而消除多次运行产生的闪烁。
void displaymode()
{
	if(Not_Keymode==0)
	{	
		OLED_Clear();Not_Keymode++;
		OLED_ShowChinese(0,0,11,16);//欢
		OLED_ShowChinese(37,0,12,16);//迎
		OLED_ShowChinese(75,0,13,16);//使
		OLED_ShowChinese(112,0,14,16);//用
		OLED_ShowChinese(2,2,15,16);//多
		OLED_ShowChinese(18,2,16,16);//功
		OLED_ShowChinese(36,2,17,16);//能
		OLED_ShowChinese(54,2,7,16);//智
		OLED_ShowChinese(72,2,8,16);//能
		OLED_ShowChinese(90,2,9,16);//门
		OLED_ShowChinese(108,2,10,16);//锁
		OLED_ShowChinese(12,4,18,16);//请
		OLED_ShowChinese(32,4,19,16);//输
		OLED_ShowChinese(52,4,20,16);//入
		OLED_ShowChinese(72,4,21,16);//密
		OLED_ShowChinese(92,4,22,16);//码
		OLED_ShowString(112,4,":",16);
	}
	if(Not_Keymode==2)
	{
		OLED_Clear();Not_Keymode++;
		OLED_ShowNum(0,2,2,1,16);
		OLED_ShowChinese(32,2,35,16);//搜索指纹
		OLED_ShowChinese(52,2,36,16);
		OLED_ShowChinese(72,2,37,16);
		OLED_ShowChinese(92,2,38,16);
		OLED_ShowNum(0,0,1,1,16);
		OLED_ShowChinese(32,0,39,16);//增加指纹
		OLED_ShowChinese(52,0,40,16);
		OLED_ShowChinese(72,0,37,16);
		OLED_ShowChinese(92,0,38,16);	
		OLED_ShowNum(0,4,3,1,16);
		OLED_ShowChinese(32,4,41,16);//删除指纹
		OLED_ShowChinese(52,4,42,16);
		OLED_ShowChinese(72,4,37,16);
		OLED_ShowChinese(92,4,38,16);		
	}	
}



                                  
								  
								  
	
	
	
	
							 /**上方空白处用户可自行添加需要函数以及代码和变量*****************************/
							/*************************官方驱动代码！！！！！！！！！！***************************/

void delay_ms(unsigned int ms)
{                         
	xdata unsigned int a;
	while(ms)
	{
		a=1800;
		while(a--);
		ms--;
	}
	return;
}

void OLED_ColorTurn(u8 i)
{
	if(i==0)
		{
			OLED_WR_Byte(0xA6,OLED_CMD);
		}
	if(i==1)
		{
			OLED_WR_Byte(0xA7,OLED_CMD);
		}
}


void OLED_DisplayTurn(u8 i)
{
	if(i==0)
		{
			OLED_WR_Byte(0xC8,OLED_CMD);
			OLED_WR_Byte(0xA1,OLED_CMD);
		}
	if(i==1)
		{
			OLED_WR_Byte(0xC0,OLED_CMD);
			OLED_WR_Byte(0xA0,OLED_CMD);
		}
}



void IIC_delay(void)
{
	xdata u8 t=1;
	while(t--);
}

void I2C_Start(void)
{
	OLED_SDA_Set();
	OLED_SCL_Set();
	IIC_delay();
	OLED_SDA_Clr();
	IIC_delay();
	OLED_SCL_Clr();
	 
}

void I2C_Stop(void)
{
	OLED_SDA_Clr();
	OLED_SCL_Set();
	IIC_delay();
	OLED_SDA_Set();
}

void I2C_WaitAck(void) 
{
	OLED_SDA_Set();
	IIC_delay();
	OLED_SCL_Set();
	IIC_delay();
	OLED_SCL_Clr();
	IIC_delay();
}


void Send_Byte(u8 dat)
{
	xdata u8 i;
	for(i=0;i<8;i++)
	{
		OLED_SCL_Clr();
		if(dat&0x80)
		{
			OLED_SDA_Set();
    }
		else
		{
			OLED_SDA_Clr();
    }
		IIC_delay();
		OLED_SCL_Set();
		IIC_delay();
		OLED_SCL_Clr();
		dat<<=1;
  }
}


void OLED_WR_Byte(u8 dat,u8 mode)
{
	I2C_Start();
	Send_Byte(0x78);
	I2C_WaitAck();
	if(mode){Send_Byte(0x40);}
  else{Send_Byte(0x00);}
	I2C_WaitAck();
	Send_Byte(dat);
	I2C_WaitAck();
	I2C_Stop();
}



void OLED_Set_Pos(u8 x, u8 y) 
{ 
	OLED_WR_Byte(0xb0+y,OLED_CMD);
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((x&0x0f),OLED_CMD);
}   	  
   
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  
	OLED_WR_Byte(0X14,OLED_CMD);  
	OLED_WR_Byte(0XAF,OLED_CMD); 
}
    
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  
	OLED_WR_Byte(0X10,OLED_CMD); 
	OLED_WR_Byte(0XAE,OLED_CMD); 
}		   			 
 
void OLED_Clear(void)  
{  
	xdata u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);  
		OLED_WR_Byte (0x00,OLED_CMD);      
		OLED_WR_Byte (0x10,OLED_CMD);     
		for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA); 
	} 
}




void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 sizey)
{      	
	xdata u8 c=0,sizex=sizey/2;
	xdata u16 i=0,size1;
	if(sizey==8)size1=6;
	else size1=(sizey/8+((sizey%8)?1:0))*(sizey/2);
	c=chr-' ';
	OLED_Set_Pos(x,y);
	for(i=0;i<size1;i++)
	{
		if(i%sizex==0&&sizey!=8) OLED_Set_Pos(x,y++);
		if(sizey==8) OLED_WR_Byte(asc2_0806[c][i],OLED_DATA);
		else if(sizey==16) OLED_WR_Byte(asc2_1608[c][i],OLED_DATA);

		else return;
	}
}

u32 oled_pow(u8 m,u8 n)
{
		xdata u32 result=1;	 
	while(n--)result*=m;    
	return result;
}				  
	  
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 sizey)
{         	
	xdata u8 t,temp,m=0;
	xdata u8 enshow=0;
	if(sizey==8)m=2;
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(sizey/2+m)*t,y,' ',sizey);
				continue;
			}else enshow=1;
		}
	 	OLED_ShowChar(x+(sizey/2+m)*t,y,temp+'0',sizey);
	}
}

void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 sizey)
{
	xdata u8 j=0;
	while (chr[j]!='\0')
	{		
		OLED_ShowChar(x,y,chr[j++],sizey);
		if(sizey==8)x+=6;
		else x+=sizey/2;
	}
}

void OLED_ShowChinese(u8 x,u8 y,u8 no,u8 sizey)
{
	 xdata u16 i,size1=(sizey/8+((sizey%8)?1:0))*sizey;
	for(i=0;i<size1;i++)
	{
		if(i%sizey==0) OLED_Set_Pos(x,y++);
		if(sizey==16) OLED_WR_Byte(Hzk[no][i],OLED_DATA);//16x16???
//		else if(sizey==xx) OLED_WR_Byte(xxx[c][i],OLED_DATA);//??????????
		else return;
	}				
}


//?????
//x,y???????
//sizex,sizey,??????
//BMP??????????
void OLED_DrawBMP(u8 x,u8 y,u8 sizex, u8 sizey,u8 BMP[])
{ 	
  xdata u16 j=0;
	xdata u8 i,m;
	sizey=sizey/8+((sizey%8)?1:0);
	for(i=0;i<sizey;i++)
	{
		OLED_Set_Pos(x,i+y);
    for(m=0;m<sizex;m++)
		{      
			OLED_WR_Byte(BMP[j++],OLED_DATA);	    	
		}
	}
} 



//?????				    
void OLED_Init(void)
{
	OLED_RES_Clr();
  delay_ms(200);
	OLED_RES_Set();
	
	OLED_WR_Byte(0xAE,OLED_CMD);//--turn off oled panel
	OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
	OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WR_Byte(0x81,OLED_CMD);//--set contrast control register
	OLED_WR_Byte(0xCF,OLED_CMD); // Set SEG Output Current Brightness
	OLED_WR_Byte(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0??????? 0xa1????
	OLED_WR_Byte(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0???·??? 0xc8????
	OLED_WR_Byte(0xA6,OLED_CMD);//--set normal display
	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3f,OLED_CMD);//--1/64 duty
	OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WR_Byte(0x00,OLED_CMD);//-not offset
	OLED_WR_Byte(0xd5,OLED_CMD);//--set display clock divide ratio/oscillator frequency
	OLED_WR_Byte(0x80,OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WR_Byte(0xD9,OLED_CMD);//--set pre-charge period
	OLED_WR_Byte(0xF1,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WR_Byte(0xDA,OLED_CMD);//--set com pins hardware configuration
	OLED_WR_Byte(0x12,OLED_CMD);
	OLED_WR_Byte(0xDB,OLED_CMD);//--set vcomh
	OLED_WR_Byte(0x40,OLED_CMD);//Set VCOM Deselect Level
	OLED_WR_Byte(0x20,OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WR_Byte(0x02,OLED_CMD);//
	OLED_WR_Byte(0x8D,OLED_CMD);//--set Charge Pump enable/disable
	OLED_WR_Byte(0x14,OLED_CMD);//--set(0x10) disable
	OLED_WR_Byte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
	OLED_WR_Byte(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7) 
	OLED_Clear();
	OLED_WR_Byte(0xAF,OLED_CMD); /*display ON*/ 
}

	 




