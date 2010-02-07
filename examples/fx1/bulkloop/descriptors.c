/*
 * Copyright (C) 2009 Steve Calfee
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */
#include <ezregs.h>
#include <chapter9.h>
#include <stdint.h>
#include "fx1setup.h"

#define VID 0xB404
#define PID 0x0410

const u8_t devicedescriptor[] = {
	sizeof(struct usb_device_descriptor),	/* bLength */
	UDESC_DEVICE, 				/* bDescriptorType */
	0x10, 0x01, 				/* bcdUSB */
	UDCLASS_VENDOR, 			/* bDeviceClass */
	UDCLASS_VENDOR, 			/* bDeviceSubClass */
	UDCLASS_VENDOR, 			/* bDeviceProtocol */
	64, 					/* bMaxPacketSize0 */
	LSB(VID),
	MSB(VID), 				/* idVendor */
	LSB(PID),
	MSB(PID), 				/* idProduct */
	0x01, 0x00, 				/* bcdDevice */
	0x01, 					/* iManufacturer */
	0x02, 					/* iProduct */
	0x00, 					/* iSerialNumber */
	0x01 					/* bNumConfigurations */
};

const u8_t configdescriptor[] = {
	sizeof(struct usb_config_descriptor),	/* bLength */
	UDESC_CONFIG,				/* bDescriptorType */
	LSB(sizeof(configdescriptor)),		/* wTotalLength L */
	MSB(sizeof(configdescriptor)), 		/* wTotalLength H */
	0x01, /* bNumInterfaces */
	0x01, /* bConfigurationValue */
	0x00, /* iConfiguration */
	0x80, /* bmAttributs */
	0x32, /* MaxPower */
	/* 
	 * interface descriptor 
	 */
	sizeof(struct usb_interface_descriptor),	/* bLength */
	UDESC_INTERFACE, 				/* bDescriptorType */
	0x00, /* bInterfaceNumber */
	0x00, /* bAlternateSetting */
	0x02, /* bNumEndpoints */
	UDCLASS_VENDOR, /* bInterfaceClass */
	UDCLASS_VENDOR, /* bInterfaceSubClass */
	UDCLASS_VENDOR, /* bInterfaceProtocol */
	0x00, /* iInterface */
	/* 
	 * endpoint descriptor 
	 */
	sizeof(struct usb_endpoint_descriptor), /* bLength */
	UDESC_ENDPOINT,			/* bDescriptorType */
	UE_DIR_OUT|0x02, 		/* bEndpointAddress */
	UE_BULK, 			/* bmAttributes */
	LSB(MAX_PACKET_BULK_FS),
	MSB(MAX_PACKET_BULK_FS), 	/* wMaxPacketSize */
	0x00, 				/* bInterval */
	/* 
	 * endpoint descriptor 
	 */
	sizeof(struct usb_endpoint_descriptor),	/* bLength */
	UDESC_ENDPOINT, 			/* bDescriptorType */
	UE_DIR_IN|0x02, 		/* bEndpointAddress */
	UE_BULK, 			/* bmAttributes */
	LSB(MAX_PACKET_BULK_FS),
	MSB(MAX_PACKET_BULK_FS), 	/* wMaxPacketSize */
	0x00, 				/* bInterval */
};

USB_MAKE_STRING_DESC(StringDscr0, 0x409 );
USB_MAKE_STRING_DESC(StringDscr1, 'C','a','l','f','e','e' );
USB_MAKE_STRING_DESC(StringDscr3, 'P', 'r', 'o', 'd', '3', );

const void * const strings[NUMBER_OF_LANGUAGES][NUMBER_OF_STRINGS] = {
   { &StringDscr0, &StringDscr1, &StringDscr3, },
};
