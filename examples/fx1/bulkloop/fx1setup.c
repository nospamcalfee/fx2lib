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
 
#include <ezregs.h>
#include <chapter9.h>
#include "fx1setup.h"

/*
 * configuration set by host.
 * 0=address state, else selected configuration
 */
unsigned char configSetting; 
unsigned char altSetting;
bit ep0_setup_buffer_rdy;

u8_t handle_vendorcommand() 
{
		return SUCCESS;
}
u8_t handle_set_interface(u8_t IFnumber, u8_t ALTnumber) 
{
	(void) IFnumber;
	(void) ALTnumber;
	return SUCCESS;
}

/*
 *----------------------------------------------------------------------
 *
 * handle_setupdata --
 *      Must be called frequently by the mainloop. If a setup packet
 *      was received by the isr, this routine will handle it and
 *      handle the status stage of the control packet protocol
 *
 *----------------------------------------------------------------------
 */

void 
handle_setupdata()
{
	xdata struct usb_device_request *setup = 
				(xdata struct usb_device_request *) &SETUPDAT;
	
	if (!ep0_setup_buffer_rdy) {
		return;
	}

	ep0_setup_buffer_rdy = 0;

	switch (setup->bRequest) {

	case UR_GET_DESCRIPTOR:

		switch(MSB(setup->wValue)) {

		case UDESC_DEVICE:
		{
			SUDPTRH = MSB(&devicedescriptor);
			SUDPTRL = LSB(&devicedescriptor);
		}
		break;

		case UDESC_CONFIG:
		{
			SUDPTRH = MSB(&configdescriptor);
			SUDPTRL = LSB(&configdescriptor);
		}
		break;

		case UDESC_STRING:
		{
			unsigned char strNumber = LSB(setup->wValue);
			unsigned char langNumber = 0;
			if (strNumber) {

				/*
				 * To return a string, find its langID offset 
				 * in string 0.
				 * Then use that index into my strings array 
				 * to find the actual string.
				 */
				 
				unsigned char i;
				struct usb_string_descriptor *stringIDs = 
				(struct usb_string_descriptor *) strings[0][0];

				for (i = 1; i < stringIDs->bLength / 2; i++) {
					if (setup->wIndex == 
						stringIDs->bString[i - 1]) {
					   break;
					}
					langNumber++;
				}   
				if (strNumber > NUMBER_OF_STRINGS - 1 ||
				langNumber > NUMBER_OF_LANGUAGES - 1 ||
				strings[langNumber][strNumber] == NULL) {
					goto stallexit;
				}
			}
			SUDPTRH = MSB(strings[langNumber][strNumber]);
			SUDPTRL = LSB(strings[langNumber][strNumber]);
		      
		break;
		}

		default:

		/* 
		 * Set stall... unexpected problem.
		 */
stallexit:             
			EP0CS = EP0STALL | CLRHSNAK;
			return;
		}
	break;

	case UR_GET_INTERFACE:

		/*
		 * Get alternate setting for an interface. 
		 */
		 
		OUT0BUF[0] = altSetting;
		OUT0BC = 1;
	break;

	case UR_SET_INTERFACE:

		/* 
		 * Change alternate settings for an interface.
		 */
		 
		altSetting = LSB(setup->wValue);

		if (handle_set_interface(setup->wIndex, altSetting)) {
			goto stallexit;
		}

	break;
	   
	case UR_SET_CONFIG:

		/* 
		 * Select configuration. Maybe High power and lower power modes.
		 * Enable default interface and alt.
		 */
		 
		configSetting = LSB(setup->wValue);

		if (handle_set_interface(0, 1)) {
			goto stallexit;
		}
	break;

	case UR_GET_CONFIG:

		/*
		 * Return the current config number.  
		 */
		OUT0BUF[0] = configSetting;
		OUT0BC = 1;
	break;

	case UR_GET_STATUS:   
      
		/*
		 * decode setup Type
		 */
		 
		switch(SETUPDAT[0]) {

		case UT_READ_DEVICE:
			OUT0BUF[0] = 0; // Not self-powered, No remote wakeup
			OUT0BUF[1] = 0;
			OUT0BC = 2;
		break;

		case UT_READ_ENDPOINT:

			/*
			 * Return endpoint stalled state
			 */
			 
			OUT0BUF[0] = EPIO[SETUPDAT[4]].cntrl & INCS_STALL;
			OUT0BUF[1] = 0;
			OUT0BC = 2;
		break;

		case UT_READ_INTERFACE:
			OUT0BUF[0] = 0; // Always return zeros
			OUT0BUF[1] = 0;
			OUT0BC = 2;
		break;

		}
	break;

	case UR_SET_FEATURE:

		 /* 
		  * Only ep stall is supported
		  */

		 if (LSB(setup->wValue) != UF_ENDPOINT_HALT) {
			goto stallexit;
		 }
		 EPIO[LSB(setup->wIndex)].cntrl |= INCS_STALL;

	break;

	case UR_CLEAR_FEATURE:

		/* 
		 * Only ep stall is supported
		 */

		if (LSB(setup->wValue) != UF_ENDPOINT_HALT) {
			goto stallexit;
		}
		EPIO[(LSB(setup->wIndex))].cntrl &= ~INCS_STALL;

	break;
	   
	/*
	 * Here if an unknown request. Try to decode it as a vendor request
	 */
	  
	default:
	{
		unsigned char result = handle_vendorcommand();
		if (result==FAILURE) {
		   
			/*
			 * unknown vendor request, stall it.
			 */
			 
			EP0CS = EP0STALL;
			return;
		}
		if (result==LETMAINHANDLEIT) {
		   
			/*
			 * wait for mainline to ack next coming data packet
			 */
			 
			goto exitWithoutHSNAK;
		}
	}
	break;
	}

      /* 
       * Acknowledge handshake phase of device request with HSNAK
       */ 
       
      EP0CS = CLRHSNAK;
      
      /* 
       * This IS in the mainline, but now I need other routines to analyze the 
       * data, so the hardware should be left naking the control packet until 
       * the mainline processing and I/O are done.
       */
       
exitWithoutHSNAK:
}


