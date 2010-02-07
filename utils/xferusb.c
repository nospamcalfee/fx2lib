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
 
/* cc -Wall -g -o xferusb xferusb.c */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/ioctl.h>
#include "../include/chapter9.h"
#include <linux/usbdevice_fs.h>

/*
 * open and claim a usb device via usbdevfs
 * called with config#,int#, alt#
 * returns fd for further io, -1 on failure
 */
int open_claim(char *device,
		unsigned char confignumber,
		unsigned char interfaceindex,
		unsigned char interfacealt)
{
	int fd;
	struct usbdevfs_ioctl disconnect = { 0 };
	struct usbdevfs_setinterface interface = { 0 };
	unsigned int myconfig = (unsigned int) confignumber;

	if ((fd = open(device, O_RDWR)) < 0) {
		perror ("can't open dev file r/w");
		return -1;
	}
	/*
	 * Disconnect any existing interface.  Ignore failure.
	 */
	 
	disconnect.ifno = interfaceindex;
	disconnect.ioctl_code = USBDEVFS_DISCONNECT;
	ioctl(fd, USBDEVFS_IOCTL, &disconnect);

	/*
	 * Set in the desired configuration number
	 */
	 
	if (ioctl(fd, USBDEVFS_SETCONFIGURATION, &myconfig) != 0) {
	   fprintf(stderr, "error(%d): ioctl USBDEVFS_SETCONFIGURATION=%d %s\n", 
	                    errno, confignumber, strerror(errno));
	   return -1;
	}
    
	/*
	 * Claim Interface.
	 */

	interface.interface = interfaceindex;
	interface.altsetting = interfacealt;

	if (ioctl(fd, USBDEVFS_CLAIMINTERFACE, &interface.interface) != 0) {
	   fprintf(stderr, "error(%d): ioctl claim interface=%d alt=%d, %s\n", 
	                    errno,interfaceindex, interfacealt, strerror(errno));
	   return -1;
	}

	/*
	 * Set Interface.
	 */

	if (ioctl(fd, USBDEVFS_SETINTERFACE, &interface) < 0) {
	   fprintf(stderr, "ioctl set interface, %s\n", strerror(errno));
	   return -1;
	}

	return fd;
}

int main (int argc, char **argv)
{
	int	c, i;
	int	iterations = 1;
	int	verbosity = 0;
	int	inEP = -1, outEP = -1;
	char	*device;
	int	length;
	int				fd;
	struct usb_device_descriptor	dev;
	struct usbdevfs_bulktransfer	bulkin, bulkout;
	unsigned char	inbuf[64];
	char	outbuf[] = "Hi out there";

	while ((c = getopt (argc, argv, "D:c:s:i:o:v")) != EOF)
	switch (c) {
	case 'D':	/* device, if only one */
		device = optarg;
		continue;
	case 'v':	/* increase verbosity */
		verbosity++;
		continue;
	case 'c':	/* count iterations */
		iterations = atoi (optarg);
		if (iterations < 0)
			goto usage;
		continue;
	case 's':	/* size of packet */
		length = atoi (optarg);
		if (length < 0)
			goto usage;
		continue;
	case 'i' :
		inEP = atoi (optarg);
		if (inEP == 0) goto usage;
		continue;
	case 'o' :
		outEP = atoi (optarg);
		if (outEP == 0) goto usage;
		continue;
	case '?':
	case 'h':
	default:
usage:
		fprintf (stderr, "usage: %s [-D dev]"
			"\t[-c iterations] \t[-s packetsize]\n"
			"\t[-v] (increase verbosity)"
			"\t[-i inEP_decimal] [-o outEP_decimal]\n", 
			argv [0]);
		return 1;
	}
	if (optind != argc)
		goto usage;
	if (!device) {
		fprintf (stderr, "must specify '-D dev'\n");
		goto usage;
	}
	if (inEP < 0 && outEP < 0) {
		fprintf (stderr, "must specify at least one endpoint\n");
		goto usage;
	}

	printf("opening %s inEP=%d=0x%x outEP=%d=0x%x\n", 
			device, inEP, inEP, outEP, outEP);
	/* Open the device for i/o config 0, int 0, alt 0 */
	if ((fd = open_claim(device, 1, 0, 0)) < 0) {
		perror ("can't open dev file");
		return 0;
	}
	if (read (fd, &dev, sizeof dev) != sizeof dev)
		fputs ("short devfile read!\n", stderr);

	printf("idVendor=%4x idProduct=%4x\n",dev.idVendor, dev.idProduct);

	for (i = 0; i < iterations; i++) {
		int ret;
		bulkin.ep = inEP;
		bulkin.len = sizeof(inbuf);
		bulkin.timeout = 1000; /* 1 second */
		bulkin.data = inbuf;
		bulkout.ep = outEP;
		bulkout.len = sizeof(outbuf);
		bulkout.timeout = 1000; /* 1 second */
		bulkout.data = outbuf;

		if (outEP > 0 && 
		(ret = ioctl(fd, USBDEVFS_BULK, &bulkout)) < 0) {
			printf("OUT ioctl error=%d %s\n", errno, strerror(errno));
		}
		if (verbosity) printf("wrote %d bytes\n", ret);
		
		if (inEP > 0 && 
		(ret = ioctl(fd, USBDEVFS_BULK, &bulkin)) < 0) {
			printf("IN ioctl error=%d %s\n", errno, strerror(errno));
		}
		if (verbosity) printf("read %d bytes frame=%u cnt=%u str=%s\n", 
			ret, inbuf[0] + (inbuf[1] << 8), inbuf[2], &inbuf[3]);
	}
	return 0;
}
