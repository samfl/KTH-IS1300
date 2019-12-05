/*
 * display.h
 *
 *  Created on: Nov 25, 2019
 *      Author: samfl
 */

#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_
#endif /* INC_DISPLAY_H_ */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <spi.h>
#include <gpio.h>

void Set_cs(uint8_t);
void Write_data(uint8_t);
void Write_string(char*);
void Reset_display(void);
void Delay_spi(void);
void Display_color(char[]);
void Init_display(void);
void Spi_rdy(void);
