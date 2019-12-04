/*
 * display.c
 *
 *  Created on: Nov 25, 2019
 *      Author: samfl
 */

#include <display.h>

void Set_cs(uint8_t signal) {
	HAL_GPIO_WritePin(CS_SPI2_GPIO_Port, CS_SPI2_Pin, signal);
}

void Write_data(uint8_t hexa) {
    Spi_rdy();
	uint8_t data[3];
	data[0] = 0x5f;
	data[1] = hexa & 0x0f;
	data[2] = (hexa >> 4) & 0x0f;
	HAL_SPI_Transmit(&hspi2, data,3,10);
	return;
}

void Write_string(char * string) {
	do {
		Write_data(*string++);
	} while(*string);
}

void Delay_spi(void) {
	HAL_Delay(10);
}

void Reset_display(void) {
	HAL_GPIO_WritePin(Display_reset_GPIO_Port, Display_reset_Pin, SET);
	Delay_spi();
	HAL_GPIO_WritePin(Display_reset_GPIO_Port, Display_reset_Pin, RESET);
	HAL_Delay(100);
}

void Display_color(char color[]) {
	if(strcmp(color, "red")) HAL_GPIO_WritePin(Display_red_GPIO_Port, Display_red_Pin, SET);
	if(strcmp(color, "green")) HAL_GPIO_WritePin(Display_green_GPIO_Port, Display_green_Pin, SET);
	if(strcmp(color, "white")) HAL_GPIO_WritePin(Display_white_GPIO_Port, Display_white_Pin, SET);
	return;
}

void Write_ins(uint8_t hexa){
	Spi_rdy();
	uint8_t data[3];
	data[0] = 0x1f;
	data[1] = hexa & 0x0f;
	data[2] = (hexa >> 4) & 0x0f;
	HAL_SPI_Transmit(&hspi2, data,3,10);
	return;
}

void Spi_rdy(void) {
    Set_cs(1);
    HAL_Delay(10);
    Set_cs(0);
}

void Init_display(void)
{
		// Delay
		Spi_rdy();

	    // Reset Display
	    HAL_GPIO_WritePin(Display_reset_GPIO_Port, Display_reset_Pin, GPIO_PIN_SET);
	    HAL_Delay(10);

	    Write_ins(0x3a);
	    Write_ins(0x09); //4 line initiation
	    Write_ins(0x06); //botton view
	    Write_ins(0x1e);//bias setting
	    Write_ins(0x39); //function set
	    Write_ins(0x1b); //internal osc
	    Write_ins(0x6e); //follower
	    Write_ins(0x56); //power control
	    Write_ins(0x7a); //contrast
	    Write_ins(0x38); //function set
		Write_ins(0x3a); //adress
		Write_ins(0x72); //adress

		Write_data(0x00); //adress
		Write_ins(0x38); //adress
	    Write_ins(0x0f); //display on
	    Write_ins(0x01); //adress

	    // DATA
	    // One letter: Write_data(0xff);
	    // String sequence: Write_string("your string!");

	    Write_string("Hallo Bengan!");
	    Set_cs(1);
	    Write_data(0xff); //ascii
	    HAL_Delay(10);
}
