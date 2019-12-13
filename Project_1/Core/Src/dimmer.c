/*
 * dimmer.c
 *
 * Description: Dimmers the RED background LEDS by setting the pulse value of timer from of the analog potentiometer input.
 *  Created on: Dec 12, 2019
 *      Author: samfl
 *
 */

#include "dimmer.h"

/**
 * To initialize interrupt for the potentiometer.
 * Analog To Digital conversion starts when the interrupt method is used.
 */
void Init_potentiometer(void) {
  HAL_ADC_Start_IT(&hadc1);
}

/**
 * Callback function ran on interrupt.
 * Indicates the end of the current process or when a DMA transfer has completed.
 */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
  if(hadc->Instance == ADC1) {
    Set_backlight_dimmer(HAL_ADC_GetValue(&hadc1)); /** Retrieve conversion result and pass it down */
  }
}

/**
 * Set the dimmer values
 * Called from the interrupt callback function
 */
void Set_backlight_dimmer(uint32_t pulse_value) {
  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2); /** Starts the Pulse Width Modulation signal generation */
  TIM_OC_InitTypeDef sConfigOC; /** Reference to the oscillator */
  sConfigOC.OCMode = TIM_OCMODE_PWM1; /** */
  sConfigOC.Pulse = pulse_value; /** Pulse set by the potentiometer */
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH; /** */
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE; /** */
  HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2); /** Initializes the TIM PWM channels with (1, 2, 3) */
}


