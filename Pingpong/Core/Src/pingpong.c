/**
******************************************************************************
@brief Pingpong, state machine for Pingpong-program
@file pingpong_functions.c
@author Sam Florin
@version 1.0
@date 08-November-2019
@brief Structure/state machine for pipong program.
******************************************************************************
*/
#include <stdint.h>
#include <stdbool.h>
#include <pingpong_functions.h>
#include <pingpong.h>
#include <gpio.h>

typedef enum
{ Start,
MoveRight,
MoveLeft,
Duel
} states;

static states State, NextState;

void Pingpong(void) {
	bool ButtonPressed = false;
	bool PlayerLeftServe, PlayerRightServe; // To remember that button is pressed
	uint32_t Varv, Speed; // Ball speed
	uint8_t Led; // LED nr
	uint8_t PlayerLeftScore, PlayerRightScore = 0;

	State= Start; // Initiate State to Start
	NextState= Start;
	Speed= 500000; // Number of loops

	/* Infinite loop */
	while (1) {
		State = NextState;

		switch (State) { // State machine
			case Start:
				Speed= 500000;
				PlayerRightServe = 0;
				PlayerLeftServe = 0;
				Led_on(0); // Turn off all LEDs
				if ( L_hit() == true ) { // L serve
					PlayerLeftServe = 1;
					Led = 1;
					NextState= MoveRight;
					while ( L_hit() == true ); // wait until button is released
				} else if ( R_hit() == true ) { // R serve
					PlayerRightServe = 1;
					Led = 8;
					NextState= MoveLeft;
					while ( R_hit() == true );
				} else // wait until button is released
					NextState = Start; // Stay in Start state
			break;

			case MoveRight: {
				Led_on(Led);
				Varv = Speed;
				while( Varv != 0 ) {
					if ( R_hit() ) ButtonPressed = true; // R hit
					Varv--;
				}
				if ( ButtonPressed ) { // R pressed
					if ( Led == 8 ) { // and LED8 activated
						NextState=MoveLeft; // return ball
						Led=7;
						Speed -= 50000;
					}	else {
							Duel_over(1);
							PlayerLeftScore++;
							NextState = Duel; // hit to early
					}

				}	else {
						if ( Led == 9 ) {
							Duel_over(1);
							PlayerLeftScore++;
							NextState = Duel;
						} else
							NextState = MoveRight; // ball continues to move right
					}
				if ( !ButtonPressed ) Led++; // prepare to turn next LED on
					ButtonPressed=false;
			}
			break;

			case MoveLeft: {
				Led_on(Led);
				Varv = Speed;
				while(Varv != 0) {
					if ( L_hit() ) ButtonPressed = true; // L hit
					Varv--;
				}
				if ( ButtonPressed ) { // L pressed
					if ( Led == 1 ) { // and LED1 active
						NextState=MoveRight; // return ball
						Led=2;
						Speed -= 50000;
					} else {
						Duel_over(2);
						PlayerRightScore++;
						NextState = Duel; // hit to early
					}
				} else {
					if ( Led == 0 )  { // no hit or to late
						Duel_over(2);
						PlayerRightScore++;
						NextState = Duel;
					} else
						NextState = MoveLeft; // ball continues to move left
				}
				if ( !ButtonPressed ) Led--; // prepare to turn next LED on
					ButtonPressed=false;
			}
			break;

			case Duel: {
				Show_points(PlayerLeftScore, PlayerRightScore);
				if((PlayerLeftScore== 3) || (PlayerRightScore== 3)) {
					PlayerLeftScore = 0;
					PlayerRightScore = 0;
					HAL_Delay(2000);
					NextState = Start;
				} else {
					Speed= 500000;
					Led_on(0); // Turn off all LEDs
					if ( (L_hit() && PlayerLeftServe) == true ) { // L serve
						PlayerLeftServe = 0;
						PlayerRightServe = 1;
						Led = 1;
						NextState= MoveRight;
						while ( L_hit() == true ); // wait until button is released
					} else if ( (R_hit() && PlayerRightServe) == true ) { // R serve
						PlayerLeftServe = 1;
						PlayerRightServe = 0;
						Led = 8;
						NextState= MoveLeft;
						while ( R_hit() == true );
					} else // wait until button is released
						NextState = Duel; // Stay in Start state
				}
			}
			break;

			default:
			break;
		}
	}
}
