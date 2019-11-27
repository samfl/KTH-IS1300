/*
 * display.c
 *
 *  Created on: Nov 25, 2019
 *      Author: samfl
 */

#include <display.h>

void Set_cs(uint8_t signal) {
	HAL_GPIO_WritePin(Chip_select_GPIO_Port, Chip_select_Pin, signal);
}

void Write_data(char data) {
	Set_cs(0);
	HAL_SPI_Transmit(&hspi2, 0x5F, 1,10);
	HAL_SPI_Transmit(&hspi2, (data & 0x0F), 1,10);
	HAL_SPI_Transmit(&hspi2, ((data>>4) & 0x0F), 1,10);
	Set_cs(1);
	Delay_spi();
}

void Write_string(char * string) {
	do {
		Write_data(*string++);
	} while(*string);
}

void Write_instruction(char instruction) {
	// Chip Select (Active High, set to low during a write)
	// Transmit (&hspi2 pointer to SPI config module, lcd_data pointer to dataBuffer, Size (in bytes) to be sent, Timeout duration

	Set_cs(0);
	HAL_SPI_Transmit(&hspi2, 0x1F, 1,10);
	HAL_SPI_Transmit(&hspi2, (instruction & 0x0F), 1,10);
	HAL_SPI_Transmit(&hspi2, ((instruction>>4) & 0x0F), 1,10);
	Set_cs(1);
	Delay_spi();
}

void Delay_spi(void) {
	HAL_Delay(10);
}

void Clear_display(void) {
	Write_instruction(0x01);
}

void Init_display(void) {

	Write_instruction(0x3A);	// 8-Bit data length extension Bit RE=1; REV=0
	Write_instruction(0x09);	// 4 line display
	Write_instruction(0x06);	// 8-Bit data length extension Bit RE=0; IS=1 Bottom View
	Write_instruction(0x1E);	// BS1=1
	Write_instruction(0x39);	// 8 bit data length extension
	Write_instruction(0x1B);	// BS0=1
	Write_instruction(0x6E);	// Devider on and set value
	Write_instruction(0x56);	// Booster on and set contrast
	Write_instruction(0x7A);	// Set contrast
	Write_instruction(0x38); 	// 8 bit data length extension
	Write_instruction(0x0F);	// Display on, cursor on, blink on

	return;
}

void Display_color(char color[]) {
	if(!strcmp(color,"red"))
		HAL_GPIO_WritePin(Display_red_GPIO_Port, Display_red_Pin, SET);
	else if(!strcmp(color,"green"))
		HAL_GPIO_WritePin(Display_green_GPIO_Port, Display_green_Pin, SET);
	else
		HAL_GPIO_WritePin(Display_white_GPIO_Port, Display_white_Pin, SET);

	return;
}
