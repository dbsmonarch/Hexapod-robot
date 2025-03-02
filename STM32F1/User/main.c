#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
#include "Servo.h"
#include "HCSR04.h"
uint8_t RxData;
uint8_t RxData2;
uint8_t Angle = 90;
uint8_t Angle2 = 90;
int main(void)
{
	OLED_Init();
	OLED_ShowString(1, 1, "RxData:");
	Servo_Init();
	Serial_Init();
	Servo_SetAngle(Angle);
	Servo_SetAngle2(Angle2);
	
	while (1)
	{
//		if (Serial_GetRxFlag() == 1)
//		{
			RxData = Serial_GetRxData();
			Serial_SendByte(RxData);
			if(RxData == 'a') 
			{Serial_SendString("$DGT:4-9,1!");
				Delay_ms(600);
			}
			if(RxData == 'b')  
			{
			Serial_SendString("$DGT:10-15,1!");
				Delay_ms(1000);
			}
			if(RxData == 'c') 
			{
			 Serial_SendString("$DGT:16-21,1!");
				Delay_ms(1000);
			}
//			if(RxData == 'd')  
//			{
//			Serial_SendString("$DGT:23-31,1!");
//			}
			if(RxData == 'e')  
			{
				Serial_SendString("$DGS:0!");
			}
			if(RxData == 'f')  
			{
			Serial_SendString("$DGS:1!");
			}
			if(RxData == 'g') 
			{
			 Serial_SendString("$DGS:2!");
			}
			if(RxData == 'h')  
			{
				Serial_SendString("$DGS:3!");
			}
			if(RxData2 == 'i') 
			{
			Angle +=  5;
			Servo_SetAngle(Angle);
			}
			if(RxData2 == 'j') 
			{
			Angle -=  5;
			Servo_SetAngle(Angle);
			}	
			if(RxData2 == 'k') 
			{
			Angle2 +=  5;
			Servo_SetAngle2(Angle2);
			}
			if(RxData2 == 'l') 
			{
			Angle2 -=  5;
			Servo_SetAngle2(Angle2);
			}
//		}
			if (Serial_GetRxFlag2() == 1)
		{
			RxData2 = Serial_GetRxData2();
			Serial_SendByte(RxData2);
			if(RxData2 == 'a') 
			{
			Angle +=  5;
			Servo_SetAngle(Angle);
			Delay_ms(500);
			}
			if(RxData2 == 'b') 
			{
			Angle -=  5;
			Servo_SetAngle(Angle);
				Delay_ms(500);
			}	
			if(RxData2 == 'c') 
			{
			Angle2 -=  5;
			Servo_SetAngle2(Angle2);
				Delay_ms(500);
			}
			if(RxData2 == 'd') 
			{
			Angle2 +=  5;
			Servo_SetAngle2(Angle2);
				Delay_ms(500);
			}
		}
	}
}
