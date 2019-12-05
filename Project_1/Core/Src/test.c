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
