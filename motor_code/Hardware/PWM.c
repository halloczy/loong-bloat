#include "stm32f10x.h"                  // Device header

void PWM_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	

	
	TIM_InternalClockConfig(TIM2);//调用内部时钟
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision =TIM_CKD_DIV1 ;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up ;
	TIM_TimeBaseInitStruct.TIM_Period = 100-1;//自动重装（刚好1s）越小变越快 ARR
	TIM_TimeBaseInitStruct.TIM_Prescaler = 36-1;//预分频（对72M进行7200分频=10000）越小变越快 PSC
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;//高级计时器才有
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
	
	TIM_OCInitTypeDef TIM_OCInitStruct;
	TIM_OCStructInit(&TIM_OCInitStruct);//先赋初始值
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1 ;
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCNPolarity_High;
	TIM_OCInitStruct.TIM_OutputState =TIM_OutputState_Enable ;
	TIM_OCInitStruct.TIM_Pulse = 0;  //CCR
	
	TIM_OC1Init(TIM2,&TIM_OCInitStruct);
	TIM_OC2Init(TIM2,&TIM_OCInitStruct);
	
	TIM_Cmd(TIM2,ENABLE);
}

void PWM_SetCompare1(uint16_t Compare)
{
	TIM_SetCompare1(TIM2,Compare);
}

void PWM_SetCompare2(uint16_t Compare)
{
	TIM_SetCompare2(TIM2,Compare);
}