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

/*
 * The rest of this file contains stubs for interrupts we don't use.
 *
 * usb_sudav_isr --
 *      This interrupt is triggered when a setup packet arrives on the
 *      control endpoint.  
 */
void
usb_sudav_isr(void) interrupt
{

   /*
    * Clear interrupt
    */
   EXIF &= ~USBINT;
   USBIRQ = SUDAVIR; /* enable SUDAV interrupt */
}


/*
 * usb_ep0out_isr --
 *      This interrupt gets triggered after the data phase of a setup
 *      transfer.
 */
void
usb_ep0out_isr(void) interrupt
{
   /* clear USB interrupt */
   EXIF &= ~USBINT;
   OUT07IRQ = OUT0IR;
}


/*
 * usb_sof_isr --
 *      This interrupt occurs once for every USB start of frame.
 */
void
usb_sof_isr(void) interrupt
{
   /* clear interrupt */
   EXIF &= ~USBINT;
   USBIRQ = SOFIR;
}


/*
 * The stubs clear their respective interrupt and return.  Most of this
 * code is never executed because the interrupts don't get enabled.
 */


void
int0_isr(void) interrupt 0
{
   /* clear interrupt */
   IE0 = 0;
}


void
int1_isr(void) interrupt 2
{
   /* clear interrupt */
   IE1 = 0;
}


void
ser0_isr(void) interrupt 4
{
   /* clear interrupt */
   RI	= 0;
   TI	= 0;
}


void
timer2_isr(void) interrupt 5
{
   /* clear interrupt */
   TF2 = 0;
}


void
resume_isr(void) interrupt 6
{
   /* clear interrupt */
   RESI = 0;

}


void
ser1_isr(void) interrupt 7
{
   /* clear interrupt */
   RI1 = 0;
   TI1 = 0;
}


void
i2c_isr(void) interrupt 9
{
   /* clear interrupt */
   EXIF &= ~I2CINT;
}


void
int4_isr(void) interrupt 10
{
   /* clear interrupt */
   EXIF &= ~IE4;
}


void
int5_isr(void) interrupt 11
{
   /* clear interrupt */
   EXIF &= ~IE5;
}


void
int6_isr(void) interrupt 12
{
   /* clear interrupt */
   INT6 = 0;
}



void
usb_sutok_isr(void) interrupt
{
   /* clear interrupt */
   EXIF &= ~USBINT;
   USBIRQ = SUTOKIR;
}


void
usb_suspend_isr(void) interrupt
{
   /* clear interrupt */
   EXIF &= ~USBINT;
   USBIRQ = SUSPIR;
}


void
usb_usbreset_isr(void) interrupt
{
   /* clear interrupt */
   EXIF &= ~USBINT;
   USBIRQ = URESIR;
}


/* included for completeness */
void
usb_reserved_isr(void) interrupt
{}


void
usb_ep0in_isr(void) interrupt
{
   /* clear interrupt */
   EXIF &= ~USBINT;
   IN07IRQ = IN0IR;

}


void
usb_ep1in_isr(void) interrupt
{
   /* clear interrupt */
   EXIF &= ~USBINT;
   IN07IRQ = IN1IR;
}


void
usb_ep1out_isr(void) interrupt
{
   /* clear interrupt */
   EXIF &= ~USBINT;
   OUT07IRQ = OUT1IR;
}


void
usb_ep2in_isr(void) interrupt
{
   /* clear interrupt */
   EXIF &= ~USBINT;
   IN07IRQ = IN2IR;
}


void
usb_ep2out_isr(void) interrupt
{
   /* clear interrupt */
   EXIF &= ~USBINT;
   OUT07IRQ = OUT2IR;
}

void
usb_ep3in_isr(void) interrupt
{
   /* clear interrupt */
   EXIF &= ~USBINT;
   IN07IRQ = IN3IR;
}


void
usb_ep3out_isr(void) interrupt
{
   /* clear interrupt */
   EXIF &= ~USBINT;
   OUT07IRQ = OUT3IR;
}


void
usb_ep4in_isr(void) interrupt
{
   /* clear interrupt */
   EXIF &= ~USBINT;
   IN07IRQ = IN4IR;
}


void
usb_ep4out_isr(void) interrupt
{
   /* clear interrupt */
   EXIF &= ~USBINT;
   OUT07IRQ = OUT4IR;
}


void
usb_ep5in_isr(void) interrupt
{
   /* clear interrupt */
   EXIF &= ~USBINT;
   IN07IRQ = IN5IR;
}


void
usb_ep5out_isr(void) interrupt
{
   /* clear interrupt */
   EXIF &= ~USBINT;
   OUT07IRQ = OUT5IR;
}


void
usb_ep6in_isr(void) interrupt
{
   /* clear interrupt */
   EXIF &= ~USBINT;
   IN07IRQ = IN6IR;
}


void
usb_ep6out_isr(void) interrupt
{
   /* clear interrupt */
   EXIF &= ~USBINT;
   OUT07IRQ = OUT6IR;
}


void
usb_ep7in_isr(void) interrupt
{
   /* clear interrupt */
   EXIF &= ~USBINT;
   IN07IRQ = IN7IR;
}


void
usb_ep7out_isr(void) interrupt
{
   /* clear interrupt */
   EXIF &= ~USBINT;
   OUT07IRQ = OUT7IR;
}

