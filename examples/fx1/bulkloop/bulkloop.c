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
#include "fx1setup.h"
#include <fx1intjt.h>
/*
 * USA 19 unique port A led bit
 */
#define bmMYLED 0x20

static volatile u16_t overflow_count = 0;

void main() {
	struct usb_device_request *setup = 
					(struct usb_device_request *)SETUPDAT;
	u16_t delay_count;
	/*
	 * Init everything for the i/o to come.
	 * timer = 24Mhz/12 = 2Mhz then divided by 65536 = 30.517578125 per sec
	 * which is every 0.032768 seconds
	 */
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
	//ET0 = 1;	/* enable timer0 ints  */
	ET1 = 1;	/* enable timer1 ints */
	EA  = 1;	/* global int enable */
	/* enable autovector, disable breakpoint logic */
	USBBAV = D0;

	delay_count = overflow_count;	/*freeze current timer */
	/*
	 * Init usb for transfers
	 */
	/* disconnect from USB */
	USBCS = DISCON | RENUM;
	/* wait for 1.5s  elapsed timer > desired wait time */
	//OUTA |= bmMYLED;	/* led on */
	OUTA &= ~bmMYLED;
	while (overflow_count - delay_count < 30*3) {}
	//OUTA |= bmMYLED;
	//OUTA &= ~bmMYLED;	/* led off */

	/* reconnect and renumerate USB */
	USBCS = DISCOE | RENUM;


	ep0_setup_buffer_rdy = 0;
	
	/* Turn on interrupts for all endpoints we're going to use. */
	OUT07IEN = OUT0IR | OUT2IR;
	IN07IEN  =  IN0IR |  IN2IR;

	/* Set the proper endpoint valid bits. */
	OUT07VAL = OUT0VAL | OUT2VAL;
	IN07VAL  =  IN0VAL |  IN2VAL;

	/*
	 * Enable double buffering for EP2. 
	 */
	USBPAIR |= PR2IN;
	USBPAIR |= PR2OUT;

	/*
	 * Configure isocronous endpoints, and interrupts.
	 */
	ISOCTL = ISODISAB; /* disable all iso */
	INISOVAL = 0;
	OUTISOVAL = 0;

	/*
	 * use a pair of 512 byte FIFOS for endpoint 8, see EZUSB Spec Chapter 8.4
	 */
	OUT8ADDR = 0x00;
	IN8ADDR = 0x00;

	//USBPAIR |= ISOSEND0;

	/* enable setup packet interrupt */
	USBIEN = SUDAVIE;

	/* enable USB interrupt */
	EUSB = 1;

	while(TRUE) {
 
		handle_setupdata();
#if 1
		if (overflow_count & 0x1c) {
			OUTA &= ~bmMYLED;
		} else {
			OUTA |= bmMYLED;
		}
#endif
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
	TF0 = 0;		/* clear interrupt */
}

void timer1_isr(void) interrupt (3)
{
	/* clear interrupt */
	overflow_count++;   /* Increment the overflow count */
   	TF1 = 0;
}
