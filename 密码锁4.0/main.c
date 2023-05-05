#include <STC89C5xRC.H>
#include "Delay.h"
#include "LCD1602.h"
#include "AT24C02.h"
#include "MatrixKeyboard.h"

unsigned char change=0,add=0,lock=1,guest=0;//4��ģʽ״̬ change�����޸����룬add--����û���lock--������guest--�����ʱ����
unsigned char enter=0,del=0;//2�����ܰ���
unsigned char user_num=0,num=0,num_temp=0,num_flag=0,guest_flag=0;//
unsigned char key=20;//����--Ĭ��20������������
unsigned char  keywords[6][6] = {1};//��ȡ��������
unsigned char  guest_keywords[6] = {1};//��ʱ������
unsigned char input[6] = {0};//��������Ĵ��
unsigned char T0Count_s=0,T0Count_m=0,T0Count_guest=0;//��ʱ
unsigned char i=0,j=0,j_temp,error=0;
unsigned char right=2,key_lock=0,input_lock=0,change_right=2,password_fake=0;//

void display();
void key_scan();
void processing();//���ݴ���
void Timer0Init(void);

sbit led1=P2^3;			//lock
sbit led2=P2^2;			//unlock
sbit Buzzer = P1^5;

void main()
{
	
	
	Timer0Init();
	LCD_Init();
	
	//��������������������������������������������������������������������������������������������
	
	
	
//	for(i=0;i<254;i++)                      //��һ��ʹ��ʱ����Ҫ��¼���Σ���һ����¼�ǵô��ϴ˲��֣��ڶ�����¼�ǵ�ע�͵���������������������
//	{
//	AT24C02_WriteByte(i,0);
//		Delay(20);
//	}
//		AT24C02_WriteByte(255,1);	
//	Delay(20);
	
	
	//����������������������������������������������������������������������������������������������������
	
	
	user_num=AT24C02_ReadByte(255);//��ȡ�û�����
	for(j=0;j<user_num;j++)//��ȡ�����user����
	{
		for(i=0;i<6;i++)
		keywords[j][i]=AT24C02_ReadByte(j*6+i);
	}
//	for(i=0;i<6;i++)//������
//	{
//	LCD_ShowNum(2,i+1,keywords[0][i],1);
//	}
	
	led1=1;//led��ʼ��
	led2=1;
	
	while(1)
	{
		
		display();
		key_scan();
		processing();
		if(lock==0&&add==0&&change==0&&guest==0)
		{
			led2=0;
		}
		if(lock==1)
		{
			led2=1;
		}
		
	}
	
	
	
}





void display()
{
//	LCD_ShowNum(2,9,change,1);									//������
//	LCD_ShowNum(2,10,lock,1);
//	LCD_ShowNum(2,11,change_right,1);
//	LCD_ShowNum(2,12,add,1);
//	LCD_ShowNum(2,13,guest,1);
	
	if(lock==1)
	{
		LCD_ShowString(1,1,"PLESE ENTER CODE");	
		if(num_flag>0)
			LCD_ShowChar(2,num_flag,0x2A);
	}
	if(change==0&&lock==0&&change_right==2&&add==0&&guest==0)
	{
		LCD1602_Clear_1LINE();
		LCD_ShowString(1,1,"WELCOME");
		LCD1602_Clear_2LINE();
		Delay(200);
		LCD_ShowNum(2,1,0,1);
		Delay(200);
	}
	if(key_lock==1)
	{
		led1=0;
		Buzzer=!Buzzer;
		TR0=1;
	}
	if(change==1&&lock==0&&change_right==2)
	{
		LCD_ShowString(1,1,"PLESE ENTER NEWC");	
		LCD1602_Clear_2LINE();
		Delay(200);
		for(i=num_flag;i<6;i++)
		{
			LCD_ShowNum(2,i+1,0,1);
		}
		if(num_flag>0)
		{
			for(i=0;i<num_flag;i++)
			LCD_ShowChar(2,i+1,0x2A);
		}
		Delay(200);
	}
	if(change_right==1)
	{
		LCD1602_Clear_2LINE();
		Delay(200);
		for(i=num_flag;i<6;i++)
		{
			LCD_ShowNum(2,i+1,0,1);
		}
		if(num_flag>0)
		{
			for(i=0;i<num_flag;i++)
			LCD_ShowNum(2,i+1,input[i],1);
		}
		Delay(200);
	}
	if(change_right==0)
	{
		LCD1602_Clear_1LINE();
		LCD_ShowString(1,1,"WELCOME");
		LCD1602_Clear_2LINE();
	}
	if(add==1&&lock==0)
	{
		change_right=2;
		LCD_ShowString(1,1,"PLESE ENTER NEWU");	
		LCD1602_Clear_2LINE();
		Delay(100);
		if(num_flag>0)
		{
			for(i=0;i<num_flag;i++)
			LCD_ShowNum(2,i+1,input[i],1);
		}
		Delay(100);
	}
	if(guest==1&&lock==0)
	{
		change_right=2;
		LCD_ShowString(1,1,"PLESE ENTER NEWG");	
		LCD1602_Clear_2LINE();
		Delay(100);
		if(num_flag>0)
		{
			for(i=0;i<num_flag;i++)
			LCD_ShowNum(2,i+1,input[i],1);
		}
		Delay(100);
	}
	
	
}

void	key_scan()
{
	key=MatrixKeyboard();
	if(num_temp==num-1)
	{
		num_temp=num;	
		if(num_temp<7)
			num_flag++;//����*����ʾ
	}
	else
	{
		num=num_temp;
	}
	
	if(key==13&&lock==0)
	{
		change=1;
		input_lock=0;
	}
	if(key==14&&lock==0)
	{
		add=1;
		input_lock=0;
	}
	if(key==11&&lock==0)
	{
		guest=1;
		input_lock=0;
	}
	if(key==12&&lock==0&&add==0&&change==0&&guest==0)
	{
		LCD1602_Clear_1LINE();
		LCD1602_Clear_2LINE();
		j_temp=0;
		lock=1;
		change_right=2;
		input_lock=0;
	}
	if(key==15&&input_lock==0)
	{
		for(i=0;i<6;i++)				//��λ
		{
			input[i] = 0;
		}
		num_temp=0;
		num=0;
		num_flag=0;		
		LCD1602_Clear_2LINE();		
	}

}

void processing()
{
	if(input_lock==0&&num_temp>0 && num_temp<7 && key!=12 && key!=13 && key!=14 && key!=15 && key!=16&&key!=20)
	{
		input[num_temp-1]=key;
	}
	else	if(num_temp>=6)			//���ܰ����ж�
	{
		switch(key)
		{
	//		case 15: del=1;break;
			case 16: enter=1;break;
		}
	}
	
	
	
	
	if(lock==1&&enter==1)//������������
	{
		for(j=0;j<user_num;j++)
			{
					for(i = 0;i < 6;i++)				
				{
					if(input[i] == keywords[j][i])		//�ȶ�����
						right = 1;
					if(input[i] != keywords[j][i])		
					{
						right = 0;
						break;
					}
				}
				if(right==1)
				{
					break;
				}
			}
		if(guest_flag==1 && right==0)
		{
				for(i = 0;i < 6;i++)				
				{
					if(input[i] == guest_keywords[i])		//�ȶ���ʱ����
						right = 1;
					if(input[i] != guest_keywords[i])		
					{
						right = 0;
						break;
					}
				}
		}
			if(right==1)
			{
				j_temp=j;
				lock=0;
				input_lock=1;
				error=0;
			}
			else
			{
				error++;
				LCD1602_Clear_2LINE();
				if(error>0&&error<3)//3�δ�����
				{
					Delay(200);
					led1=0;
					Delay(200);
					led1=1;
				}
				else if(error>=3)//�������3��
				{
							key_lock=1;
				}
			}
			
			for(i=0;i<6;i++)				//��λ
				{
				input[i] = 0;
				}
			right=2;
			num_temp=0;
			num=0;
			enter=0;	
			num_flag=0;				
	}
	
	if(lock == 0 && guest_flag==0 && change == 1&& enter==1)		//�������޸�����
	{	
		
				if(change_right==1)
			{
				
				for(i=0;i<6;i++)
				{
					keywords[j_temp][i] = input[i];
				}	
				for(i=0;i<6;i++)
				{
					AT24C02_WriteByte(i+6*j_temp,keywords[j_temp][i]);
					Delay(20);
				}
				Delay(20);
				AT24C02_WriteByte(255,user_num);
				Delay(20);
				
				for(i=0;i<6;i++)				//��λ
				{
				input[i] = 0;
				}
				change_right=2;
				change=0;
		//		j_temp=0;
				right=2;
				num_temp=0;
				num=0;
				enter=0;	
				num_flag=0;	
				input_lock=1;
				
			}
		if(right==2)
		{
				for(i = 0;i < 6;i++)				
			{
				if(input[i] == keywords[j_temp][i])		//�ȶ�����
					right = 1;
				if(input[i] != keywords[j_temp][i])		
				{
					right = 0;
					break;
				}
			}
		}
			if(right==1)
			{
				change_right=1;
				for(i=0;i<6;i++)				//��λ
					{
					input[i] = 0;
					}
					right=3;
				num_temp=0;
				num=0;
				enter=0;	
				num_flag=0;		
			}
			else if(right==0)
			{
				change_right=0;
				change=0;
				for(i=0;i<6;i++)				//��λ
				{
				input[i] = 0;
				}
			//	j_temp=0;
				right=2;
				num_temp=0;
				num=0;
				enter=0;	
				num_flag=0;	
				input_lock=1;
			}
			
	}
	
	//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	
	if(lock == 0 && guest_flag==0 && enter == 1&& add==1)		//�����¼��û�
	{
				for(i=0;i<6;i++)
				{
					keywords[j_temp+1][i] = input[i];
				}	
				for(i=0;i<6;i++)
				{
					AT24C02_WriteByte(i+6*(j_temp+1),keywords[j_temp+1][i]);
					Delay(20);
				}
				Delay(20);
				user_num++;
				AT24C02_WriteByte(255,user_num);
				Delay(20);
				
				for(i=0;i<6;i++)				//��λ
				{
				input[i] = 0;
				}
				add=0;
				j_temp++;
				num_temp=0;
				num=0;
				enter=0;	
				num_flag=0;	
				input_lock=1;
	}
	
	//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	
		if(lock == 0 && enter == 1&& guest==1)		//�����¼���ʱ�û�
		{
				for(i=0;i<6;i++)
				{
					guest_keywords[i] = input[i];
				}	
				
				for(i=0;i<6;i++)				//��λ
				{
				input[i] = 0;
				}
				guest_flag=1;
				guest=0;
				num_temp=0;
				num=0;
				enter=0;	
				num_flag=0;	
				input_lock=1;
        T0Count_guest=0;
				TR0=1;
				
		}
		
	
	
	
	
	
	
	
	
	
	
//			while(1)                     //������
//		{
//			//LCD1602_Clear_1LINE();
//			for(i=0;i<6;i++)
//			LCD_ShowNum(1,i+3,input[i],1);
//					for(i=0;i<6;i++)
//						LCD_ShowNum(2,i+3,keywords[j_temp][i],1);
//			
//			LCD_ShowNum(2,15,right,1);
//		}
	
}



void Timer0Init(void)		//@12.000MHz    ��ʱ10ms
{
	TMOD &= 0xF0;		
	TMOD |= 0x01;		
	TL0 = 0xF0;	
	TH0 = 0xD8;
	TF0 = 0;		
	TR0 = 0;		
	ET0=1;
	EA=1;
}

void Timer0_Routine() interrupt 1
{
	TL0 = 0xF0;	
	TH0 = 0xD8;
	T0Count_s++;
	if(T0Count_s>=100)//1s��ʱ
	{
		T0Count_s=0;
		if(error>=3)
			T0Count_m++;
		if(guest_flag==1)
			T0Count_guest++;
		if(T0Count_m>=30&&error>=3)//�������3�μ�ʱ
		{
			T0Count_m=0;
			key_lock=0;
			error=0;
			led1=1;
		}
		else if(T0Count_guest>=110&&guest_flag==1)//��ʱ�����ʱ
		{
			T0Count_guest=0;
			guest_flag=0;
		}
		
		if(guest_flag==0&&error==0)
		{
			TR0 = 0;
			TL0 = 0xF0;		
			TH0 = 0xD8;
		}
	}
}