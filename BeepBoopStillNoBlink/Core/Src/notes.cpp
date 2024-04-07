/*
 * notes.cpp
 *
 *  Created on: Apr 6, 2024
 *      Author: adam
 */

#include "notes.h"

void tone(TIM_HandleTypeDef *htim1, TIM_HandleTypeDef *htim2, uint16_t freq, uint32_t delay, uint8_t volume){
	TIM2->CNT = 0;
	__HAL_TIM_SET_AUTORELOAD(htim2, delay);
	if (freq == 0){
		__HAL_TIM_SET_COMPARE(htim1, TIM_CHANNEL_2, 0);
		return;
	}
	uint16_t ARR = (uint16_t)((1000000/freq)*0.94);

	uint16_t CRR = (uint16_t)(ARR-((volume * ARR) / 200));
	__HAL_TIM_SET_AUTORELOAD(htim1, ARR);
	__HAL_TIM_SET_COMPARE(htim1, TIM_CHANNEL_2, CRR);
//	HAL_TIM_PWM_Start(htim1, TIM_CHANNEL_2);
//	__HAL_TIM_SET_AUTORELOAD(htim2, delay);
//	HAL_Delay(delay);
//	HAL_TIM_PWM_Stop(htim1, TIM_CHANNEL_2);
//	__HAL_TIM_SET_COMPARE(htim1, TIM_CHANNEL_2, 0);
}

void scale(TIM_HandleTypeDef *htim1, TIM_HandleTypeDef *htim2){
	uint32_t delay = 1000;
	tone(htim1, htim2, 523, delay);
	HAL_Delay(delay);
	tone(htim1, htim2, 554, delay);
	HAL_Delay(delay);
	tone(htim1, htim2, 587, delay);
	HAL_Delay(delay);
	tone(htim1, htim2, 622, delay);
	HAL_Delay(delay);
	tone(htim1, htim2, 659, delay);
	HAL_Delay(delay);
	tone(htim1, htim2, 698, delay);
	HAL_Delay(delay);
	tone(htim1, htim2, 740, delay);
	HAL_Delay(delay);
	tone(htim1, htim2, 784, delay);
	HAL_Delay(delay);
	tone(htim1, htim2, 831, delay);
	HAL_Delay(delay);
	tone(htim1, htim2, 880, delay);
	HAL_Delay(delay);
	tone(htim1, htim2, 932, delay);
	HAL_Delay(delay);
	tone(htim1, htim2, 988, delay);
}
