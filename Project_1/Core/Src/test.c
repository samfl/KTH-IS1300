/*
 * test.c
 *
 *  Created on: Nov 25, 2019
 *      Author: samfl
 */
#include <test.h>

void Test_program(void) {
//	Test_display_background("red");
//	Test_display_background("green");
	Test_display_background("white");
	Test_display();

	return;
}

void Test_display(void) {
//	Init_display();
//	Write_data(0x61);
	LCDinit();
}

void Test_display_background(char color[]) {
	Display_color(color);
}