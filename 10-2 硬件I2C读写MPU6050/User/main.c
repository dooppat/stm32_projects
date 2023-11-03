#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "MPU6050.h"
#include "Serial.h"

uint8_t ID;
int16_t AX, AY, AZ, GX, GY, GZ;

int main(void)
{
	Serial_Init();
	//OLED_Init();
	MPU6050_Init();
	
	//OLED_ShowString(1, 1, "ID:");
	ID = MPU6050_GetID();
	//OLED_ShowHexNum(1, 4, ID, 2);
	
	while (1)
	{
		MPU6050_GetData(&AX, &AY, &AZ, &GX, &GY, &GZ);
		Serial_Printf("AX = %d, AY = %d, AZ = %d\r\n",AX,AY,AZ);
		Serial_Printf("GX = %d, GY = %d, GZ = %d\r\n",GX,GY,GZ);
		Delay_ms(500);
	}
}
