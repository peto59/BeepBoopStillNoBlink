#include "main_cpp.h"
#include "notes.h"
//#include "stdbool.h"

int main_cpp(UART_HandleTypeDef huart2, TIM_HandleTypeDef *htim1){
	//	  tone(&htim1, 500);
	//	  HAL_Delay(5000);
	//	  tone(&htim1, 1000);
	//	  HAL_Delay(5000);
	//	  tone(&htim1, 2000);
	//	  HAL_Delay(5000);
		  uint8_t received_freq[2];
		  uint8_t received_start[8];
		  uint8_t received_end[8];
		  bool full_received = true;

		  full_received &= HAL_UART_Receive(&huart2, received_freq, 2, 10) == HAL_OK;
		  if(full_received){
			  HAL_GPIO_TogglePin (GPIOA, GPIO_PIN_6);
			  full_received &= HAL_UART_Receive(&huart2, received_start, 8, 10) == HAL_OK;
			  full_received &= HAL_UART_Receive(&huart2, received_end, 8, 10) == HAL_OK;
			  if(full_received){
				  HAL_GPIO_TogglePin (GPIOA, GPIO_PIN_6);
				  uint16_t freq = (uint16_t)received_freq[0] << 8 | received_freq[1];
				  uint64_t start = ((uint64_t)received_start[0] << 56) | ((uint64_t)received_start[1] << 48) |
				                        ((uint64_t)received_start[2] << 40) | ((uint64_t)received_start[3] << 32) |
				                        ((uint64_t)received_start[4] << 24) | ((uint64_t)received_start[5] << 16) |
				                        ((uint64_t)received_start[6] << 8) | received_start[7];
				  uint64_t end = ((uint64_t)received_end[0] << 56) | ((uint64_t)received_end[1] << 48) |
				  			                        ((uint64_t)received_end[2] << 40) | ((uint64_t)received_end[3] << 32) |
				  			                        ((uint64_t)received_end[4] << 24) | ((uint64_t)received_end[5] << 16) |
				  			                        ((uint64_t)received_end[6] << 8) | received_end[7];
				  if(freq != 0){
					  HAL_TIM_PWM_Start(htim1, TIM_CHANNEL_2);
					  tone(htim1, freq, (uint32_t)(end-start), 100);
				  }else{
					  HAL_TIM_PWM_Stop(htim1, TIM_CHANNEL_2);
				  }
//				  HAL_Delay(15000);
			  }
		  }
//		  HAL_UART_Transmit(&huart2, received_data, 12, 1000);
//		  HAL_Delay(1000);
		  return 0;
}
