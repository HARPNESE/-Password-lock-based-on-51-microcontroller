#ifndef __AT24C02_H__
#define __AT24C02_H__

void I2C_Start();
void I2C_Stop();
void I2C_SendByte(unsigned char Byte);
unsigned char I2C_ReceiveByte();
void I2C_SendAck(unsigned char AckBit);
unsigned char I2C_ReceiveAck();
void AT24C02_WriteByte(unsigned char WordAddress,Data);
unsigned char AT24C02_ReadByte(unsigned char WordAddress);


//void Delay(unsigned int xms);		//@12.000MHz


#endif


