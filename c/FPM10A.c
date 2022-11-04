#include"FPM10A.h"
 unsigned char FPM10A_RECEICE_BUFFER[32];
unsigned int finger_id = 0;
void Uart_Send_Byte(unsigned char c)
{
	S3BUF=c;
	while(!(S3CON&0x02));
	S3CON&=~0x02;
}

unsigned char Uart_Receive_Byte()//UART Receive a byteg
{	
xdata	unsigned char dat;
	while(!(S3CON&0x01));	 //接收完为1 
	S3CON&= ~0x01;
	dat = S3BUF;
	
	return (dat);
	
}

void Delay_Us(unsigned int i)
{
	while(--i);
}

//FINGERPRINT通信协议定义

code unsigned char FPM10A_Get_Device[10] ={0x01,0x00,0x07,0x13,0x00,0x00,0x00,0x00,0x00,0x1b};//口令验证
code unsigned char FPM10A_Pack_Head[6] = {0xEF,0x01,0xFF,0xFF,0xFF,0xFF};  //协议包头
code unsigned char FPM10A_Get_Img[6] = {0x01,0x00,0x03,0x01,0x00,0x05};    //获得指纹图像
code unsigned char FPM10A_Get_Templete_Count[6] ={0x01,0x00,0x03,0x1D,0x00,0x21 }; //获得模版总数
code unsigned char FPM10A_Search[11]={0x01,0x00,0x08,0x04,0x01,0x00,0x00,0x03,0xE7,0x00,0xF8}; //搜索指纹搜索范围0 - 999,使用BUFFER1中的特征码搜索
code unsigned char FPM10A_Search_0_9[11]={0x01,0x00,0x08,0x04,0x01,0x00,0x00,0x00,0x13,0x00,0x21}; //搜索0-9号指纹
code unsigned char FPM10A_Img_To_Buffer1[7]={0x01,0x00,0x04,0x02,0x01,0x00,0x08}; //将图像放入到BUFFER1
code unsigned char FPM10A_Img_To_Buffer2[7]={0x01,0x00,0x04,0x02,0x02,0x00,0x09}; //将图像放入到BUFFER2
code unsigned char FPM10A_Reg_Model[6]={0x01,0x00,0x03,0x05,0x00,0x09}; //将BUFFER1跟BUFFER2合成特征模版
code unsigned char FPM10A_Delete_All_Model[6]={0x01,0x00,0x03,0x0d,0x00,0x11};//删除指纹模块里所有的模版
volatile unsigned char  FPM10A_Save_Finger[9]={0x01,0x00,0x06,0x06,0x01,0x00,0x0B,0x00,0x19};//将BUFFER1中的特征码存放到指定的位置
//volatile:系统总是重新从它所在的内存读取数据，即使它前面的指令刚刚从该处读取过数据
/*------------------ FINGERPRINT命令字 --------------------------*/
 //发送包头
void FPM10A_Cmd_Send_Pack_Head(void)
{
	xdata int i;	
	for(i=0;i<6;i++) //包头
   {
     Uart_Send_Byte(FPM10A_Pack_Head[i]);   
    }		
}
//发送指令
void FPM10A_Cmd_Check(void)
{
	xdata int i=0;
	FPM10A_Cmd_Send_Pack_Head(); //发送通信协议包头
	for(i=0;i<10;i++)
	 {		
		Uart_Send_Byte(FPM10A_Get_Device[i]);
	  }
}
//接收反馈数据缓冲
void FPM10A_Receive_Data(unsigned char ucLength)
{
  xdata unsigned char i;

  for (i=0;i<ucLength;i++)
     FPM10A_RECEICE_BUFFER[i] = Uart_Receive_Byte();

}

//FINGERPRINT_获得指纹图像命令
void FPM10A_Cmd_Get_Img(void)
{
    unsigned char i;
    FPM10A_Cmd_Send_Pack_Head(); //发送通信协议包头
    for(i=0;i<6;i++) //发送命令 0x1d
	{
       Uart_Send_Byte(FPM10A_Get_Img[i]);
	}
}
//讲图像转换成特征码存放在Buffer1中
void FINGERPRINT_Cmd_Img_To_Buffer1(void)
{
 	unsigned char i;
	FPM10A_Cmd_Send_Pack_Head(); //发送通信协议包头      
   	for(i=0;i<7;i++)   //发送命令 将图像转换成 特征码 存放在 CHAR_buffer1
     {
      Uart_Send_Byte(FPM10A_Img_To_Buffer1[i]);
   	  }
}
//将图像转换成特征码存放在Buffer2中
void FINGERPRINT_Cmd_Img_To_Buffer2(void)
{
     unsigned char i;
     for(i=0;i<6;i++)    //发送包头
	 {
    	Uart_Send_Byte(FPM10A_Pack_Head[i]);   
   	 }
     for(i=0;i<7;i++)   //发送命令 将图像转换成 特征码 存放在 CHAR_buffer1
      {
      	Uart_Send_Byte(FPM10A_Img_To_Buffer2[i]);
   	  }
}
//搜索全部用户999枚
void FPM10A_Cmd_Search_Finger(void)
{
       unsigned char i;	   	    
			 FPM10A_Cmd_Send_Pack_Head(); //发送通信协议包头
       for(i=0;i<11;i++)
           {
    	      Uart_Send_Byte(FPM10A_Search[i]);   
   		   }
}

void FPM10A_Cmd_Reg_Model(void)
{
       unsigned char i;	   
	    
			 FPM10A_Cmd_Send_Pack_Head(); //发送通信协议包头

       for(i=0;i<6;i++)
           {
    	      Uart_Send_Byte(FPM10A_Reg_Model[i]);   
   		   }


}
//删除指纹模块里的所有指纹模版
void FINGERPRINT_Cmd_Delete_All_Model(void)
{
     unsigned char i;    
    for(i=0;i<6;i++) //包头
      Uart_Send_Byte(FPM10A_Pack_Head[i]);   
    for(i=0;i<6;i++) //命令合并指纹模版
	   {
      Uart_Send_Byte(FPM10A_Delete_All_Model[i]);   
		 }	
}
//保存指纹
void FPM10A_Cmd_Save_Finger( unsigned int storeID )
{
       unsigned long temp = 0;
		   unsigned char i;
       FPM10A_Save_Finger[5] =(storeID&0xFF00)>>8;
       FPM10A_Save_Finger[6] = (storeID&0x00FF);
		   for(i=0;i<7;i++)   //计算校验和
		   	   temp = temp + FPM10A_Save_Finger[i]; 
		   FPM10A_Save_Finger[7]=(temp & 0x00FF00) >> 8; //存放校验数据
		   FPM10A_Save_Finger[8]= temp & 0x0000FF;		   
       FPM10A_Cmd_Send_Pack_Head(); //发送通信协议包头	
       for(i=0;i<9;i++)  
      		Uart_Send_Byte(FPM10A_Save_Finger[i]);      //发送命令 将图像转换成 特征码 存放在 CHAR_buffer1
}
//添加指纹
void FPM10A_Add_Fingerprint()
{
	unsigned char id_show[]={0,0,0};
	OLED_Clear(); //清屏
finger_id=0;  
	while(1)
	{
		OLED_ShowNum(0,2,2,1,16);
	OLED_ShowChinese(65,2,43,16);//返回
	OLED_ShowChinese(85,2,44,16);
	OLED_ShowNum(0,0,1,1,16);
	OLED_ShowChinese(32,0,39,16);//增加id
	OLED_ShowChinese(52,0,40,16);
	OLED_ShowString(72,0,"id",16);
	OLED_ShowNum(104,0,finger_id,3,16);
	OLED_ShowNum(0,4,3,1,16);
	OLED_ShowChinese(65,4,39,16);
	OLED_ShowChinese(85,4,40,16);
	if(P22 == 0) 
	{
		 while(P22==0);
							 OLED_Clear();
	P2=0x7f;
	OLED_ShowNum(0,2,2,1,16);
	OLED_ShowChinese(32,2,35,16);//收索指纹
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
	OLED_ShowNum(0,6,4,1,16);
	OLED_ShowChinese(42,6,43,16);//返回
	OLED_ShowChinese(82,6,44,16);
		 break;
	}

	//按切换键指纹iD值加1
	if(P23 == 0)
	{
		while(P23==0);
		if(finger_id == 1000)
		{
			finger_id = 0;
		}
		else
		finger_id = finger_id + 1;
	}

	 //按确认键开始录入指纹信息 		 			
	 if(P21 == 0)
	  {	
			  while(P21==0);
				OLED_Clear();
			while(P22 == 1)
		   {
			  //按下返回键退出录入返回fingerID调整状态   
				if(P22 == 0) 
				 {
				  while(P22==0);
				  break;
				  }	
	OLED_ShowChinese(32,0,45,16);//
	OLED_ShowChinese(52,0,46,16);
	OLED_ShowChinese(72,0,47,16);
	OLED_ShowChinese(92,0,48,16);	
				FPM10A_Cmd_Get_Img(); //获得指纹图像
				FPM10A_Receive_Data(12);		
			
				//判断接收到的确认码,等于0指纹获取成功
				if(FPM10A_RECEICE_BUFFER[9]==0)
				 {	
					 OLED_ShowString(30,4,"one",16);
					Delay_Us(100*150);
					FINGERPRINT_Cmd_Img_To_Buffer1();
				    FPM10A_Receive_Data(12);
					Delay_Us(50000);

					while(1)
					{
						if(P22 == 0) 
						{
							while(P22==0);
							break;
						}
					 FPM10A_Cmd_Get_Img(); //获得指纹图像
					 FPM10A_Receive_Data(12);
					//判断接收到的确认码,等于0指纹获取成功

					if(FPM10A_RECEICE_BUFFER[9]==0)
					{			
						OLED_ShowString(30,4,"two ok",16);
						Delay_Us(15000);

						FINGERPRINT_Cmd_Img_To_Buffer2();
				  		FPM10A_Receive_Data(12);
						FPM10A_Cmd_Reg_Model();//转换成特征码
	         			FPM10A_Receive_Data(12); 
					  	FPM10A_Cmd_Save_Finger(finger_id);                		         
	          			FPM10A_Receive_Data(12);
						
						finger_id=finger_id+1;
						Delay_Us(50000);
							OLED_Clear(); //清屏		
	OLED_ShowChinese(25,4,49,16);
	OLED_ShowChinese(45,4,50,16);
							break;
				    	
				  	}
					
				   }
	        break;
					}
				}
//			ClrScreen(); //清空显示屏
			}
		//	Delay_Ms(500);
		}
}

//搜索指纹
void FPM10A_Find_Fingerprint()
{

	idata unsigned int find_fingerid = 0;
	idata unsigned char id_show[]={0,0,0};
	
	OLED_Clear();
	OLED_ShowChinese(32,0,45,16);
	OLED_ShowChinese(52,0,49,16);
	OLED_ShowChinese(72,0,47,16);
	OLED_ShowChinese(92,0,48,16);	
	OLED_ShowNum(0,2,2,1,16);
	OLED_ShowChinese(65,2,43,16);//返回
	OLED_ShowChinese(85,2,44,16);		
	do
	{
	
	
		FPM10A_Cmd_Get_Img(); //获得指纹图像
		FPM10A_Receive_Data(12);		
			
		//判断接收到的确认码,等于0指纹获取成功
		if(FPM10A_RECEICE_BUFFER[9]==0)
		{			
			
			Delay_Us(15000);
			FINGERPRINT_Cmd_Img_To_Buffer1();
			FPM10A_Receive_Data(12);		
			FPM10A_Cmd_Search_Finger();
			FPM10A_Receive_Data(16);			
			if(FPM10A_RECEICE_BUFFER[9] == 0) //搜索到  
			{
				OLED_Clear();	
				
		OLED_ShowChinese(75,2,23,16);//正
		OLED_ShowChinese(112,2,24,16);//确				
				//拼接指纹ID数
				find_fingerid = FPM10A_RECEICE_BUFFER[10]*256 + FPM10A_RECEICE_BUFFER[11];					
			
				Delay_Us(2000);				
			   }
				else //没有找到
				{
					OLED_Clear();

					OLED_ShowChinese(75,2,32,16);//错
			OLED_ShowChinese(112,2,33,16);//误	
					
				}
			}

		}while(P22 == 1);
		OLED_Clear();
		OLED_ShowNum(0,2,2,1,16);
	OLED_ShowChinese(32,2,35,16);//收索指纹
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
	OLED_ShowNum(0,6,4,1,16);
	OLED_ShowChinese(42,6,43,16);//返回
	OLED_ShowChinese(82,6,44,16);
}
//删除所有存贮的指纹库
void FPM10A_Delete_All_Fingerprint()
{
		unsigned char i=0;
	OLED_Clear();
		OLED_ShowNum(0,2,2,1,16);
	OLED_ShowChinese(65,2,43,16);//返回
	OLED_ShowChinese(85,2,44,16);
	OLED_ShowNum(0,4,3,1,16);
	OLED_ShowString(60,4,"ok",16);
		do
		 {
			if(P21==0)
			{
				while(P21==0);
//				LCD1602_Display(0x80,"   emptying     ",0,16);
//				LCD1602_Display(0xc0,"                ",0,16); 
				Delay_Us(15000);
//				LCD1602_WriteCMD(0xc0);
				for(i=0;i<16;i++)
				 {
				//	LCD1602_WriteDAT(42);
					Delay_Us(15000);
				 }
				FINGERPRINT_Cmd_Delete_All_Model();
			  FPM10A_Receive_Data(12); 
//				LCD1602_Display(0x80,"   All empty    ",0,16);
//				LCD1602_Display(0xc0,"                ",0,16);

				break;
			}
		 }while(P22==1);
		 		OLED_Clear();
		OLED_ShowNum(0,2,2,1,16);
	OLED_ShowChinese(32,2,35,16);//收索指纹
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
	OLED_ShowNum(0,6,4,1,16);
	OLED_ShowChinese(42,6,43,16);//返回
	OLED_ShowChinese(82,6,44,16);
}

void Device_Check(void)
{
		xdata unsigned char i=0;
		FPM10A_RECEICE_BUFFER[9]=1;				           //串口数组第九位可判断是否通信正常
//		LCD1602_Display(0xc0,"Loading",0,7);	           //设备加载中界面							   
		for(i=0;i<8;i++)						           //进度条式更新，看起来美观
		{
			//LCD1602_WriteDAT(42);	                       //42对应ASIC码的 *
			Delay_Us(30000);						           //控制进度条速度
		}									
//		LCD1602_Display(0xc0,"Docking  failure",0,16);      //液晶先显示对接失败，如果指纹模块插对的话会将其覆盖	
		FPM10A_Cmd_Check();									//单片机向指纹模块发送校对命令
		FPM10A_Receive_Data(12);							//将串口接收到的数据转存
 		if(FPM10A_RECEICE_BUFFER[9] == 0)					//判断数据低第9位是否接收到0
		{
//			LCD1602_Display(0xc0,"Docking  success",0,16);	//符合成功条件则显示对接成功
		}
}

