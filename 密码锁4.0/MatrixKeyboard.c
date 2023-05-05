#include <STC89C5xRC.H>
#include "Delay.h"
char MatrixKeyboard()
{
	extern unsigned char num,key_lock;
	unsigned char number=20;
	if(key_lock==0)
	{
	P1=0XFF;
	P13=0;
	if(P17==0){Delay(10);while(P17==0);number=1;num++;}
	if(P16==0){Delay(10);while(P16==0);number=4;num++;}
	if(P15==0){Delay(10);while(P15==0);number=7;num++;}
	if(P14==0){Delay(10);while(P14==0);number=0;num++;}

	P1=0XFF;
	P12=0;
	if(P17==0){Delay(10);while(P17==0);number=2;num++;}
	if(P16==0){Delay(10);while(P16==0);number=5;num++;}
	if(P15==0){Delay(10);while(P15==0);number=8;num++;}
	if(P14==0){Delay(10);while(P14==0);number=11;}//临时密码

	P1=0XFF;
	P11=0;
	if(P17==0){Delay(10);while(P17==0);number=3;num++;}
	if(P16==0){Delay(10);while(P16==0);number=6;num++;}
	if(P15==0){Delay(10);while(P15==0);number=9;num++;}
	if(P14==0){Delay(10);while(P14==0);number=15;}//清除

	P1=0XFF;
	P10=0;
	if(P17==0){Delay(10);while(P17==0);number=12;}//上锁
	if(P16==0){Delay(10);while(P16==0);number=13;}//change
	if(P15==0){Delay(10);while(P15==0);number=14;}//添加用户
	if(P14==0){Delay(10);while(P14==0);number=16;}//确认

	return number;
	}
}

