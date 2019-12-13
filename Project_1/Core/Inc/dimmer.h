/*
 * dimmer.h
 *
 *  Created on: Dec 12, 2019
 *      Author: samfl
 */

#ifndef INC_DIMMER_H_
#define INC_DIMMER_H_
#endif /* INC_DIMMER_H_ */

#include <stdint.h>
#include "tim.h"
#include "adc.h"

void Init_potentiometer(void);
void Set_backlight_dimmer(uint32_t);
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *);
