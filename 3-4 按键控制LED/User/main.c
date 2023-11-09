#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "Key.h"

uint8_t KeyNum;

int main(void)
{
	LED_Init();
	Key_Init();
	
	while (1)
	{
		KeyNum = Key_GetNum();
		if (KeyNum == 1)
		{
			if(GPIO_ReadOutputDataBit(GPIOB,Led_Pin)==1)
			GPIO_ResetBits(GPIOB,Led_Pin);
			else{
			GPIO_SetBits(GPIOB,Led_Pin);
			}
		}
	}
}
