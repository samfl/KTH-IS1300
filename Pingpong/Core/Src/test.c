/**
******************************************************************************
@brief Pingpong, state machine for Pingpong-program
@file pingpong_functions.c
@author Sam Florin
@version 1.0
@date 06-November-2019
@brief Structure/state machine for pingpong program.
******************************************************************************
*/
#include <stdint.h>
#include <stdbool.h>
#include <pingpong_functions.h>
#include <test.h>
#include <gpio.h>

void Test_program(void) {
	/*
	Test_led_on();
	Test_set_led();
	Test_reset_led();
	Test_set_leds();
	Test_reset_leds();
	Test_game_indication();

	Test_show_points();
	Test_buttons();
	*/
	Test_duel_over();
}

void Test_led_on(void) {
	uint8_t Lednr;

	for(Lednr=1; Lednr<= 8; Lednr++) {
		Led_on(Lednr);
		HAL_Delay(500);
	}
	Led_on(9);
	HAL_Delay(1000);
	return;
}

void Test_set_led(void) {
	uint8_t i;

	for(i=1; i<=8; i++){
		Set_led(i);
		HAL_Delay(200);
	}
	return;
}

void Test_reset_led(void) {
	uint8_t i;

	for(i=8; i>0; i--){
		Reset_led(i);
		HAL_Delay(200);
	}
	return;
}

void Test_set_leds(void) {
	HAL_Delay(100);
	Set_leds();
	HAL_Delay(500);
	return;
}

void Test_reset_leds(void) {
	Reset_leds();
	HAL_Delay(500);
	return;
}

void Test_game_indication(void) {
	HAL_Delay(500);
	Game_indication();
	return;
}

void Test_duel_over(void) {
	Duel_over(1);
	HAL_Delay(500);
	Duel_over(2);
	return;
}

void Test_show_points(void) {
	Show_points(3,2);
	return;
}

void Test_buttons(void) {
	uint8_t j;

	/* Checking buttons */
	j=4;
	Led_on(j); // Light on
	while (j<9 && j>0){
		if (L_hit() == true) { // Wait for left button hit
			j++; // next led to the right
			Led_on(j); // Light on
			HAL_Delay(100); // 100 ms
			while ( L_hit() == true ); // Wait for button release
			HAL_Delay(100); // 100 ms
		}
		if ( R_hit() == true ){ // Wait for right button hit
			j--; // next led to the left
			Led_on(j); // Light on
			HAL_Delay(100); // 100 ms
			while ( R_hit() == true ); // Wait for button release
			HAL_Delay(100); // 100 ms
			if (j<1) j=0; // Start again from left
		}
	}
	return;
}
