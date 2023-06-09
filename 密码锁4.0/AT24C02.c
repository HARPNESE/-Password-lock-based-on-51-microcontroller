#include <STC89C5xRC.H>

#define AT24C02_ADDRESS  0XA0


sbit I2C_SCL=P2^1;
sbit I2C_SDA=P2^0;

void I2C_Start()
{
	I2C_SDA=1;
	I2C_SCL=1;
	I2C_SDA=0;
	I2C_SCL=0;
}

void I2C_Stop()
{
	I2C_SDA=0;
	I2C_SCL=1;
	I2C_SDA=1;
}

void I2C_SendByte(unsigned char Byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		I2C_SDA=Byte&(0X80>>i);
		I2C_SCL=1;
		I2C_SCL=0;
	}
}

unsigned char I2C_ReceiveByte()
{
	unsigned char Byte=0x00,i;
	for(i=0;i<8;i++)
	{
		I2C_SCL=1;
		if(I2C_SDA){Byte|=(0x80>>i);}
		I2C_SCL=0;
	}
	return Byte;
}

/*

函数名称：I2C发送应答
参数：应答位 AckBit   0为应答，1为非应答
返回值：无

*/
void I2C_SendAck(unsigned char AckBit)
{
	I2C_SDA=AckBit;
	I2C_SCL=1;
	I2C_SCL=0;
}

/*

函数名称：I2C接收应答�
参数：无
返回值：接收到的应答位，0为应答，1为非应答

*/
unsigned char I2C_ReceiveAck()
{
	unsigned char AckBit;
	I2C_SDA=1;
	I2C_SCL=1;
	AckBit=I2C_SDA;
	I2C_SCL=0;
	return AckBit;
}




void AT24C02_WriteByte(unsigned char WordAddress,Data)//WORDADDRESS :0-255
{
	I2C_Start();
	I2C_SendByte(AT24C02_ADDRESS);
	I2C_ReceiveAck();
	I2C_SendByte(WordAddress);
	I2C_ReceiveAck();
	I2C_SendByte(Data);
	I2C_ReceiveAck();
	I2C_Stop();
}

unsigned char AT24C02_ReadByte(unsigned char WordAddress)
{
	unsigned char Data;
	
	I2C_Start();
	I2C_SendByte(AT24C02_ADDRESS);
	I2C_ReceiveAck();
	I2C_SendByte(WordAddress);
	I2C_ReceiveAck();
	I2C_Start();
	I2C_SendByte(AT24C02_ADDRESS|0X01);
	I2C_ReceiveAck();
	Data=I2C_ReceiveByte();
	I2C_SendAck(1);
	I2C_Stop();
	
	return Data;
}

//void Delay(unsigned int xms)		//@12.000MHz
//{
//	unsigned char i, j;
//	while(xms--)
//	{

//		i = 2;
//		j = 239;
//		do
//		{
//			while (--j);
//		} while (--i);
//	}
//}













