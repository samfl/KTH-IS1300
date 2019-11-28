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

void Write_data(char data) {
	Set_cs(0);
	HAL_SPI_Transmit(&hspi2, 0x5F, 1,10);
	Set_cs(1);
	Delay_spi;

	Set_cs(0);
	HAL_SPI_Transmit(&hspi2, (data & 0x0F), 1,10);
	Set_cs(1);
	Delay_spi;

	Set_cs(0);
	HAL_SPI_Transmit(&hspi2, ((data>>4) & 0x0F), 1,10);
	Set_cs(1);
	Delay_spi();
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
	if(!strcmp(color,"red"))
		HAL_GPIO_WritePin(Display_red_GPIO_Port, Display_red_Pin, SET);
	else if(!strcmp(color,"green"))
		HAL_GPIO_WritePin(Display_green_GPIO_Port, Display_green_Pin, SET);
	else
		HAL_GPIO_WritePin(Display_white_GPIO_Port, Display_white_Pin, SET);

	return;
}

void prephexa(uint8_t hexa, uint8_t *adress){
	adress[1] = hexa & 0x0f;
	adress[2] = (hexa >> 4) & 0x0f;

	return;
}

void LCDinit(void)
{
	uint8_t lcd_data[3];
	lcd_data[0] = 0x1f;

	    HAL_GPIO_WritePin(Display_green_GPIO_Port, Display_green_Pin, GPIO_PIN_RESET);
	    HAL_GPIO_WritePin(Display_reset_GPIO_Port, Display_reset_Pin, GPIO_PIN_RESET);
	    HAL_Delay(10);
	    HAL_GPIO_WritePin(Display_reset_GPIO_Port, Display_reset_Pin, GPIO_PIN_SET);
	    HAL_Delay(10);
	    HAL_GPIO_WritePin(Display_reset_GPIO_Port, Display_reset_Pin, GPIO_PIN_RESET);
	    HAL_GPIO_WritePin(Display_green_GPIO_Port, Display_green_Pin, GPIO_PIN_SET);

	    HAL_GPIO_WritePin(CS_SPI2_GPIO_Port, CS_SPI2_Pin, GPIO_PIN_SET);
	    HAL_Delay(10);
	    HAL_GPIO_WritePin(CS_SPI2_GPIO_Port, CS_SPI2_Pin, GPIO_PIN_RESET);


	    HAL_GPIO_WritePin(Display_reset_GPIO_Port, Display_reset_Pin, GPIO_PIN_SET);
	      HAL_Delay(10);


	    prephexa(0x3a, lcd_data);
	    HAL_SPI_Transmit(&hspi2, lcd_data,3,10); //function set

	    HAL_GPIO_WritePin(CS_SPI2_GPIO_Port, CS_SPI2_Pin, GPIO_PIN_SET);
	    HAL_Delay(10);
	    HAL_GPIO_WritePin(CS_SPI2_GPIO_Port, CS_SPI2_Pin, GPIO_PIN_RESET);

	    prephexa(0x09, lcd_data); //4 line initiation
	    HAL_SPI_Transmit(&hspi2, lcd_data,3,10);

	    HAL_GPIO_WritePin(CS_SPI2_GPIO_Port, CS_SPI2_Pin, GPIO_PIN_SET);
	    HAL_Delay(10);
	    HAL_GPIO_WritePin(CS_SPI2_GPIO_Port, CS_SPI2_Pin, GPIO_PIN_RESET);

	    prephexa(0x06, lcd_data); //botton view
	    HAL_SPI_Transmit(&hspi2, lcd_data,3,10);

	    HAL_GPIO_WritePin(CS_SPI2_GPIO_Port, CS_SPI2_Pin, GPIO_PIN_SET);
	    HAL_Delay(10);
	    HAL_GPIO_WritePin(CS_SPI2_GPIO_Port, CS_SPI2_Pin, GPIO_PIN_RESET);

	    prephexa(0x1e, lcd_data);//bias setting
	    HAL_SPI_Transmit(&hspi2, lcd_data,3,10);

	    HAL_GPIO_WritePin(CS_SPI2_GPIO_Port, CS_SPI2_Pin, GPIO_PIN_SET);
	    HAL_Delay(10);
	    HAL_GPIO_WritePin(CS_SPI2_GPIO_Port, CS_SPI2_Pin, GPIO_PIN_RESET);

	    prephexa(0x39, lcd_data); //function set
	    HAL_SPI_Transmit(&hspi2, lcd_data,3,10);

	    HAL_GPIO_WritePin(CS_SPI2_GPIO_Port, CS_SPI2_Pin, GPIO_PIN_SET);
	    HAL_Delay(10);
	    HAL_GPIO_WritePin(CS_SPI2_GPIO_Port, CS_SPI2_Pin, GPIO_PIN_RESET);

	    prephexa(0x1b, lcd_data); //internal osc
	    HAL_SPI_Transmit(&hspi2, lcd_data,3,10);

	    HAL_GPIO_WritePin(CS_SPI2_GPIO_Port, CS_SPI2_Pin, GPIO_PIN_SET);
	    HAL_Delay(10);
	    HAL_GPIO_WritePin(CS_SPI2_GPIO_Port, CS_SPI2_Pin, GPIO_PIN_RESET);

	    prephexa(0x6e, lcd_data); //follower
	    HAL_SPI_Transmit(&hspi2, lcd_data,3,10);

	    HAL_GPIO_WritePin(CS_SPI2_GPIO_Port, CS_SPI2_Pin, GPIO_PIN_SET);
	    HAL_Delay(10);
	    HAL_GPIO_WritePin(CS_SPI2_GPIO_Port, CS_SPI2_Pin, GPIO_PIN_RESET);

	    prephexa(0x56, lcd_data); //power control
	    HAL_SPI_Transmit(&hspi2, lcd_data,3,10);

	    HAL_GPIO_WritePin(CS_SPI2_GPIO_Port, CS_SPI2_Pin, GPIO_PIN_SET);
	    HAL_Delay(10);
	    HAL_GPIO_WritePin(CS_SPI2_GPIO_Port, CS_SPI2_Pin, GPIO_PIN_RESET);

	    prephexa(0x7a, lcd_data); //contrast
	    HAL_SPI_Transmit(&hspi2, lcd_data,3,10);

	    HAL_GPIO_WritePin(CS_SPI2_GPIO_Port, CS_SPI2_Pin, GPIO_PIN_SET);
	    HAL_Delay(10);
	    HAL_GPIO_WritePin(CS_SPI2_GPIO_Port, CS_SPI2_Pin, GPIO_PIN_RESET);

	    prephexa(0x38, lcd_data); //function set
	    HAL_SPI_Transmit(&hspi2, lcd_data,3,10);

	    HAL_GPIO_WritePin(CS_SPI2_GPIO_Port, CS_SPI2_Pin, GPIO_PIN_SET);
	    HAL_Delay(10);

	    ////// ------------------------------------------------
	      HAL_GPIO_WritePin(CS_SPI2_GPIO_Port, CS_SPI2_Pin, GPIO_PIN_RESET);

	      prephexa(0x3a, lcd_data); //adress
	      HAL_SPI_Transmit(&hspi2, lcd_data,3,10);

	      HAL_GPIO_WritePin(CS_SPI2_GPIO_Port, CS_SPI2_Pin, GPIO_PIN_SET);
	      HAL_Delay(10);

	      HAL_GPIO_WritePin(CS_SPI2_GPIO_Port, CS_SPI2_Pin, GPIO_PIN_RESET);

	      prephexa(0x72, lcd_data); //adress
	      HAL_SPI_Transmit(&hspi2, lcd_data,3,10);

	      HAL_GPIO_WritePin(CS_SPI2_GPIO_Port, CS_SPI2_Pin, GPIO_PIN_SET);
	      HAL_Delay(10);

	      HAL_GPIO_WritePin(CS_SPI2_GPIO_Port, CS_SPI2_Pin, GPIO_PIN_RESET);
	      lcd_data[0] = 0x5f;
	      prephexa(0x00, lcd_data); //adress
	      HAL_SPI_Transmit(&hspi2, lcd_data,3,10);

	      HAL_GPIO_WritePin(CS_SPI2_GPIO_Port, CS_SPI2_Pin, GPIO_PIN_SET);
	      HAL_Delay(10);

	      HAL_GPIO_WritePin(CS_SPI2_GPIO_Port, CS_SPI2_Pin, GPIO_PIN_RESET);
	        lcd_data[0] = 0x1f;
	        prephexa(0x38, lcd_data); //adress
	        HAL_SPI_Transmit(&hspi2, lcd_data,3,10);

	        HAL_GPIO_WritePin(CS_SPI2_GPIO_Port, CS_SPI2_Pin, GPIO_PIN_SET);
	        HAL_Delay(10);

	    ////


	    HAL_GPIO_WritePin(CS_SPI2_GPIO_Port, CS_SPI2_Pin, GPIO_PIN_RESET);

	    prephexa(0x0f, lcd_data); //display on
	    HAL_SPI_Transmit(&hspi2, lcd_data,3,10);

	    HAL_GPIO_WritePin(CS_SPI2_GPIO_Port, CS_SPI2_Pin, GPIO_PIN_SET);
	    HAL_Delay(10);
	    HAL_GPIO_WritePin(CS_SPI2_GPIO_Port, CS_SPI2_Pin, GPIO_PIN_RESET);

	    prephexa(0x01, lcd_data); //adress
	    HAL_SPI_Transmit(&hspi2, lcd_data,3,10);

	    HAL_GPIO_WritePin(CS_SPI2_GPIO_Port, CS_SPI2_Pin, GPIO_PIN_SET);
	    HAL_Delay(10);



	    lcd_data[0] = 0x5f;
	    HAL_GPIO_WritePin(CS_SPI2_GPIO_Port, CS_SPI2_Pin, GPIO_PIN_RESET);

	    prephexa(0xff, lcd_data); //ascii
	    HAL_SPI_Transmit(&hspi2, lcd_data,3,10);

	    HAL_GPIO_WritePin(CS_SPI2_GPIO_Port, CS_SPI2_Pin, GPIO_PIN_SET);
	    HAL_Delay(10);

	    HAL_GPIO_WritePin(CS_SPI2_GPIO_Port, CS_SPI2_Pin, GPIO_PIN_RESET);

	    prephexa(0x30, lcd_data); //ascii
	    HAL_SPI_Transmit(&hspi2, lcd_data,3,10);

	    HAL_GPIO_WritePin(CS_SPI2_GPIO_Port, CS_SPI2_Pin, GPIO_PIN_SET);
	    HAL_Delay(10);


}
