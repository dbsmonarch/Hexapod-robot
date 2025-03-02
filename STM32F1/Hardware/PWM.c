#include "stm32f10x.h"                  // Device header

#include "stm32f10x.h"                  // Device header


void PWM_Init(void)
{
        GPIO_InitTypeDef GPIOInitStructure;
        TIM_TimeBaseInitTypeDef TIMInitStructure;
        TIM_OCInitTypeDef TIMOCInitStructure_TIM3;
        //1.使能GPIO时钟、定时器时钟、复用时钟
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

      //  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
 
        //3.配置GPIO
        GPIOInitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
        GPIOInitStructure.GPIO_Pin = GPIO_Pin_6| GPIO_Pin_7;
        GPIOInitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        
        GPIO_Init(GPIOA, &GPIOInitStructure);
    
        //4.配置定时器
        TIMInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
        TIMInitStructure.TIM_CounterMode   = TIM_CounterMode_Up;
        TIMInitStructure.TIM_Period        = 20000-1;
        TIMInitStructure.TIM_Prescaler     = 72-1;
		TIMInitStructure.TIM_RepetitionCounter = 0;
        TIM_TimeBaseInit(TIM3, &TIMInitStructure);
		

        //5.配置PWM

		
        TIMOCInitStructure_TIM3.TIM_OCMode      = TIM_OCMode_PWM1;
        TIMOCInitStructure_TIM3.TIM_OutputState = TIM_OutputState_Enable;
        TIMOCInitStructure_TIM3.TIM_OCPolarity  = TIM_OCPolarity_High;
        
        TIM_OC1Init(TIM3, &TIMOCInitStructure_TIM3);
        TIM_OC2Init(TIM3, &TIMOCInitStructure_TIM3);

        TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
        TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
		TIM_ARRPreloadConfig(TIM3, ENABLE);
        TIM_Cmd(TIM3, ENABLE);
		
		
}

void PWM_SetCompare1(uint16_t Compare)
{
	TIM_SetCompare1(TIM3, Compare);
}
void PWM_SetCompare2(uint16_t Compare)
{
	TIM_SetCompare2(TIM3, Compare);
}
