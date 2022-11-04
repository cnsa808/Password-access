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
	while(!(S3CON&0x01));	 //������Ϊ1 
	S3CON&= ~0x01;
	dat = S3BUF;
	
	return (dat);
	
}

void Delay_Us(unsigned int i)
{
	while(--i);
}

//FINGERPRINTͨ��Э�鶨��

code unsigned char FPM10A_Get_Device[10] ={0x01,0x00,0x07,0x13,0x00,0x00,0x00,0x00,0x00,0x1b};//������֤
code unsigned char FPM10A_Pack_Head[6] = {0xEF,0x01,0xFF,0xFF,0xFF,0xFF};  //Э���ͷ
code unsigned char FPM10A_Get_Img[6] = {0x01,0x00,0x03,0x01,0x00,0x05};    //���ָ��ͼ��
code unsigned char FPM10A_Get_Templete_Count[6] ={0x01,0x00,0x03,0x1D,0x00,0x21 }; //���ģ������
code unsigned char FPM10A_Search[11]={0x01,0x00,0x08,0x04,0x01,0x00,0x00,0x03,0xE7,0x00,0xF8}; //����ָ��������Χ0 - 999,ʹ��BUFFER1�е�����������
code unsigned char FPM10A_Search_0_9[11]={0x01,0x00,0x08,0x04,0x01,0x00,0x00,0x00,0x13,0x00,0x21}; //����0-9��ָ��
code unsigned char FPM10A_Img_To_Buffer1[7]={0x01,0x00,0x04,0x02,0x01,0x00,0x08}; //��ͼ����뵽BUFFER1
code unsigned char FPM10A_Img_To_Buffer2[7]={0x01,0x00,0x04,0x02,0x02,0x00,0x09}; //��ͼ����뵽BUFFER2
code unsigned char FPM10A_Reg_Model[6]={0x01,0x00,0x03,0x05,0x00,0x09}; //��BUFFER1��BUFFER2�ϳ�����ģ��
code unsigned char FPM10A_Delete_All_Model[6]={0x01,0x00,0x03,0x0d,0x00,0x11};//ɾ��ָ��ģ�������е�ģ��
volatile unsigned char  FPM10A_Save_Finger[9]={0x01,0x00,0x06,0x06,0x01,0x00,0x0B,0x00,0x19};//��BUFFER1�е��������ŵ�ָ����λ��
//volatile:ϵͳ�������´������ڵ��ڴ��ȡ���ݣ���ʹ��ǰ���ָ��ոմӸô���ȡ������
/*------------------ FINGERPRINT������ --------------------------*/
 //���Ͱ�ͷ
void FPM10A_Cmd_Send_Pack_Head(void)
{
	xdata int i;	
	for(i=0;i<6;i++) //��ͷ
   {
     Uart_Send_Byte(FPM10A_Pack_Head[i]);   
    }		
}
//����ָ��
void FPM10A_Cmd_Check(void)
{
	xdata int i=0;
	FPM10A_Cmd_Send_Pack_Head(); //����ͨ��Э���ͷ
	for(i=0;i<10;i++)
	 {		
		Uart_Send_Byte(FPM10A_Get_Device[i]);
	  }
}
//���շ������ݻ���
void FPM10A_Receive_Data(unsigned char ucLength)
{
  xdata unsigned char i;

  for (i=0;i<ucLength;i++)
     FPM10A_RECEICE_BUFFER[i] = Uart_Receive_Byte();

}

//FINGERPRINT_���ָ��ͼ������
void FPM10A_Cmd_Get_Img(void)
{
    unsigned char i;
    FPM10A_Cmd_Send_Pack_Head(); //����ͨ��Э���ͷ
    for(i=0;i<6;i++) //�������� 0x1d
	{
       Uart_Send_Byte(FPM10A_Get_Img[i]);
	}
}
//��ͼ��ת��������������Buffer1��
void FINGERPRINT_Cmd_Img_To_Buffer1(void)
{
 	unsigned char i;
	FPM10A_Cmd_Send_Pack_Head(); //����ͨ��Э���ͷ      
   	for(i=0;i<7;i++)   //�������� ��ͼ��ת���� ������ ����� CHAR_buffer1
     {
      Uart_Send_Byte(FPM10A_Img_To_Buffer1[i]);
   	  }
}
//��ͼ��ת��������������Buffer2��
void FINGERPRINT_Cmd_Img_To_Buffer2(void)
{
     unsigned char i;
     for(i=0;i<6;i++)    //���Ͱ�ͷ
	 {
    	Uart_Send_Byte(FPM10A_Pack_Head[i]);   
   	 }
     for(i=0;i<7;i++)   //�������� ��ͼ��ת���� ������ ����� CHAR_buffer1
      {
      	Uart_Send_Byte(FPM10A_Img_To_Buffer2[i]);
   	  }
}
//����ȫ���û�999ö
void FPM10A_Cmd_Search_Finger(void)
{
       unsigned char i;	   	    
			 FPM10A_Cmd_Send_Pack_Head(); //����ͨ��Э���ͷ
       for(i=0;i<11;i++)
           {
    	      Uart_Send_Byte(FPM10A_Search[i]);   
   		   }
}

void FPM10A_Cmd_Reg_Model(void)
{
       unsigned char i;	   
	    
			 FPM10A_Cmd_Send_Pack_Head(); //����ͨ��Э���ͷ

       for(i=0;i<6;i++)
           {
    	      Uart_Send_Byte(FPM10A_Reg_Model[i]);   
   		   }


}
//ɾ��ָ��ģ���������ָ��ģ��
void FINGERPRINT_Cmd_Delete_All_Model(void)
{
     unsigned char i;    
    for(i=0;i<6;i++) //��ͷ
      Uart_Send_Byte(FPM10A_Pack_Head[i]);   
    for(i=0;i<6;i++) //����ϲ�ָ��ģ��
	   {
      Uart_Send_Byte(FPM10A_Delete_All_Model[i]);   
		 }	
}
//����ָ��
void FPM10A_Cmd_Save_Finger( unsigned int storeID )
{
       unsigned long temp = 0;
		   unsigned char i;
       FPM10A_Save_Finger[5] =(storeID&0xFF00)>>8;
       FPM10A_Save_Finger[6] = (storeID&0x00FF);
		   for(i=0;i<7;i++)   //����У���
		   	   temp = temp + FPM10A_Save_Finger[i]; 
		   FPM10A_Save_Finger[7]=(temp & 0x00FF00) >> 8; //���У������
		   FPM10A_Save_Finger[8]= temp & 0x0000FF;		   
       FPM10A_Cmd_Send_Pack_Head(); //����ͨ��Э���ͷ	
       for(i=0;i<9;i++)  
      		Uart_Send_Byte(FPM10A_Save_Finger[i]);      //�������� ��ͼ��ת���� ������ ����� CHAR_buffer1
}
//���ָ��
void FPM10A_Add_Fingerprint()
{
	unsigned char id_show[]={0,0,0};
	OLED_Clear(); //����
finger_id=0;  
	while(1)
	{
		OLED_ShowNum(0,2,2,1,16);
	OLED_ShowChinese(65,2,43,16);//����
	OLED_ShowChinese(85,2,44,16);
	OLED_ShowNum(0,0,1,1,16);
	OLED_ShowChinese(32,0,39,16);//����id
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
	OLED_ShowChinese(32,2,35,16);//����ָ��
	OLED_ShowChinese(52,2,36,16);
	OLED_ShowChinese(72,2,37,16);
	OLED_ShowChinese(92,2,38,16);
	OLED_ShowNum(0,0,1,1,16);
	OLED_ShowChinese(32,0,39,16);//����ָ��
	OLED_ShowChinese(52,0,40,16);
	OLED_ShowChinese(72,0,37,16);
	OLED_ShowChinese(92,0,38,16);	
	OLED_ShowNum(0,4,3,1,16);
	OLED_ShowChinese(32,4,41,16);//ɾ��ָ��
	OLED_ShowChinese(52,4,42,16);
	OLED_ShowChinese(72,4,37,16);
	OLED_ShowChinese(92,4,38,16);		
	OLED_ShowNum(0,6,4,1,16);
	OLED_ShowChinese(42,6,43,16);//����
	OLED_ShowChinese(82,6,44,16);
		 break;
	}

	//���л���ָ��iDֵ��1
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

	 //��ȷ�ϼ���ʼ¼��ָ����Ϣ 		 			
	 if(P21 == 0)
	  {	
			  while(P21==0);
				OLED_Clear();
			while(P22 == 1)
		   {
			  //���·��ؼ��˳�¼�뷵��fingerID����״̬   
				if(P22 == 0) 
				 {
				  while(P22==0);
				  break;
				  }	
	OLED_ShowChinese(32,0,45,16);//
	OLED_ShowChinese(52,0,46,16);
	OLED_ShowChinese(72,0,47,16);
	OLED_ShowChinese(92,0,48,16);	
				FPM10A_Cmd_Get_Img(); //���ָ��ͼ��
				FPM10A_Receive_Data(12);		
			
				//�жϽ��յ���ȷ����,����0ָ�ƻ�ȡ�ɹ�
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
					 FPM10A_Cmd_Get_Img(); //���ָ��ͼ��
					 FPM10A_Receive_Data(12);
					//�жϽ��յ���ȷ����,����0ָ�ƻ�ȡ�ɹ�

					if(FPM10A_RECEICE_BUFFER[9]==0)
					{			
						OLED_ShowString(30,4,"two ok",16);
						Delay_Us(15000);

						FINGERPRINT_Cmd_Img_To_Buffer2();
				  		FPM10A_Receive_Data(12);
						FPM10A_Cmd_Reg_Model();//ת����������
	         			FPM10A_Receive_Data(12); 
					  	FPM10A_Cmd_Save_Finger(finger_id);                		         
	          			FPM10A_Receive_Data(12);
						
						finger_id=finger_id+1;
						Delay_Us(50000);
							OLED_Clear(); //����		
	OLED_ShowChinese(25,4,49,16);
	OLED_ShowChinese(45,4,50,16);
							break;
				    	
				  	}
					
				   }
	        break;
					}
				}
//			ClrScreen(); //�����ʾ��
			}
		//	Delay_Ms(500);
		}
}

//����ָ��
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
	OLED_ShowChinese(65,2,43,16);//����
	OLED_ShowChinese(85,2,44,16);		
	do
	{
	
	
		FPM10A_Cmd_Get_Img(); //���ָ��ͼ��
		FPM10A_Receive_Data(12);		
			
		//�жϽ��յ���ȷ����,����0ָ�ƻ�ȡ�ɹ�
		if(FPM10A_RECEICE_BUFFER[9]==0)
		{			
			
			Delay_Us(15000);
			FINGERPRINT_Cmd_Img_To_Buffer1();
			FPM10A_Receive_Data(12);		
			FPM10A_Cmd_Search_Finger();
			FPM10A_Receive_Data(16);			
			if(FPM10A_RECEICE_BUFFER[9] == 0) //������  
			{
				OLED_Clear();	
				
		OLED_ShowChinese(75,2,23,16);//��
		OLED_ShowChinese(112,2,24,16);//ȷ				
				//ƴ��ָ��ID��
				find_fingerid = FPM10A_RECEICE_BUFFER[10]*256 + FPM10A_RECEICE_BUFFER[11];					
			
				Delay_Us(2000);				
			   }
				else //û���ҵ�
				{
					OLED_Clear();

					OLED_ShowChinese(75,2,32,16);//��
			OLED_ShowChinese(112,2,33,16);//��	
					
				}
			}

		}while(P22 == 1);
		OLED_Clear();
		OLED_ShowNum(0,2,2,1,16);
	OLED_ShowChinese(32,2,35,16);//����ָ��
	OLED_ShowChinese(52,2,36,16);
	OLED_ShowChinese(72,2,37,16);
	OLED_ShowChinese(92,2,38,16);
	OLED_ShowNum(0,0,1,1,16);
	OLED_ShowChinese(32,0,39,16);//����ָ��
	OLED_ShowChinese(52,0,40,16);
	OLED_ShowChinese(72,0,37,16);
	OLED_ShowChinese(92,0,38,16);	
	OLED_ShowNum(0,4,3,1,16);
	OLED_ShowChinese(32,4,41,16);//ɾ��ָ��
	OLED_ShowChinese(52,4,42,16);
	OLED_ShowChinese(72,4,37,16);
	OLED_ShowChinese(92,4,38,16);		
	OLED_ShowNum(0,6,4,1,16);
	OLED_ShowChinese(42,6,43,16);//����
	OLED_ShowChinese(82,6,44,16);
}
//ɾ�����д�����ָ�ƿ�
void FPM10A_Delete_All_Fingerprint()
{
		unsigned char i=0;
	OLED_Clear();
		OLED_ShowNum(0,2,2,1,16);
	OLED_ShowChinese(65,2,43,16);//����
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
	OLED_ShowChinese(32,2,35,16);//����ָ��
	OLED_ShowChinese(52,2,36,16);
	OLED_ShowChinese(72,2,37,16);
	OLED_ShowChinese(92,2,38,16);
	OLED_ShowNum(0,0,1,1,16);
	OLED_ShowChinese(32,0,39,16);//����ָ��
	OLED_ShowChinese(52,0,40,16);
	OLED_ShowChinese(72,0,37,16);
	OLED_ShowChinese(92,0,38,16);	
	OLED_ShowNum(0,4,3,1,16);
	OLED_ShowChinese(32,4,41,16);//ɾ��ָ��
	OLED_ShowChinese(52,4,42,16);
	OLED_ShowChinese(72,4,37,16);
	OLED_ShowChinese(92,4,38,16);		
	OLED_ShowNum(0,6,4,1,16);
	OLED_ShowChinese(42,6,43,16);//����
	OLED_ShowChinese(82,6,44,16);
}

void Device_Check(void)
{
		xdata unsigned char i=0;
		FPM10A_RECEICE_BUFFER[9]=1;				           //��������ھ�λ���ж��Ƿ�ͨ������
//		LCD1602_Display(0xc0,"Loading",0,7);	           //�豸�����н���							   
		for(i=0;i<8;i++)						           //������ʽ���£�����������
		{
			//LCD1602_WriteDAT(42);	                       //42��ӦASIC��� *
			Delay_Us(30000);						           //���ƽ������ٶ�
		}									
//		LCD1602_Display(0xc0,"Docking  failure",0,16);      //Һ������ʾ�Խ�ʧ�ܣ����ָ��ģ���ԵĻ��Ὣ�串��	
		FPM10A_Cmd_Check();									//��Ƭ����ָ��ģ�鷢��У������
		FPM10A_Receive_Data(12);							//�����ڽ��յ�������ת��
 		if(FPM10A_RECEICE_BUFFER[9] == 0)					//�ж����ݵ͵�9λ�Ƿ���յ�0
		{
//			LCD1602_Display(0xc0,"Docking  success",0,16);	//���ϳɹ���������ʾ�Խӳɹ�
		}
}

