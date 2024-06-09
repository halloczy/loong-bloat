#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Motor.h"
#include "Key.h"
#include "LED.h"

uint8_t KeyNum;
uint8_t Scount=0;
//注意范围
int8_t Speed;
int8_t Speed2;

int main(void)
{
	OLED_Init();
	MotorAll_Init();
	Key_Init();
	LED_Init();
	
	OLED_ShowString(1,1,"Speed:");
	OLED_ShowString(3,1,"Speed2:");
	
	while(1)
	{

		KeyNum = Key_GetNum();
		if(KeyNum==1){
			Speed = 0;
			Speed2 = 0;
			Scount = 0;
			LED1_OFF();
			LED2_OFF();
		}
		if(KeyNum==2){
			Speed = 100;
			Speed2 = -100;
			LED2_ON();
			LED1_OFF();
		}
		
		if(KeyNum==3)
			{
				Scount += 1;
				if((Scount+2)%2==0)
				{
					Speed = 75;
					Speed2 = 75;
					LED1_ON();
					LED2_OFF();
				}
				if((Scount +3)%4 == 0)
				{
					Speed = 31;
					Speed2 = 37;
					LED1_OFF();
					LED2_OFF();
				}
				if((Scount +1)%4 == 0)
				{
					Speed = 100;
					Speed2 = 100;
					LED1_ON();
					LED2_ON();
				}
			}																						
		if(KeyNum==4){
			Speed  =  -45;
			Speed2 =  -45;
		}
		if(KeyNum==5){
			Speed += 2;
			if(Speed>100)
			{
				Speed = 100;
			}

		}
		if(KeyNum==6){
			Speed -= 2;

		}
		if(KeyNum==7){

			Speed2 += 2;
			if(Speed2>99)
			{
				Speed2 = 100;
			}
		}
		if(KeyNum==8){

			Speed2 -= 2;
		}
		

		MotorL_SetSpeed(Speed);
		OLED_ShowSignedNum(2,1,Speed,4);
		MotorR_SetSpeed(Speed2);
		OLED_ShowSignedNum(4,1,Speed2,4);
	}
}

