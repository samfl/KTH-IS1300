/*
 * test.c
 *
 *  Created on: Nov 25, 2019
 *      Author: samfl
 */
#include <test.h>

void Test_program(void) {

	// OK
	Test_display_background("green");
	// OK
	Test_display();
	// OK - Input CLock in Set_time..
	Test_rtc();

	return;
}

void Test_display(void) {
	Init_display();
//	Write_data(0x61);
	HAL_GPIO_WritePin(Display_white_GPIO_Port, Display_white_Pin, SET);
}

void Test_display_background(char color[]) {
	Display_color(color);
}

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
