/*
 * pingpong_functions.h
 *
 *  Created on: Nov 6, 2019
 *      Author: samfl
 */

#ifndef INC_PINGPONG_FUNCTIONS_H_
#define INC_PINGPONG_FUNCTIONS_H_
#endif /* INC_PINGPONG_FUNCTIONS_H_ */

void Led_on(uint8_t Lednr);
void Set_led(uint8_t Lednr);
void Reset_led(uint8_t Lednr);
void Set_leds(void);
void Reset_leds(void);
void Game_indication(void);
void Duel_over(uint8_t player);
void Show_points(uint8_t L_points ,uint8_t R_points);
bool L_hit(void);
bool R_hit(void);
