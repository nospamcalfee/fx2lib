#ifndef _FXINTJT_H_
#define _FXINTJT_H_

#include "ezregs.h"

// this causes usbjt to be included from the lib
// not used for anything
extern u8_t INT2JT;
/*
 * Hardware fixed interrupts
 */
#pragma save
#pragma nooverlay

void int0_isr(void) 	interrupt 0;
void timer0_isr(void) 	interrupt 1;
void int1_isr(void) 	interrupt 2;
void timer1_isr(void) 	interrupt 3;
void ser0_isr(void) 	interrupt 4;
void timer2_isr(void) 	interrupt 5;
void resume_isr(void) 	interrupt 6;
void ser1_isr(void) 	interrupt 7;

/*
 * defined in fwJumptable.asm, see autovector in EZUSB spec
 * */
extern void usb_isr(void) interrupt 8;

void i2c_isr(void) 	interrupt 9;
void int4_isr(void) 	interrupt 10;
void int5_isr(void) 	interrupt 11;
void int6_isr(void) 	interrupt 12;

/*
 *	usb interrupts, must be page aligned somewhere
 */
void usb_sudav_isr(void)interrupt;
void usb_sof_isr(void) interrupt;
void usb_sutok_isr(void) interrupt;
void usb_suspend_isr(void) interrupt;
void usb_usbreset_isr(void) interrupt;
void usb_reserved_isr(void) interrupt;
void usb_ep0in_isr(void) interrupt;
void usb_ep0out_isr(void) interrupt;
void usb_ep1in_isr(void) interrupt;
void usb_ep1out_isr(void) interrupt;
void usb_ep2in_isr(void) interrupt;
void usb_ep2out_isr(void) interrupt;
void usb_ep3in_isr(void) interrupt;
void usb_ep3out_isr(void) interrupt;
void usb_ep4in_isr(void) interrupt;
void usb_ep4out_isr(void) interrupt;
void usb_ep5in_isr(void) interrupt;
void usb_ep5out_isr(void) interrupt;
void usb_ep6in_isr(void) interrupt;
void usb_ep6out_isr(void) interrupt;
void usb_ep7in_isr(void) interrupt;
void usb_ep7out_isr(void) interrupt;

#pragma restore

#endif /* _FXINTJT_H_ */
