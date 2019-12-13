/*
 * process.c
 * Description: Handles all the project components
 *  Created on: Dec 13, 2019
 *      Author: samfl
 */

#include <process.h>

/**
 * Configures all the peripherals.
 */
void Set_up(void) {
	Init_potentiometer();
	Init_Display();
	Set_time(Input_clock());
}

/**
 * Sends current time to USB COM.
 */
void Send_rtc_to_usb(void) {
	static char new_line = '\n\r';
	HAL_UART_Transmit(&huart5, Get_time(), 8, 1);
	HAL_UART_Transmit(&huart5, &new_line, 2, 1);
}

/**
 * Writes current time to the display.
 */
void Send_rtc_to_display(void) {
	Write_ins(0x01);
	Write_string(Get_time());
}

/**
 * Updating the clock.
 */
void Start_clock(void) {
	for(;;) {
		Send_rtc_to_usb();
		Send_rtc_to_display
		HAL_Delay(1000);
	}

}
