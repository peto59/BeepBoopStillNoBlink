#include "main_cpp.h"
#include "notes.h"
//#include "stdbool.h"

const uint8_t seg[4] = {0x02,0x04,0x08,0x10};
const uint8_t num[10] 	= {0b11111101,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
bool read = true;
//0bgfedcbap
uint8_t U = 0b10000011;
uint8_t O = 0b10000001;
uint8_t L = 0b10001111;
void setRead(void){
	read = true;
}
int main_cpp(UART_HandleTypeDef huart2, TIM_HandleTypeDef *htim1, TIM_HandleTypeDef *htim2){
	//	  tone(&htim1, 500);
	//	  HAL_Delay(5000);
	//	  tone(&htim1, 1000);
	//	  HAL_Delay(5000);
	//	  tone(&htim1, 2000);
	//	  HAL_Delay(5000);
	tone(htim1,htim2,500,500);
	HAL_Delay(500);
	scale(htim1, htim2);
//	scale(htim1);
//	while(1){
//		setRegister((U<<8) | seg[0]);
//		setRegister((O<<8) | seg[1]);
//		setRegister((L<<8) | seg[2]);
//		setRegister((num[3]<<8) | seg[3]);
//	}
		  uint8_t received_freq[2];
		  uint8_t received_start[8];
		  uint8_t received_end[8];
		  while (1){
			  bool full_received = true;
//			  setRegister((U<<8) | seg[0]);
//			  setRegister((O<<8) | seg[1]);
//			  setRegister((L<<8) | seg[2]);
			  if(read){

			  		  full_received &= HAL_UART_Receive(&huart2, received_freq, 2, 10) == HAL_OK;
			  		  if(full_received){
			  //			  HAL_GPIO_TogglePin (GPIOA, GPIO_PIN_6);
			  			  full_received &= HAL_UART_Receive(&huart2, received_start, 8, 10) == HAL_OK;
			  			  full_received &= HAL_UART_Receive(&huart2, received_end, 8, 10) == HAL_OK;
			  			  if(full_received){
			  				read = false;
			  //				  HAL_GPIO_TogglePin (GPIOA, GPIO_PIN_6);
			  				  uint16_t freq = (uint16_t)received_freq[0] << 8 | received_freq[1];
			  				  uint64_t start = ((uint64_t)received_start[0] << 56) | ((uint64_t)received_start[1] << 48) |
			  				                        ((uint64_t)received_start[2] << 40) | ((uint64_t)received_start[3] << 32) |
			  				                        ((uint64_t)received_start[4] << 24) | ((uint64_t)received_start[5] << 16) |
			  				                        ((uint64_t)received_start[6] << 8) | received_start[7];
			  				  uint64_t end = ((uint64_t)received_end[0] << 56) | ((uint64_t)received_end[1] << 48) |
			  				  			                        ((uint64_t)received_end[2] << 40) | ((uint64_t)received_end[3] << 32) |
			  				  			                        ((uint64_t)received_end[4] << 24) | ((uint64_t)received_end[5] << 16) |
			  				  			                        ((uint64_t)received_end[6] << 8) | received_end[7];
			  //				  if(freq != 0){
			  //					  HAL_TIM_PWM_Start(htim1, TIM_CHANNEL_2);
			  					  tone(htim1, htim2, freq, (uint32_t)(end-start), 100);
			  //				  }else{
			  //					  HAL_TIM_PWM_Stop(htim1, TIM_CHANNEL_2);
			  //				  }
			  //				  HAL_Delay(15000);
			  			  }
			  		  }
			  	  }
		  }
//		  HAL_UART_Transmit(&huart2, received_data, 12, 1000);
//		  HAL_Delay(1000);
		  return 0;
}
#define DATA_PIN GPIO_PIN_9
#define CLOCK_PIN GPIO_PIN_8
#define LATCH_PIN GPIO_PIN_5

void setRegister(uint16_t val) {
    HAL_GPIO_WritePin(GPIOB, LATCH_PIN, GPIO_PIN_RESET); // Latch low
    for (int i = 0; i < 15; i++) {
        HAL_GPIO_WritePin(GPIOA, DATA_PIN, (val & (1 << (15 - i))) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA, CLOCK_PIN, GPIO_PIN_SET); // Clock pulse
        HAL_Delay(1); // Adjust delay as needed
        HAL_GPIO_WritePin(GPIOA, CLOCK_PIN, GPIO_PIN_RESET);
    }
    HAL_GPIO_WritePin(GPIOB, LATCH_PIN, GPIO_PIN_SET); // Latch high
    HAL_Delay(1); // Adjust delay as needed
}
