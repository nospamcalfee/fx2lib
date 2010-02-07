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
 */
#ifndef _FX1SETUP_H_
#define _FX1SETUP_H_

void handle_setupdata();

extern const u8_t devicedescriptor[];
extern const u8_t configdescriptor[];
/*
 * Bits indicating a USB bus transfer has happened
 */
extern bit ep0_setup_buffer_rdy;
extern bit ep1_in_buffer_rdy;
extern bit ep0_out_buffer_rdy;
extern bit ep0_in_buffer_rdy;
/*
 * user app supplied routines
 */
u8_t handle_vendorcommand();
u8_t handle_set_interface(u8_t IFnumber, u8_t ALTnumber);
/*
 * Define some makefile overrideable constants
 */
 
#ifndef NUMBER_OF_STRINGS
#define NUMBER_OF_STRINGS 3
#endif
#ifndef NUMBER_OF_LANGUAGES
#define NUMBER_OF_LANGUAGES 1
#endif

#ifndef NUMBER_OF_CONFIGS
#define NUMBER_OF_CONFIGS 1
#endif

extern const void * const strings[NUMBER_OF_LANGUAGES][NUMBER_OF_STRINGS];

#endif
