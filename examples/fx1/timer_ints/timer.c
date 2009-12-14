/**
 * Copyright (C) 2009 Steve Calfee
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 **/
#include <ezregs.h>
#include <chapter9.h>
/*
 * USA 19 unique port A led bit
 */
#define bmMYLED 0x20

static volatile u16_t overflow_count = 0;

void main() {
	struct usb_device_request *setup = 
					(struct usb_device_request *)SETUPDAT;
	/*
	 * Init everything for the i/o to come.
	 * timer = 24Mhz/12 = 2Mhz then divided by 65536 = 30.517578125 per sec
	 * which is every 0.032768 seconds
	 */
#if 1
	SCON0 = 0;	/* disable serial ports */
	SCON1 = 0;	/* disable serial ports */
	TMOD =  T0M0 | T1M0;	/* 6 bit timer0, timer1 */
	CKCON = 0;	/* clock timers at 24Mhz/12  */
	TCON = 0;
	TL0 = 0;	/* explicitly set to 65536 */
	TH0 = 0;	/* explicitly set to 65536 */
	TR0 = 1;	/* start the timer */
	TL1 = 0;	/* explicitly set to 65536 */
	TH1 = 0;	/* explicitly set to 65536 */
	TR1 = 1;
	IE  = 0;	/* all ints disabled individually */
	EIE = 0;	/* all ints disabled individually */
	ET0 = 1;	/* enable timer0 ints  */
	//ET1 = 1;	/* enable timer1 ints */
	EA  = 1;	/* global int enable */
#endif
	while(TRUE) {
		if (overflow_count & 0x0e) {
	    		OUTA &= ~bmMYLED;
       		} else {
	       		OUTA |= bmMYLED;
       		}
  	}
}

/* 
 * timer0_isr --
 *      The timer interrupt.  Gets called according to the timer
 *      registers initalized 
 */
void timer0_isr(void) interrupt (1)
{
	overflow_count++;   	/* Increment the overflow count */
}

void timer1_isr(void) interrupt (3)
{
}
