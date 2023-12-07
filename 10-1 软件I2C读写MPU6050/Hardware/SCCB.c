#include "sccb.h"
#include "Delay.h"
#define SCL_PIN GPIO_Pin_6
#define SDA_PIN GPIO_Pin_7

void SDA_MODE_OUT(void) {
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void SDA_MODE_IN(void) {
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void sccb_init()
{
		GPIO_InitTypeDef GPIO_InitTypeStruct;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
		
		//OV SCL
		GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_Out_OD;
		GPIO_InitTypeStruct.GPIO_Pin = SCL_PIN;
		GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitTypeStruct);
		GPIO_SetBits(GPIOB,SCL_PIN);
		//OV SDA
		GPIO_InitTypeStruct.GPIO_Pin = SDA_PIN;
		GPIO_Init(GPIOB, &GPIO_InitTypeStruct);
		GPIO_SetBits(GPIOB,SDA_PIN);	
}



void sccb_start()
{
	SCCB_SDA_H();
	SCCB_SCL_H();
	Delay_us(50);
	if(!SCCB_SDAIN())
		return;
	SCCB_SDA_L();
	if(SCCB_SDAIN())
		return;
	SCCB_SDA_L();
	Delay_us(50);
	SCCB_SCL_L();
}


void sccb_stop()
{
	SCCB_SDA_L();
	Delay_us(50);
	SCCB_SCL_H();
	Delay_us(50);
	SCCB_SDA_H();
	Delay_us(50);
}


//0 ????? 1?????
u8 wait_ack()
{
	u8 res;
	SDA_MODE_IN();		//????SDA????? 
	Delay_us(50);
	SCCB_SCL_H();		//??????¦Ë,???§Ø????????
	Delay_us(50);
	if(SCCB_SDAIN())res=1;  //SDA=1????????????1
	else res=0;         //SDA=0????????????0
	SCCB_SCL_L();			 
	SDA_MODE_OUT();		//????SDA???? 
	return res;
}


void sccb_ack()
{
	SCCB_SCL_L();
	Delay_us(50);
	SCCB_SDA_L();
	Delay_us(50);
	SCCB_SCL_H();
	Delay_us(50);
	SCCB_SCL_L();
	Delay_us(50);
	
}


void sccb_nack()
{

	Delay_us(50);	
	SCCB_SDA_H();
	SCCB_SCL_H();
	Delay_us(50);
	SCCB_SCL_L();
	Delay_us(50);
	SCCB_SDA_L();
	Delay_us(50);
}


void sccb_write(u8 data)
{
	char i;
	u8 temp = data;
	for(i=0; i<8; i++)
	{
		if(temp & 0x80) SCCB_SDA_H();
		else SCCB_SDA_L();
		Delay_us(50);
		SCCB_SCL_H();
		Delay_us(50);
		temp <<= 1;
		SCCB_SCL_L();
	}
}


u8 sccb_read()
{
	u8 temp = 0,i;
	SDA_MODE_IN();
	for(i=0; i<8; i++)
	{
		temp <<= 1;
		SCCB_SCL_L();
		Delay_us(50);
		SCCB_SCL_H();
		if(SCCB_SDAIN())
			temp ++;
		Delay_us(50);	
	}
	SDA_MODE_OUT();
	SCCB_SCL_L();
	return temp;
}

void SCCB_WriteByte(u16 WriteAddress, u8 Sendbyte)
{
	sccb_start(); 					//Æô¶¯SCCB´«Êä
	sccb_write(OV_ID);
	wait_ack();	//Ð´Æ÷¼þID	  
	Delay_us(100);
  sccb_write(WriteAddress);
	wait_ack();		//Ð´¼Ä´æÆ÷µØÖ·	  
	Delay_us(100);
  sccb_write(Sendbyte);
	wait_ack(); 	//Ð´Êý¾Ý	 
  sccb_stop();	  
}

u8 SCCB_ReadByte(u8 ReadAddress)
{
	u8 val=0;
	sccb_start(); //wait_ack();				//Æô¶¯SCCB´«Êä
	sccb_write(OV_ID);
	wait_ack();	//Ð´Æ÷¼þID	  
	Delay_us(100);	 
	sccb_write(ReadAddress);
	wait_ack();			//Ð´¼Ä´æÆ÷µØÖ·	  
	Delay_us(100);	  
	sccb_stop();   
	Delay_us(100);	   
	//ÉèÖÃ¼Ä´æÆ÷µØÖ·ºó£¬²ÅÊÇ¶Á
	sccb_start();//wait_ack();
	sccb_write(OV_ID|0X01);
	wait_ack();//·¢ËÍ¶ÁÃüÁî	  
	Delay_us(100);
	val=sccb_read();		 	//¶ÁÈ¡Êý¾Ý
	sccb_nack();
	sccb_stop();
	return val;
}





















