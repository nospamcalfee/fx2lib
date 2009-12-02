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

 /*
  * Minimal sample to flash the LED on the keyspan USA19
  */

#include <ezregs.h>

/*
 * USA 19 unique port A led bit
 */
#define bmMYLED 0x20

void delay1ms(void)
{
   /*
    * 24MHz clock => 166.6ns/cycle
    *
    * 10 cycles in a loop, 602 loops in a millisecond
    */
   _asm
      mov  dptr,#(0xffff - 602);
   loop:
      inc  dptr   ; 3 cycles
      mov  a,dpl  ; 2 cycles
      orl  a,dph  ; 2 cycles
      jnz  loop   ; 3 cycles
   _endasm;
}
void mdelay(u16_t ms)
{
   u16_t i;
   
   for(i=0; i < ms; i++) {
      delay1ms();
   }
}

void main(void)
{

    	// loop endlessly
    	for(;;) {
    		OUTA &= ~bmMYLED;
       		mdelay(500);
       		OUTA |= bmMYLED;
       		mdelay(50);
    	}
}
