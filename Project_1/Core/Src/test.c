/*
 * test.c
 * Description: To test all the functionality in the program.
 *  Created on: Nov 25, 2019
 *      Author: samfl
 */

#include <test.h>

/**
 * Main test-file.
 */
void Test_program(void) {
	Test_potentiometer(); /** PASSED - Dims the background on potentiometer change */
	// Test_display_background("green"); /** PASSED - Changes the background color of the display */
	Test_display(); /** PASSED - Displays the inputed text */
	Test_rtc(); /** PASSED - Writes and updates the current time to the display and to the USB COM */
	return;
}

/**
 * To test Init, write, reset, config the display.
 */
void Test_display(void) {
	Init_display();
//	Write_data(0x61);
	HAL_GPIO_WritePin(Display_white_GPIO_Port, Display_white_Pin, SET);
}

/**
 * To test the background lighting.
 */
void Test_display_background(char color[]) {
	Display_color(color);
}

/**
 * To test the Real Time Clock configure and output.
 */
void Test_rtc(void) {
	Set_time(Input_clock());
	char new_line = '\n\r';
	for(;;) {
		Write_ins(0x01);
		Write_string(Get_time());
		HAL_UART_Transmit(&huart5, Get_time(), 8, 1);
		HAL_UART_Transmit(&huart5, &new_line, 2, 1);
		HAL_Delay(1000);
	}
}

/**
 * To test the potentiometer and PWM background lightning.
 */
void Test_potentiometer(void) {
	Init_potentiometer();
}
