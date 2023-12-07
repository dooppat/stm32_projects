#ifndef __SCCB_H__
#define __SCCB_H__
#include "stm32f10x.h"                  // Device header

void SDA_MODE_OUT(void);

void SDA_MODE_IN(void);


#define SCCB_SDAIN()   GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7)

#define SCCB_SDA_H()      GPIO_SetBits(GPIOB, GPIO_Pin_7)    // SDA÷√∏ﬂ
#define SCCB_SDA_L()      GPIO_ResetBits(GPIOB, GPIO_Pin_7)  // SDA÷√µÕ
#define SCCB_SCL_H()      GPIO_SetBits(GPIOB, GPIO_Pin_6)    // SCL÷√∏ﬂ
#define SCCB_SCL_L()      GPIO_ResetBits(GPIOB, GPIO_Pin_6)  // SCL÷√µÕ





#define OV_ID 0xD0

void sccb_init(void);
void sccb_start(void);
u8 wait_ack(void);
void sccb_stop(void);
void sccb_ack(void);
void sccb_nack(void);
void sccb_write(u8 data);
u8 sccb_read(void);
void SCCB_WriteByte(u16 WriteAddress, u8 Sendbyte);
u8 SCCB_ReadByte(u8 ReadAddress);

#endif





