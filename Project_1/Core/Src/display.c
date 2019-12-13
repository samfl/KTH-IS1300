/*
 * display.c
 *
 * Description: Functions to support initialization, reset, writing etc. to the display.
 *  Created on: Nov 25, 2019
 *      Author: samfl
 */

#include <display.h>

/**
 *  Helper function to faster set the Chip Select bit for SPI communication.
 */
void Set_cs(uint8_t signal) {
	HAL_GPIO_WritePin(CS_SPI2_GPIO_Port, CS_SPI2_Pin, signal);
}


/**
 *  Helper function to write ONE character to the display.
 */
void Write_data(uint8_t hexa) {
    Spi_rdy();
	uint8_t data[3];
	data[0] = 0x5f;
	data[1] = hexa & 0x0f;
	data[2] = (hexa >> 4) & 0x0f;
	HAL_SPI_Transmit(&hspi2, data,3,10);
	return;
}


/**
 *  To write a string to the Display.
 */
void Write_string(char * string) {
	do {
		Write_data(*string++);
	} while(*string);
	Set_cs(1);
}


/**
 *  To reset/clear the display.
 */
void Reset_display(void) {
	HAL_GPIO_WritePin(Display_reset_GPIO_Port, Display_reset_Pin, SET);
	HAL_Delay(10);
	HAL_GPIO_WritePin(Display_reset_GPIO_Port, Display_reset_Pin, RESET);
	HAL_Delay(100);
}


/**
 *  To display a certain color, RED is disabled while demonstrating the PWM backlight dimmer.
 */
void Display_color(char* color) {
	//if(!strcmp(color, "red")) HAL_GPIO_WritePin(Display_red_GPIO_Port, Display_red_Pin, SET);
	if(!strcmp(color, "green")) HAL_GPIO_WritePin(Display_green_GPIO_Port, Display_green_Pin, SET);
	else if(!strcmp(color, "white")) HAL_GPIO_WritePin(Display_white_GPIO_Port, Display_white_Pin, SET);
	else printf("No color was set");
}


/**
 *  Helper function to write an instruction(configuration) to the display.
 */
void Write_ins(uint8_t hexa){
	Spi_rdy();
	uint8_t data[3];
	data[0] = 0x1f;
	data[1] = hexa & 0x0f;
	data[2] = (hexa >> 4) & 0x0f;
	HAL_SPI_Transmit(&hspi2, data,3,10);
	return;
}


/**
 *  Helper function to improve readability in SPI communication funtions
 */
void Spi_rdy(void) {
    Set_cs(1);
    HAL_Delay(10);
    Set_cs(0);
}

/**
 *  Helper function to improve readability in SPI communication funtions
 */
void Clear_display(void) {
	Write_ins(0x01);
}


/**
 *  To initialize the display, ready for writing DATA to.
 */
void Init_display(void)
{
	    // Reset Display
		Spi_rdy();
	    HAL_GPIO_WritePin(Display_reset_GPIO_Port, Display_reset_Pin, GPIO_PIN_SET);
	    HAL_Delay(10);

	    // Initialization Example
	    Write_ins(0x3a); // function set: RE=1; REV=0
	    Write_ins(0x09); // extended function set: 4-line initialization
	    Write_ins(0x06); // entry mode set: Botton View
	    Write_ins(0x1e); // bias setting: BS1 = 1
	    Write_ins(0x39); // function set: RE=0, IS=1
	    Write_ins(0x1b); // internal osc: BS0=1 -> Bias=1/6
	    Write_ins(0x6e); // follower control: divider on and set value
	    Write_ins(0x56); // power control: booster on and set contrast
	    Write_ins(0x7a); // contrast set: DB3-DB0=C3-C0
	    Write_ins(0x38); // function set: RE=0, IS=0

		// Change View
		Write_ins(0x3a); // function set: RE=1, IS=0
		Write_ins(0x06); // entry mode: bottom view
		Write_ins(0x38); // function set: RE=0, IS=0

		// Display On
	    Write_ins(0x0f); // display on, cursor on, blink on

	    // Clear Display
	    Clear_display();

	    // String Sequence Line 1
	    //Write_ins(0x80); //address
	    //Write_string("Sam");

	    // String Sequence Line 2
	    // Write_ins(0xa0); //address
	    // Write_string("Florin");

	    // String Sequence Line 3
	    // Write_ins(0xc0); //address
	    // Write_string("S-tuna");

	    // String Sequence Line 4
	    // Write_ins(0xe0); //address
	    // Write_string("TIDAB");

	    // Stop Transmit
	    Set_cs(1);
}
