/*
 * process.h
 *
 *  Created on: Dec 13, 2019
 *      Author: samfl
 */

#ifndef INC_PROCESS_H_
#define INC_PROCESS_H_
#endif /* INC_PROCESS_H_ */

#include <display.h>
#include <rtc.h>
#include <dimmer.h>

void Set_up(void);
void Send_rtc_to_usb(void);
void Send_rtc_to_display(void);
void Start_clock(void);
