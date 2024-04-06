/*
 * notes.h
 *
 *  Created on: Apr 6, 2024
 *      Author: adam
 */

#ifndef INC_NOTES_H_
#define INC_NOTES_H_

#include <stdint.h>
#include "main.h"
#include "main_cpp.h"

void tone(TIM_HandleTypeDef *htim1, TIM_HandleTypeDef *htim2, uint16_t freq, uint32_t delay = 0, uint8_t volume = 100);
void scale(TIM_HandleTypeDef *htim1, TIM_HandleTypeDef *htim2);

#endif /* INC_NOTES_H_ */
