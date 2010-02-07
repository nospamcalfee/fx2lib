#!/usr/bin/gawk -f
# findusb.awk version 1.1
# Copyright: 2010 Steve Calfee
#
# This software may be used and distributed according to the terms of
# the GNU General Public License (GPL), version 2, or at your option
# any later version.
#
# All examples below use the keyspan USA-19Qi vid/pid "06cd 010c"
# To find all "interfaces" for all vid/pid:
# findusb.awk 06cd 010c -i
# To find all paths in /dev/usb for the listed vid/pid:
# findusb.awk 06cd 010c -d
# To find the path to an existing driver /unbind param in sysfs
# findusb.awk 6cd 10c -p
# 
# Mix and match, to make the driver unbind writeable:
# sudo chmod a+w `./findusb.awk 06cd 010c -p`
# 
# To unbind an existing driver:
# echo -n `./findusb.awk 06cd 010c -i` > `./findusb.awk 6cd 10c -p`
# 
# To load a new firmware:
# sudo fxload -D `./findusb.awk 06cd 010c -d` -I bulkloop.ihx
BEGIN {
	buses = "/sys/bus/usb/devices/usb*"
	FN = nbus = 1;
	# extract vid pid 
	if (ARGC < 3) exit 1
	for (i = 1; i < ARGC; i++) {
		if (tolower(ARGV[i]) ~ /^\-v/) verbose++
		if (tolower(ARGV[i]) ~ /^\-p/) path++
		if (tolower(ARGV[i]) ~ /^\-i/) interface++
		if (tolower(ARGV[i]) ~ /^\-d/) devnode++
		if (tolower(ARGV[i]) !~ /^\-/) {
			if (VID == "") VID = ARGV[i]	
				else PID = ARGV[i]
		}
		ARGV[i] = ""
	}
	if (verbose+0) {
		print ARGC,"VID=",VID,"PID=",PID
		print "path=" path " intf=" interface " devnode=" devnode
	}
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
function fx( str ) {
	return strtonum("0x" str)
}
function find_device(dev, level, parent, count,   dc, di, ndi, ip, i, dr, ndr, tdr) {
	if (verbose+0 > 1) print "find_device " dev, level, parent, count
	if (verbose+0 > 1) print f(dev "busnum"), f(dev "devnum"), f(dev "idVendor"), f(dev "idProduct")
	ndi = getdir(dev "*-*")
	for (i in dirs) di[i] = dirs[i]
	delete dirs

	for (ip = 0; ip < ndi; ip++) {
		if (!match(di[ip], /:/)) {
			find_device(di[ip], level+1, f(dev "devnum"), ++dc)
		} else {
			if (verbose+0) printf("%03d/%03d dvid=%x vid=%x dpid=%x pid=%x\n", f(dev "busnum"), f(dev "devnum"), fx(f(dev "idVendor")), fx(VID), fx(f(dev "idProduct")), fx(PID))
			if (fx(VID) == fx(f(dev "idVendor")) && 
				fx(f(dev "idProduct")) == fx(PID)) {
					#print dev, di[ip]
					if ( ( ("readlink " di[ip] "/driver") | getline dr) <= 0) dr = "(none)"
					#path for driver
					if (path+0) print di[ip] dr "/unbind"; 
					ndr = split(di[ip], tdr, "/")
					#interface id used for unbind
					if (interface+0) print tdr[ndr - 1]; 
					#print device to do I/O on
					if (devnode+0) printf("/dev/bus/usb/%03d/%03d",f(dev "busnum"), f(dev "devnum")) 
				}
		}
	}
}
FILENAME != lastFILENAME { 
	find_device(bus[FN], 0, 0, 0)
	lastFILENAME = FILENAME
	FN++
	}
