#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "MPU6050.h"
#include "Serial.h"

#define GRAVITY 9.81  // 重力加速度
#define DELTA_T 0.01  // 时间间隔，10ms为0.01s

uint8_t ID;
int16_t AX, AY, AZ, GX, GY, GZ;

int main(void)
{
	Serial_Init();
	Serial_Printf("Serial has initialized.\r\n");
	
	MPU6050_Init();
	ID = MPU6050_GetID();
	Serial_Printf("MPU6050 has initialized.ID = %d\r\n",ID);

	
	while (1)
	{
		MPU6050_GetData(&AX, &AY, &AZ, &GX, &GY, &GZ);
		Serial_Printf("AX = %d, AY = %d, AZ = %d\r\n",AX,AY,AZ);
		Serial_Printf("GX = %d, GY = %d, GZ = %d\r\n",GX,GY,GZ);
		Delay_ms(500);
	}
}
