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

void Clear_display(void) {
	Write_instruction(0x01);
}

void Reset_display(void) {
	HAL_GPIO_WritePin(Display_reset_GPIO_Port, Display_reset_Pin, SET);
	Delay_spi();
	HAL_GPIO_WritePin(Display_reset_GPIO_Port, Display_reset_Pin, RESET);
	HAL_Delay(100);
}

void Write_instruction(char instruction) {
	// Chip Select (Active High, set to low during a write)
	// Transmit (&hspi2 pointer to SPI config module, lcd_data pointer to dataBuffer, Size (in bytes) to be sent, Timeout duration

	Set_cs(0);
	HAL_SPI_Transmit(&hspi2, 0x1F, 1,10);
	Set_cs(1);
	Delay_spi();

	Set_cs(0);
	HAL_SPI_Transmit(&hspi2, (instruction & 0x0F), 1,10);
	Set_cs(1);
	Delay_spi();

	Set_cs(0);
	HAL_SPI_Transmit(&hspi2, ((instruction>>4) & 0x0F), 1,10);
	Set_cs(1);
	Delay_spi();
}

void Init_display(void) {
	Reset_display();
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
	if(strcmp(color, "red")) HAL_GPIO_WritePin(Display_red_GPIO_Port, Display_red_Pin, SET);
	if(strcmp(color, "green")) HAL_GPIO_WritePin(Display_green_GPIO_Port, Display_green_Pin, SET);
	if(strcmp(color, "white")) HAL_GPIO_WritePin(Display_white_GPIO_Port, Display_white_Pin, SET);
	return;
}

void Write_ins(uint8_t hexa){
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
void LCDinit(void)
{
		// Delay
		Spi_rdy();

	    // Reset Display
	    HAL_GPIO_WritePin(Display_reset_GPIO_Port, Display_reset_Pin, GPIO_PIN_SET);
	    HAL_Delay(10);

	    Write_ins(0x3a);
	    Spi_rdy();

	    Write_ins(0x09); //4 line initiation
	    Spi_rdy();

	    Write_ins(0x06); //botton view
	    Spi_rdy();

	    Write_ins(0x1e);//bias setting
	    Spi_rdy();

	    Write_ins(0x39); //function set
	    Spi_rdy();

	    Write_ins(0x1b); //internal osc
	    Spi_rdy();

	    Write_ins(0x6e); //follower
	    Spi_rdy();

	    Write_ins(0x56); //power control
	    Spi_rdy();

	    Write_ins(0x7a); //contrast
	    Spi_rdy();

	    Write_ins(0x38); //function set
	    Spi_rdy();

		Write_ins(0x3a); //adress
		Spi_rdy();

		Write_ins(0x72); //adress
		Spi_rdy();

		Write_data(0x00); //adress
		Spi_rdy();

		Write_ins(0x38); //adress
		Spi_rdy();

	    Write_ins(0x0f); //display on
	    Spi_rdy();

	    Write_ins(0x01); //adress
	    Spi_rdy();

	    // DATA
	    Write_data(0xff); //ascii
	    Spi_rdy();

	    Write_data(0x30); //ascii
	    Set_cs(1);

	    HAL_Delay(10);
}
