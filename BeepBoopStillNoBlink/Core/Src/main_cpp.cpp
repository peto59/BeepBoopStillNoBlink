#include "main_cpp.h"
#include "notes.h"
//#include "stdbool.h"

const uint8_t seg[4] = {0x02,0x04,0x08,0x10};
const uint8_t num[10] = {
		0b10000001,
		0b11110011,
		0b01001001,
		0b01100001,
		0b00110011,
		0b00100101,
		0b00000101,
		0b11110001,
		0b00000001,
		0b00100001
};
bool read = true;
//0bgfedcbap
uint8_t U = 0b10000011;
uint8_t O = 0b10000001;
uint8_t L = 0b10001111;
uint8_t M = 0b10010001;
uint8_t o = 0b01000111;
uint8_t d = 0b01000011;
void setRead(void){
	read = true;
}
uint32_t lastButtonPressTimeA = 0;
uint32_t lastButtonPressTimeB = 0;
uint32_t lastButtonPressTimeC = 0;
uint32_t lastValueTime = 0;
uint8_t volume = 100;
uint8_t button_mode = 0;
uint8_t play_mode = 0;
uint8_t readPlayMode(void){
	return play_mode;
}
uint32_t DEBOUNCE_TIME = 150;
#define DEFAULT_DEBOUNCE_TIME 150
#define VALUE_SHOW_TIME 5000
bool checkButtonPressA(void)
{
    if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_RESET) // Button is pressed
    {
        uint32_t currentTime = HAL_GetTick();
        if (currentTime - lastButtonPressTimeA > DEBOUNCE_TIME)
        {
            // Button press is valid, perform your action here
        	lastButtonPressTimeA = currentTime;
        	return true;
        }
    }
    return false;
}
bool checkButtonPressB(void)
{
    if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) == GPIO_PIN_RESET) // Button is pressed
    {
        uint32_t currentTime = HAL_GetTick();
        if(currentTime - lastButtonPressTimeB > 1000){
			DEBOUNCE_TIME = DEFAULT_DEBOUNCE_TIME;
		}
		else if (DEBOUNCE_TIME > 50){
			DEBOUNCE_TIME -= 3;
		}
        if (currentTime - lastButtonPressTimeB > DEBOUNCE_TIME)
        {
            // Button press is valid, perform your action here
        	lastButtonPressTimeB = currentTime;
        	return true;
        }
    }
    return false;
}
bool checkButtonPressC(void)
{
    if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1) == GPIO_PIN_RESET) // Button is pressed
    {
        uint32_t currentTime = HAL_GetTick();
        if(currentTime - lastButtonPressTimeC > 1000){
			DEBOUNCE_TIME = DEFAULT_DEBOUNCE_TIME;
		}
		else if (DEBOUNCE_TIME > 50){
			DEBOUNCE_TIME -= 1;
		}
        if (currentTime - lastButtonPressTimeC > DEBOUNCE_TIME)
        {
            // Button press is valid, perform your action here
            lastButtonPressTimeC = currentTime;
            return true;
        }
    }
    return false;
}

void playTone( TIM_HandleTypeDef *htim1, TIM_HandleTypeDef *htim2, uint16_t freq, uint64_t start, uint64_t end){
	tone(htim1, htim2, freq, end-start, volume);
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
//	HAL_UART_Receive_IT(&huart2, UART2_rxBuffer, 18);
//	scale(htim1, htim2);
//	scale(htim1);
//	while(1){
//		setRegister((U<<8) | seg[0]);
//		setRegister((O<<8) | seg[1]);
//		setRegister((L<<8) | seg[2]);
//		setRegister((num[3]<<8) | seg[3]);
//	}
//		  uint8_t received_freq[2];
//		  uint8_t received_start[8];
//		  uint8_t received_end[8];
		  while (1){
			  uint32_t currentTime = HAL_GetTick();
			  if (currentTime - lastValueTime < VALUE_SHOW_TIME){
				  if(button_mode == 0){
					  setRegister((U<<8) | seg[0]);
					  setRegister((O<<8) | seg[1]);
					  setRegister((L<<8) | seg[2]);
				  }else if (button_mode == 1){
					  setRegister((M<<8) | seg[0]);
					  setRegister((o<<8) | seg[1]);
					  setRegister((d<<8) | seg[2]);
//					  setRegister((num[button_mode]<<8) | seg[3]);
				  }
			  }else if(button_mode == 0){
				  if (volume == 100){
					  setRegister((num[1]<<8) | seg[1]);
					  setRegister((num[0]<<8) | seg[2]);
					  setRegister((num[0]<<8) | seg[3]);
				  }else if (volume > 9){
//					  setRegister((0xff<<8) | seg[1]);
					  uint8_t tenths = (uint8_t)(volume / 10);
					  setRegister((num[tenths]<<8) | seg[2]);
					  setRegister((num[volume-(tenths*10)]<<8) | seg[3]);
				  }else{
//					  setRegister((0xff<<8) | seg[1]);
//					  setRegister((0xff<<8) | seg[2]);
					  setRegister((num[volume]<<8) | seg[3]);
				  }

			  }else if(button_mode == 1){
				  setRegister((num[play_mode]<<8) | seg[3]);
			  }
			  if (checkButtonPressA()){
				  button_mode++;
				  if(button_mode > 1){
					  button_mode = 0;
				  }
				  lastValueTime = currentTime;
			  }
			  if (checkButtonPressB()){
				  if (button_mode == 0){
					  if(volume > 0){
						  volume--;
					  }
				  }else if (button_mode == 1){
					  play_mode--;
					  if(play_mode < 0){
						  play_mode = 2;
					  }
				  }
				  lastValueTime = 0;
			  }
			  if (checkButtonPressC()){
				  if (button_mode == 0){
					  if(volume < 100){
						  volume++;
					  }
				  }else if (button_mode == 1){
					  play_mode++;
					  if(play_mode > 2){
						  play_mode = 0;
					  }
				  }
				  lastValueTime = 0;
			  }
//			  bool full_received = true;

//			  if(read){
//
//			  		  full_received &= HAL_UART_Receive(&huart2, received_freq, 2, 10) == HAL_OK;
//			  		  if(full_received){
//			  //			  HAL_GPIO_TogglePin (GPIOA, GPIO_PIN_6);
//			  			  full_received &= HAL_UART_Receive(&huart2, received_start, 8, 10) == HAL_OK;
//			  			  full_received &= HAL_UART_Receive(&huart2, received_end, 8, 10) == HAL_OK;
//			  			  if(full_received){
//			  				read = false;
//			  //				  HAL_GPIO_TogglePin (GPIOA, GPIO_PIN_6);
//			  				  uint16_t freq = (uint16_t)received_freq[0] << 8 | received_freq[1];
//			  				  uint64_t start = ((uint64_t)received_start[0] << 56) | ((uint64_t)received_start[1] << 48) |
//			  				                        ((uint64_t)received_start[2] << 40) | ((uint64_t)received_start[3] << 32) |
//			  				                        ((uint64_t)received_start[4] << 24) | ((uint64_t)received_start[5] << 16) |
//			  				                        ((uint64_t)received_start[6] << 8) | received_start[7];
//			  				  uint64_t end = ((uint64_t)received_end[0] << 56) | ((uint64_t)received_end[1] << 48) |
//			  				  			                        ((uint64_t)received_end[2] << 40) | ((uint64_t)received_end[3] << 32) |
//			  				  			                        ((uint64_t)received_end[4] << 24) | ((uint64_t)received_end[5] << 16) |
//			  				  			                        ((uint64_t)received_end[6] << 8) | received_end[7];
//			  //				  if(freq != 0){
//			  //					  HAL_TIM_PWM_Start(htim1, TIM_CHANNEL_2);
//			  					  tone(htim1, htim2, freq, (uint32_t)(end-start), 100);
//			  //				  }else{
//			  //					  HAL_TIM_PWM_Stop(htim1, TIM_CHANNEL_2);
//			  //				  }
//			  //				  HAL_Delay(15000);
//			  			  }
//			  		  }
//			  	  }
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
//    shiftToLatch();
}

void shiftToLatch(void){
	HAL_GPIO_WritePin(GPIOA, DATA_PIN, GPIO_PIN_SET); // Set data pin high
	HAL_Delay(1); // Wait for a short period
	HAL_GPIO_WritePin(GPIOA, CLOCK_PIN, GPIO_PIN_SET); // Pulse SRCLK pin high
	HAL_Delay(1); // Wait for a short period
	HAL_GPIO_WritePin(GPIOA, CLOCK_PIN, GPIO_PIN_RESET); // Pulse SRCLK pin low
	HAL_Delay(1); // Wait for a short period

	// Transfer data from shift register to latch register
	HAL_GPIO_WritePin(GPIOB, LATCH_PIN, GPIO_PIN_SET); // Pulse LCLK pin high
	HAL_Delay(1); // Wait for a short period
	HAL_GPIO_WritePin(GPIOB, LATCH_PIN, GPIO_PIN_RESET); // Pulse LCLK pin low
	HAL_Delay(1); // Wait for a short period
}
