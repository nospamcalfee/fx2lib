; Copyright (C) 2009 Steve Calfee
;
; This library is free software; you can redistribute it and/or
; modify it under the terms of the GNU Lesser General Public
; License as published by the Free Software Foundation; either
; version 2.1 of the License, or (at your option) any later version.
; 
; This library is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
; Lesser General Public License for more details.
; 
; You should have received a copy of the GNU Lesser General Public
; License along with this library; if not, write to the Free Software
; Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

.module INT2JT ; jump table for usb auto vector

; these are to help make sure 
; this assembly gets stuck in the right place 
; and I guess you could read INT2/4AV for kicks too
; read one of them to a dummy location causes this module to
; get linked in
.globl _INT2JT ; defined as global so this assembly gets included in project 

.globl _INT2AV
.globl _INT4AV
.area INT2JV (ABS,OVR)
.org    0x43 ; this is where USBINT ( interrupt 8 ) jumps to
_INT2AV = #. + 2 ; two bytes for ljmp (auto set by INT2IVEC)
    ljmp _INT2JT

.area INT4JV (ABS,OVR)
.org    0x53 ; where INT4 jumps to 
_INT4AV = #. + 2
    ljmp _INT2JT ; the addr gets replaced so this really goes to int4jt locations


; INT2 Jump Table

.area INT2JT ( CODE )
;.org    0x1A00 ; needs to be on a page boundary

_INT2JT:
_usb_isr::              ; autovector jump table
                ljmp    _usb_sudav_isr     ; Setup Data Available
                .db     0
                ljmp    _usb_sof_isr       ; Start of Frame
                .db     0
                ljmp    _usb_sutok_isr     ; Setup Data Loading
                .db     0
                ljmp    _usb_suspend_isr   ; Global Suspend
                .db     0
                ljmp    _usb_usbreset_isr  ; USB Reset
                .db     0
                ljmp    _usb_reserved_isr  ; Reserved
                .db     0
                ljmp    _usb_ep0in_isr     ; End Point 0 In
                .db     0
                ljmp    _usb_ep0out_isr    ; End Point 0 Out
                .db     0
                ljmp    _usb_ep1in_isr     ; End Point 1 In
                .db     0
                ljmp    _usb_ep1out_isr    ; End Point 1 Out
                .db     0
                ljmp    _usb_ep2in_isr     ; End Point 2 In
                .db     0
                ljmp    _usb_ep2out_isr    ; End Point 2 Out
                .db     0
                ljmp    _usb_ep3in_isr     ; End Point 3 In
                .db     0
                ljmp    _usb_ep3out_isr    ; End Point 3 Out
                .db     0
                ljmp    _usb_ep4in_isr     ; End Point 4 In
                .db     0
                ljmp    _usb_ep4out_isr    ; End Point 4 Out
                .db     0
                ljmp    _usb_ep5in_isr     ; End Point 5 In
                .db     0
                ljmp    _usb_ep5out_isr    ; End Point 5 Out
                .db     0
                ljmp    _usb_ep6in_isr     ; End Point 6 In
                .db     0
                ljmp    _usb_ep6out_isr    ; End Point 6 Out
                .db     0
                ljmp    _usb_ep7in_isr     ; End Point 7 In
                .db     0
                ljmp    _usb_ep7out_isr    ; End Point 7 Out
                .db     0

.area           USBJT   (ABS,CODE)
    
