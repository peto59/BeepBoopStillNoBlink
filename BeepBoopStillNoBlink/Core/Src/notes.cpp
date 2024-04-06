/*
 * notes.cpp
 *
 *  Created on: Apr 6, 2024
 *      Author: adam
 */

#include "notes.h"

void tone(TIM_HandleTypeDef *htim1, uint16_t freq, uint32_t delay, uint8_t volume){
	if (freq == 0){
//		__HAL_TIM_SET_COMPARE(htim1, TIM_CHANNEL_2, 0);
		return;
	}
	uint16_t ARR = (uint16_t)((1000000/freq)*0.94);

	uint16_t CRR = (uint16_t)((volume * ARR) / 200);
	__HAL_TIM_SET_AUTORELOAD(htim1, ARR);
	__HAL_TIM_SET_COMPARE(htim1, TIM_CHANNEL_2, CRR);
//	HAL_TIM_PWM_Start(htim1, TIM_CHANNEL_2);
	HAL_Delay(delay);
//	HAL_TIM_PWM_Stop(htim1, TIM_CHANNEL_2);
//	__HAL_TIM_SET_COMPARE(htim1, TIM_CHANNEL_2, 0);
}

void scale(TIM_HandleTypeDef *htim1){
	uint32_t delay = 1000;
	tone(htim1, 523, delay);
	tone(htim1, 554, delay);
	tone(htim1, 587, delay);
	tone(htim1, 622, delay);
	tone(htim1, 659, delay);
	tone(htim1, 698, delay);
	tone(htim1, 740, delay);
	tone(htim1, 784, delay);
	tone(htim1, 831, delay);
	tone(htim1, 880, delay);
	tone(htim1, 932, delay);
	tone(htim1, 988, delay);
}
