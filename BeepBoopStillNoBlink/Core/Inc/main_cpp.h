/*
 * main_cpp.h
 *
 *  Created on: Apr 6, 2024
 *      Author: adam
 */

#ifndef INC_MAIN_CPP_H_
#define INC_MAIN_CPP_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"

int main_cpp(UART_HandleTypeDef huart2, TIM_HandleTypeDef *htim1, TIM_HandleTypeDef *htim2);
void setRead(void);

#ifdef __cplusplus
}
#endif

void setRegister(uint16_t val);
#endif /* INC_MAIN_CPP_H_ */
