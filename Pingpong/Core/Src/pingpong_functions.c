/**
******************************************************************************
@brief Pingpong, functions for Pingpong-program
@file pingpong_functions.c
@author Sam Florin
@version 1.0
@date 12-August-2019
@brief Functions and structures for program Pingpong
******************************************************************************
*/

#include <stdint.h>
#include <stdbool.h>
#include <gpio.h>

/**
@brief Led_on, turn one of the pingpong leds on
@param uint8_t Lednr , number to the Led that is turned on
	   Lednr can be 1-8, all other values turns all leds off
@return void
*/
void Led_on(uint8_t Lednr) {
	uint8_t i;
	for(i=1; i<= 8; i++) {
		switch(i) {
			case 1 : // Led 1
				if (Lednr==i) HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
				else HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
				break;
			case 2 : // Led 2
				if (Lednr==i) HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
				else HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
				break;
			case 3 : // Led 3
				if (Lednr==i) HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET);
				else HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET);
				break;
			case 4 : // Led 4
				if (Lednr==i) HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_SET);
				else HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_RESET);
				break;
			case 5 : // Led 5
				if (Lednr==i) HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, GPIO_PIN_SET);
				else HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, GPIO_PIN_RESET);
				break;
			case 6 : // Led 6
				if (Lednr==i) HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, GPIO_PIN_SET);
				else HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, GPIO_PIN_RESET);
				break;
			case 7 : // Led 7
				if (Lednr==i) HAL_GPIO_WritePin(LED7_GPIO_Port, LED7_Pin, GPIO_PIN_SET);
				else HAL_GPIO_WritePin(LED7_GPIO_Port, LED7_Pin, GPIO_PIN_RESET);
				break;
			case 8 : // Led 8
				if (Lednr==i) HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, GPIO_PIN_SET);
				else HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, GPIO_PIN_RESET);
				break;
			default :;
		}
	}
	return;
}

/**
@brief Set_led, Set one og the leds
@param uint8_t Lednr , number to the led
@return void
*/
void Set_led(uint8_t Lednr) {
	if (Lednr==1) HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
	if (Lednr==2) HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
	if (Lednr==3) HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET);
	if (Lednr==4) HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_SET);
	if (Lednr==5) HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, GPIO_PIN_SET);
	if (Lednr==6) HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, GPIO_PIN_SET);
	if (Lednr==7) HAL_GPIO_WritePin(LED7_GPIO_Port, LED7_Pin, GPIO_PIN_SET);
	if (Lednr==8) HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, GPIO_PIN_SET);
	return;
}

/**
@brief Reset_led, reset one of the leds
@param uint8_t Lednr , number to the led
@return void
*/
void Reset_led(uint8_t Lednr) {
	if (Lednr==1) HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
	if (Lednr==2) HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
	if (Lednr==3) HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET);
	if (Lednr==4) HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_RESET);
	if (Lednr==5) HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, GPIO_PIN_RESET);
	if (Lednr==6) HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, GPIO_PIN_RESET);
	if (Lednr==7) HAL_GPIO_WritePin(LED7_GPIO_Port, LED7_Pin, GPIO_PIN_RESET);
	if (Lednr==8) HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, GPIO_PIN_RESET);
	return;
}

/**
@brief Set all of the leds
@param void
@return void
*/
void Set_leds(void) {
	uint8_t i=1;
	while(i<=8) {
		Set_led(i);
		i++;
	}
	return;
}

/**
@brief Reset all of the leds
@param void
@return void
*/
void Reset_leds(void) {
	uint8_t i=1;
	while(i<=8) {
		Reset_led(i);
		i++;
	}
	return;
}

/**
@brief Blinking the leds
@param void
@return void
*/
void Game_indication(void){
	for(uint8_t j=1; j<=2; j++){
		Set_leds();
		HAL_Delay(300);
		Reset_leds();
		HAL_Delay(300);
	}
	return;
}

/**
@brief Blinking the leds
@param uint8_t player
@return void
*/
void Duel_over(uint8_t player){
	uint8_t i;
	uint8_t delay;
	for(delay=60; delay>0; delay-=10) {
		if(player==1){
			for(i=1; i<=8; i++) {
				Set_led(i);
				HAL_Delay(delay);
			}
		} else {
			for(i=8; i>0; i--) {
				Set_led(i);
				HAL_Delay(delay);
			}
		}
		Reset_leds();
	}
	Game_indication();
	return;
}

/**
@brief Show_points, shows points after missed ball
@param1 uint8_t L_points points for left player
@param2 uint8_t R_points points for right player
@return void, no return value
*/
void Show_points(uint8_t L_points, uint8_t R_points) {
	for(uint8_t i=1; i<=L_points; i++) {
		Set_led(i);
		HAL_Delay(5);
	}
	for(uint8_t j=8; j>8-R_points; j--) {
		Set_led(j);
		HAL_Delay(5);
	}
	return;
}

/**
@brief R_hit, check if R button is pressed
@param void
@return bool, true if R button pushed, false otherwise
*/
bool R_hit(void) {
	if(!HAL_GPIO_ReadPin(R_button_GPIO_Port, R_button_Pin)) return 1;
	else return 0;
}

/**
@brief L_hit, check if L button is pressed
@param void
@return bool, true if L button pushed, false otherwise
*/
bool L_hit (void) {
	if(!HAL_GPIO_ReadPin(L_button_GPIO_Port, L_button_Pin)) return 1;
	return 0;
}
