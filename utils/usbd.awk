#!/usr/bin/gawk -f
# usbd.awk version 1.1
# Copyright: 2009 Steve Calfee
#
# This software may be used and distributed according to the terms of
# the GNU General Public License (GPL), version 2, or at your option
# any later version.
# 
# called as usbd.awk
BEGIN {
	USB_DT_DEVICE = 1
	USB_DT_CONFIG = 2
	USB_DT_STRING = 3
	USB_DT_INTERFACE = 4
	USB_DT_ENDPOINT = 5
	USB_DT_DEVICE_QUALIFIER = 6
	USB_DT_OTHER_SPEED_CONFIG = 7
	USB_DT_INTERFACE_ASSOCIATION = 11
	o_bLength = 0
	o_bDescriptorType = 1
	o_bConfigurationValue = 5
	buses = "/sys/bus/usb/devices/usb*"
	FN = nbus = 1;
	class["00"] = ">ifc "
	class["01"] = "audio"
	class["02"] = "commc"
	class["03"] = "HID  "
	class["05"] = "phys "
	class["06"] = "image"
	class["07"] = "print"
	class["08"] = "mstor"
	class["09"] = "hub  "
	class["0a"] = "comdt"
	class["0b"] = "smcrd"
	class["0d"] = "cosec"
	class["0e"] = "video"
	class["0f"] = "perhc"
	class["dc"] = "diagd"
	class["e0"] = "wlcon"
	class["ef"] = "misc "
	class["fe"] = "app. "
	class["ff"] = "vend."
	ep_type[0] = "ctrl"
	ep_type[1] = "Isoc"
	ep_type[2] = "Bulk"
	ep_type[3] = "Int."
	while ((("ls -d1 " buses) | getline temp) > 0) {
		bus[nbus] = temp "/";
		ARGV[nbus++]  = temp "/busnum";
		ARGC++;
		#print nbus - 1, ARGV[nbus - 1]
	}
	if (ARGC < 2) exit 1
	close("ls -d1 " buses)
}
function getdir(dir,	ndirs, temp) {
	ndirs = 0
	while ((("ls -d1 " dir) | getline temp) > 0) {
		dirs[ndirs] = temp "/";
		#print "getdir ", ndirs, dirs[ndirs]
		ndirs++
	}
	close("ls -d1 " dir)
	return ndirs
}
function f(path, t) {
	getline t < path
	close(path)
	return t
}
function class_decode(cls) {
	if (cls in class) {
		return class[cls]
	} else {
		return "unk"
	}
}
function print_string(file, name,	t) {
	t = f(file)
	if (t) printf("S:  %s=%s\n", name, t) 
}
function le_word(a, b) {
	return a + (b * 256)	
}
function scan_desc(d, i, nd, srch) {
	while (i < nd) {
		if (d[i + o_bDescriptorType] == srch) {
			#print "scan_desc found " i, d[i], d[i+1]
			return i
		} else {
			#print "scan_desc hunt " i, d[i], d[i+1]
			i += d[i + o_bLength]
		}
	}
	return 0; #not found exit
}
#return index of first int descriptor matching nif in config ncf, else 0 fail
function find_int(desc, ncf,	d, nd, i) {
	nd = split(desc, d)
	i = 2
	while (i < nd) {
		i = scan_desc(d, i, nd, USB_DT_CONFIG)
		if (!i) return 0
		if (d[i + o_bConfigurationValue] == ncf) {
			#print desc
			#print "found config #" d[i+o_bConfigurationValue] " length " le_word(d[i+2], d[i+3])
			i = scan_desc(d, i + d[i + o_bLength], nd, USB_DT_INTERFACE)
			return i
		} else {
			#print "not found config #" d[i+o_bConfigurationValue] " length " le_word(d[i+2], d[i+3])
			i += le_word(d[i+2], d[i+3])
		}
	}
	return 0
}
function print_assoc_def(d, i) {
	if (i) {
		FirstIf = d[i + 2]
		IfCount = d[i + 3]
		printf("A:  FirstIf#=%2i IfCount=%2i Cls=%s(%s) Sub=%02i Prot=%02i\n",
			FirstIf, IfCount, sprintf("%02x",d[i + 4]), 
			class_decode(sprintf("%02x",d[i + 4])), 
			d[i + 5], d[i + 6])		
	}
	return i
}
function print_assoc(desc, ncf,	d, nd, i) {
	nd = split(desc, d)
	i = 2
	while (i < nd) {
		i = scan_desc(d, i, nd, USB_DT_CONFIG)
		if (!i) return 0
		if (d[i + o_bConfigurationValue] == ncf) {
			#print desc
			#print "found config #" d[i+o_bConfigurationValue] " length " le_word(d[i+2], d[i+3])
			i = scan_desc(d, i + d[i], nd, USB_DT_INTERFACE_ASSOCIATION)
			return print_assoc_def(d, i)
		} else {
			#print "not found config #" d[i+o_bConfigurationValue] " length " le_word(d[i+2], d[i+3])
			i += le_word(d[i+2], d[i+3])
		}
	}
	return 0
}
function print_eps(d, i, nd, nep, spd,	j, maxps){
	for (j = 0; j < nep && i < nd;) {
		if (d[i+1] == USB_DT_ENDPOINT ) {
			maxps = le_word(d[i+4], d[i+5])
			#print "print_eps", d[i+4], d[i+5], maxps
			printf("E:  Ad=%02x(%s) Atr=%02i(%s) MxPS=%4i*%s Ivl=%s\n", 
				d[i + 2], (d[i + 2] > 128) ? "in" : "out",
				d[i + 3], ep_type[d[i + 3] % 4],
				maxps % 2048, int(maxps / 2048) + 1, 
				(spd <= 12) ? d[i + 6] "ms" : 
					int(125 * (2 ^ (d[i + 6] - 1))) "us")
			 j++
		}
		i += d[i]
	}
	return i
}
function print_alts(p, nif, nalt, spd, drv,	nd, d, i, filey, desc){
	filey = "od -vAx -tu1 --width=5000 " p "descriptors"
	if ( ((filey) | getline desc) < 0) return;
	close(filey)
	if (!(nif >= FirstIf && nif < (FirstIf + IfCount))) print_assoc(desc, 1)
	i = find_int(desc, 1)
	nd = split(desc, d)
	while (i && i < nd) {
		if (nif == d[i + 2]) {
			printf("I:%s If#=%2i Alt=%2i #EPs=%2i Cls=%s(%s) Sub=%02i Prot=%02i Driver=%s\n",
			((nalt != d[i + 3]) ? " " : "*"),
			d[i + 2], d[i + 3], d[i + 4], 
			sprintf("%02x",d[i + 5]), 
			class_decode(sprintf("%02x",d[i + 5])),
			d[i + 6], d[i + 7], drv)
			if (d[i + 4]) {
				i = print_eps(d, i + d[i], nd, d[i + 4], spd)
				continue
			} 
		}
		i = scan_desc(d, i + d[i], nd, USB_DT_INTERFACE)
	}
	#print "print_alts if=" nif filey

}
function print_interfaces(dev, level, spd,   ip, dr, p, t, t1, di, ndi, ndi2, i, nep, nif, nalt, drv) {
	ndi = getdir(dev "*-*:*")
	for (i in dirs) di[i] = dirs[i]
	delete dirs
	for (ip = 0; ip < ndi; ip++) {
		p = di[ip]
		if ( ( ("readlink " p "/driver") | getline dr) <= 0) dr = "(none)"
		close("readlink " p "/driver")
		nep = f(p "bNumEndpoints") + 0
		t = split(dr, t1, "/")
		drv = t1[t]
		nif = f(p "bInterfaceNumber") + 0
		nalt = f(p "bAlternateSetting") + 0

		print_alts(dev, nif, nalt, spd, drv)
	}
}
function print_device(dev, level, parent, count,   port, dc, di, ndi, ip, spd, i) {
	port = 0
	if (level > 0) { port = substr(dev, length(dev)-1, 1) - 1 }
	#print "print_device " dev, level, parent, count
	spd = f(dev "speed")
	printf("\nT:  Bus=%02i Lev=%02i Prnt=%02i Port=%02i Cnt=%02i Dev#=%3i Spd=%-3s MxCh=%2i\n",
		f(dev "busnum"), level, parent, port, count, 
		f(dev "devnum"), spd, f(dev "maxchild")) 

	printf("D:  Ver=%5s Cls=%s(%s) Sub=%s Prot=%s MxPS=%2i #Cfgs=%3i\n",
		f(dev "version"), f(dev "bDeviceClass"), 
		class_decode(f(dev "bDeviceClass")), f(dev "bDeviceSubClass"), 
		f(dev "bDeviceProtocol"), f(dev "bMaxPacketSize0"), 
		f(dev "bNumConfigurations"))

	printf("P:  Vendor=%s ProdID=%s Rev=%2i.%02i\n",
		f(dev "idVendor"), f(dev "idProduct"),
		substr(f(dev "bcdDevice"),1, 2),
		substr(f(dev "bcdDevice"),3, 2) )

	print_string(dev "manufacturer", "Manufacturer")
	print_string(dev "product", "Product")
	print_string(dev "serial", "SerialNumber")

	printf("C:* #Ifs=%2i Cfg#=%2i Atr=%s MxPwr=%s\n",
		f(dev "bNumInterfaces"), f(dev "bConfigurationValue"),
		f(dev "bmAttributes"), f(dev "bMaxPower") )

	print_interfaces(dev, level, spd)

	ndi = getdir(dev "*-*")
	for (i in dirs) di[i] = dirs[i]
	delete dirs

	for (ip = 0; ip < ndi; ip++) {
		if (!match(di[ip], /:/)) {
			print_device(di[ip], level+1, f(dev "devnum"), ++dc)
		}
	}
}
FILENAME != lastFILENAME { 
	print_device(bus[FN], 0, 0, 0)
	lastFILENAME = FILENAME
	FN++
	}
