//-----------------------------------------------------------------------------
//      File:           ezregs.h
//      Contents:       EZ-USB register declarations and bit mask definitions.
//
//      Copyright (c) 1997 AnchorChips, Inc. All rights reserved
//-----------------------------------------------------------------------------
#ifndef EZREGS_H		/* Header Sentry */
#define EZREGS_H

/*-----------------------------------------------------------------------------
	Global Variables
-----------------------------------------------------------------------------*/

#define NEWEZREG(_name,_where,_size) volatile xdata at _where _size _name

typedef unsigned char u8_t;
typedef unsigned short u16_t;
typedef struct {
    u8_t cntrl;			// End point control register
    u8_t bytes;			// End point buffer byte count
} EPIOC;


/* Register Assignments 3/18/99 TPM */
NEWEZREG(OUT7BUF[64],0x7B40,u8_t);
NEWEZREG(IN7BUF[64],0x7B80,u8_t);
NEWEZREG(OUT6BUF[64],0x7BC0,u8_t);
NEWEZREG(IN6BUF[64],0x7C00,u8_t);
NEWEZREG(OUT5BUF[64],0x7C40,u8_t);
NEWEZREG(IN5BUF[64],0x7C80,u8_t);
NEWEZREG(OUT4BUF[64],0x7CC0,u8_t);
NEWEZREG(IN4BUF[64],0x7D00,u8_t);
NEWEZREG(OUT3BUF[64],0x7D40,u8_t);
NEWEZREG(IN3BUF[64],0x7D80,u8_t);
NEWEZREG(OUT2BUF[64],0x7DC0,u8_t);
NEWEZREG(IN2BUF[64],0x7E00,u8_t);
NEWEZREG(OUT1BUF[64],0x7E40,u8_t);
NEWEZREG(IN1BUF[64],0x7E80,u8_t);
NEWEZREG(OUT0BUF[64],0x7EC0,u8_t);
NEWEZREG(IN0BUF[64],0x7F00,u8_t);
NEWEZREG(OUT8DATA,0x7F60,u8_t);
NEWEZREG(OUT9DATA,0x7F61,u8_t);
NEWEZREG(OUT10DATA,0x7F62,u8_t);
NEWEZREG(OUT11DATA,0x7F63,u8_t);
NEWEZREG(OUT12DATA,0x7F64,u8_t);
NEWEZREG(OUT13DATA,0x7F65,u8_t);
NEWEZREG(OUT14DATA,0x7F66,u8_t);
NEWEZREG(OUT15DATA,0x7F67,u8_t);
NEWEZREG(IN8DATA,0x7F68,u8_t);
NEWEZREG(IN9DATA,0x7F69,u8_t);
NEWEZREG(IN10DATA,0x7F6A,u8_t);
NEWEZREG(IN11DATA,0x7F6B,u8_t);
NEWEZREG(IN12DATA,0x7F6C,u8_t);
NEWEZREG(IN13DATA,0x7F6D,u8_t);
NEWEZREG(IN14DATA,0x7F6E,u8_t);
NEWEZREG(IN15DATA,0x7F6F,u8_t);
NEWEZREG(OUT8BCH,0x7F70,u8_t);
NEWEZREG(OUT8BCL,0x7F71,u8_t);
NEWEZREG(OUT9BCH,0x7F72,u8_t);
NEWEZREG(OUT9BCL,0x7F73,u8_t);
NEWEZREG(OUT10BCH,0x7F74,u8_t);
NEWEZREG(OUT10BCL,0x7F75,u8_t);
NEWEZREG(OUT11BCH,0x7F76,u8_t);
NEWEZREG(OUT11BCL,0x7F77,u8_t);
NEWEZREG(OUT12BCH,0x7F78,u8_t);
NEWEZREG(OUT12BCL,0x7F79,u8_t);
NEWEZREG(OUT13BCH,0x7F7A,u8_t);
NEWEZREG(OUT13BCL,0x7F7B,u8_t);
NEWEZREG(OUT14BCH,0x7F7C,u8_t);
NEWEZREG(OUT14BCL,0x7F7D,u8_t);
NEWEZREG(OUT15BCH,0x7F7E,u8_t);
NEWEZREG(OUT15BCL,0x7F7F,u8_t);
NEWEZREG(CPUCS,0x7F92,u8_t);
NEWEZREG(PORTACFG,0x7F93,u8_t);
NEWEZREG(PORTBCFG,0x7F94,u8_t);
NEWEZREG(PORTCCFG,0x7F95,u8_t);
NEWEZREG(OUTA,0x7F96,u8_t);
NEWEZREG(OUTB,0x7F97,u8_t);
NEWEZREG(OUTC,0x7F98,u8_t);
NEWEZREG(PINSA,0x7F99,u8_t);
NEWEZREG(PINSB,0x7F9A,u8_t);
NEWEZREG(PINSC,0x7F9B,u8_t);
NEWEZREG(OEA,0x7F9C,u8_t);
NEWEZREG(OEB,0x7F9D,u8_t);
NEWEZREG(OEC,0x7F9E,u8_t);
NEWEZREG(UART230,0x7F9F,u8_t);
NEWEZREG(ISOERR,0x7FA0,u8_t);
NEWEZREG(ISOCTL,0x7FA1,u8_t);
NEWEZREG(ZBCOUT,0x7FA2,u8_t);
NEWEZREG(ZBCIN,0x7FA3,u8_t);
NEWEZREG(I2CS,0x7FA5,u8_t);
NEWEZREG(I2DAT,0x7FA6,u8_t);
NEWEZREG(IVEC,0x7FA8,u8_t);
NEWEZREG(IN07IRQ,0x7FA9,u8_t);
NEWEZREG(OUT07IRQ,0x7FAA,u8_t);
NEWEZREG(USBIRQ,0x7FAB,u8_t);
NEWEZREG(IN07IEN,0x7FAC,u8_t);
NEWEZREG(OUT07IEN,0x7FAD,u8_t);
NEWEZREG(USBIEN,0x7FAE,u8_t);
NEWEZREG(USBBAV,0x7FAF,u8_t);
NEWEZREG(BPADDR,0x7FB2,u16_t);
NEWEZREG(EPIO[16],0x7FB4,EPIOC);
NEWEZREG(SUDPTRH,0x7FD4,u8_t);
NEWEZREG(SUDPTRL,0x7FD5,u8_t);
NEWEZREG(USBCS,0x7FD6,u8_t);
NEWEZREG(TOGCTL,0x7FD7,u8_t);
NEWEZREG(USBFRAMEL,0x7FD8,u8_t);
NEWEZREG(USBFRAMEH,0x7FD9,u8_t);
NEWEZREG(FNADDR,0x7FDB,u8_t);
NEWEZREG(USBPAIR,0x7FDD,u8_t);
NEWEZREG(IN07VAL,0x7FDE,u8_t);
NEWEZREG(OUT07VAL,0x7FDF,u8_t);
NEWEZREG(INISOVAL,0x7FE0,u8_t);
NEWEZREG(OUTISOVAL,0x7FE1,u8_t);
NEWEZREG(FASTXFR,0x7FE2,u8_t);
NEWEZREG(AUTOPTRH,0x7FE3,u8_t);
NEWEZREG(AUTOPTRL,0x7FE4,u8_t);
NEWEZREG(AUTODATA,0x7FE5,u8_t);
NEWEZREG(SETUPDAT[8],0x7FE8,u8_t);
NEWEZREG(OUT8ADDR,0x7FF0,u8_t);
NEWEZREG(OUT9ADDR,0x7FF1,u8_t);
NEWEZREG(OUT10ADDR,0x7FF2,u8_t);
NEWEZREG(OUT11ADDR,0x7FF3,u8_t);
NEWEZREG(OUT12ADDR,0x7FF4,u8_t);
NEWEZREG(OUT13ADDR,0x7FF5,u8_t);
NEWEZREG(OUT14ADDR,0x7FF6,u8_t);
NEWEZREG(OUT15ADDR,0x7FF7,u8_t);
NEWEZREG(IN8ADDR,0x7FF8,u8_t);
NEWEZREG(IN9ADDR,0x7FF9,u8_t);
NEWEZREG(IN10ADDR,0x7FFA,u8_t);
NEWEZREG(IN11ADDR,0x7FFB,u8_t);
NEWEZREG(IN12ADDR,0x7FFC,u8_t);
NEWEZREG(IN13ADDR,0x7FFD,u8_t);
NEWEZREG(IN14ADDR,0x7FFE,u8_t);
NEWEZREG(IN15ADDR,0x7FFF,u8_t);


/*-----------------------------------------------------------------------------
	Special Function Registers (SFRs)
-----------------------------------------------------------------------------*/
sfr at 0x81 SP;
sfr at 0x82 DPL;
sfr at 0x83 DPH;
sfr at 0x84 DPL1;
sfr at 0x85 DPH1;
sfr at 0x86 DPS;

  /*  DPS  */
sfr at 0x87 PCON;
sfr at 0x88 TCON;

  /*  TCON  */
sbit at 0x88+0 IT0;  
sbit at 0x88+1 IE0;
sbit at 0x88+2 IT1;
sbit at 0x88+3 IE1;
sbit at 0x88+4 TR0;
sbit at 0x88+5 TF0;
sbit at 0x88+6 TR1;
sbit at 0x88+7 TF1;
sfr at 0x89 TMOD;

  /*  TMOD  */
sfr at 0x8A TL0;
sfr at 0x8B TL1;
sfr at 0x8C TH0;
sfr at 0x8D TH1;
sfr at 0x8E CKCON;

  /*  CKCON  */
sfr at 0x8F SPC_FNC;		// Was WRS in Reg320

sfr at 0x91 EXIF;		// EXIF Bit Values differ from Reg320
sfr at 0x92 MPAGE;
sfr at 0x98 SCON0;

  /*  SCON0  */
sbit at 0x98+0 RI;
sbit at 0x98+1 TI;
sbit at 0x98+2 RB8;
sbit at 0x98+3 TB8;
sbit at 0x98+4 REN;
sbit at 0x98+5 SM2;
sbit at 0x98+6 SM1;
sbit at 0x98+7 SM0;
sfr at 0x99 SBUF0;
sfr at 0xA8 IE;

  /*  IE  */
sbit at 0xA8+0 EX0;
sbit at 0xA8+1 ET0;
sbit at 0xA8+2 EX1;
sbit at 0xA8+3 ET1;
sbit at 0xA8+4 ES0;
sbit at 0xA8+5 ET2;
sbit at 0xA8+6 ES1;
sbit at 0xA8+7 EA;
sfr at 0xB8 IP;

  /*  IP  */
sbit at 0xB8+0 PX0;
sbit at 0xB8+1 PT0;
sbit at 0xB8+2 PX1;
sbit at 0xB8+3 PT1;
sbit at 0xB8+4 PS0;
sbit at 0xB8+5 PT2;
sbit at 0xB8+6 PS1;
sfr at 0xC0 SCON1;

  /*  SCON1  */
sbit at 0xC0+0 RI1;
sbit at 0xC0+1 TI1;
sbit at 0xC0+2 RB81;
sbit at 0xC0+3 TB81;
sbit at 0xC0+4 REN1;
sbit at 0xC0+5 SM21;
sbit at 0xC0+6 SM11;
sbit at 0xC0+7 SM01;
sfr at 0xC1 SBUF1;
sfr at 0xC8 T2CON;

  /*  T2CON  */
sbit at 0xC8+0 CP_RL2;
sbit at 0xC8+1 C_T2;
sbit at 0xC8+2 TR2;
sbit at 0xC8+3 EXEN2;
sbit at 0xC8+4 TCLK;
sbit at 0xC8+5 RCLK;
sbit at 0xC8+6 EXF2;
sbit at 0xC8+7 TF2;
sfr at 0xCA RCAP2L;
sfr at 0xCB RCAP2H;
sfr at 0xCC TL2;
sfr at 0xCD TH2;
sfr at 0xD0 PSW;

  /*  PSW  */
sbit at 0xD0+0 P;
sbit at 0xD0+1 FL;
sbit at 0xD0+2 OV;
sbit at 0xD0+3 RS0;
sbit at 0xD0+4 RS1;
sbit at 0xD0+5 F0;
sbit at 0xD0+6 AC;
sbit at 0xD0+7 CY;
sfr at 0xD8 EICON;	// Was WDCON in DS80C320; Bit Values differ from Reg320
sbit at 0xD8+3 INT6;
sbit at 0xD8+4 RESI;
sbit at 0xD8+5 ERESI;
sbit at 0xD8+7 SMOD1;
sfr at 0xE0 ACC;
sfr at 0xE8 EIE;		// EIE Bit Values differ from Reg320
sbit at 0xE8+0 EUSB;
sbit at 0xE8+1 EI2C;
sbit at 0xE8+2 EIEX4;
sbit at 0xE8+3 EIEX5;
sbit at 0xE8+4 EIEX6;
sfr at 0xF0 B;
sfr at 0xF8 EIP;		// EIP Bit Values differ from Reg320
sbit at 0xF8+0 PUSB;
sbit at 0xF8+1 PI2C;
sbit at 0xF8+2 EIPX4;
sbit at 0xF8+3 EIPX5;
sbit at 0xF8+4 EIPX6;

/*-----------------------------------------------------------------------------
	Bit Masks
-----------------------------------------------------------------------------*/

/* CPU Control & Status Register */
#define bmCHIPREV		(bmBIT7 | bmBIT6 | bmBIT5 | bmBIT4)
#define bmCLK24OE		bmBIT1
#define bm8052RES		bmBIT0
/* Port Configuration Registers */
/* Port A */
#define bmRXD1OUT		bmBIT7
#define bmRXD0OUT		bmBIT6
#define bmFRD			bmBIT5
#define bmFWR			bmBIT4
#define bmCS			bmBIT3
#define bmOE			bmBIT2
#define bmT1OUT			bmBIT1
#define bmT0OUT			bmBIT0
/* Port B */
#define bmT2OUT			bmBIT7
#define bmINT6			bmBIT6
#define bmINT5			bmBIT5
#define bmINT4			bmBIT4
#define bmTXD1			bmBIT3
#define bmRXD1			bmBIT2
#define bmT2EX			bmBIT1
#define bmT2			bmBIT0
/* Port C */
#define bmRD			bmBIT7
#define bmWR			bmBIT6
#define bmT1			bmBIT5
#define bmT0			bmBIT4
#define bmINT1			bmBIT3
#define bmINT0			bmBIT2
#define bmTXD0			bmBIT1
#define bmRXD0			bmBIT0
/* Isochronous Status & End Point Valid Registers */
#define bmEP15			bmBIT7
#define bmEP14			bmBIT6
#define bmEP13			bmBIT5
#define bmEP12			bmBIT4
#define bmEP11			bmBIT3
#define bmEP10			bmBIT2
#define bmEP9			bmBIT1
#define bmEP8			bmBIT0
/* I2C Control & Status Register */
#define bmSTART			bmBIT7
#define bmSTOP			bmBIT6
#define bmLASTRD		bmBIT5
#define bmID			(bmBIT4 | bmBIT3)
#define bmBERR			bmBIT2
#define bmACK			bmBIT1
#define bmDONE			bmBIT0
/* Interrupt Vector Register */
#define bmIV4			bmBIT6
#define bmIV3			bmBIT5
#define bmIV2			bmBIT4
#define bmIV1			bmBIT3
#define bmIV0			bmBIT2
/* End point Interrupt Request, End Point Interrupt Enable */
/* And End Point Valid Registers */
#define bmEP7			bmBIT7
#define bmEP6			bmBIT6
#define bmEP5			bmBIT5
#define bmEP4			bmBIT4
#define bmEP3			bmBIT3
#define bmEP2			bmBIT2
#define bmEP1			bmBIT1
#define bmEP0			bmBIT0
/* Global Interrupt Request & Enable Registers */
#define bmIBN        		bmBIT5
#define bmURES			bmBIT4
#define bmSUSP			bmBIT3
#define bmSUTOK			bmBIT2
#define bmSOF			bmBIT1
#define bmSUDAV			bmBIT0
/* Global Control */
#define bmBREAK			bmBIT3
#define bmBPPULSE		bmBIT2
#define bmBPEN			bmBIT1
#define bmAVEN			bmBIT0
/* USB Control & Status Register */
#define bmRWAKEUP		bmBIT7
#define bmDISCON		bmBIT3
#define bmDISCOE		bmBIT2
#define bmRENUM			bmBIT1
#define bmSIGRESUME		bmBIT0
/* End Point 0 Control & Status Register */
#define bmOUT			bmBIT3
#define bmIN			bmBIT2
#define bmHS			bmBIT1
#define bmHSSTALL		bmBIT0
/* End Point Control & Status Registers */
#define bmEPSTALL		bmBIT0
#define bmEPBUSY		bmBIT1
/* Fast Transfer Register */
#define bmFISO			bmBIT7
#define bmFBLK			bmBIT6
#define bmRPOL			bmBIT5
#define bmRMOD1			bmBIT4
#define bmRMOD0			bmBIT3
#define bmWPOL			bmBIT2
#define bmWMOD1			bmBIT1
#define bmWMOD0			bmBIT0
/* Endpoint Pairing Register */
#define bmISOSEND0		bmBIT7
#define bmPR6OUT		bmBIT5
#define bmPR4OUT		bmBIT4
#define bmPR2OUT		bmBIT3
#define bmPR6IN			bmBIT2
#define bmPR4IN			bmBIT1
#define bmPR2IN			bmBIT0
/* End point control offsets */
enum {  IN0BUF_ID, 
	IN1BUF_ID, 
	IN2BUF_ID, 
	IN3BUF_ID, 
	IN4BUF_ID, 
	IN5BUF_ID,
	IN6BUF_ID,
    	IN7BUF_ID, 
    	OUT0BUF_ID, 
    	OUT1BUF_ID, 
    	OUT2BUF_ID, 
    	OUT3BUF_ID,
    	OUT4BUF_ID, 
    	OUT5BUF_ID, 
    	OUT6BUF_ID, 
    	OUT7BUF_ID
};

#define EP0CS	EPIO[0].cntrl
#define IN0BC	EPIO[0].bytes
#define IN1CS	EPIO[1].cntrl
#define IN1BC	EPIO[1].bytes
#define IN2CS	EPIO[2].cntrl
#define IN2BC	EPIO[2].bytes
#define IN3CS	EPIO[3].cntrl
#define IN3BC	EPIO[3].bytes
#define IN4CS	EPIO[4].cntrl
#define IN4BC	EPIO[4].bytes
#define IN5CS	EPIO[5].cntrl
#define IN5BC	EPIO[5].bytes
#define IN6CS	EPIO[6].cntrl
#define IN6BC	EPIO[6].bytes
#define IN7CS	EPIO[7].cntrl
#define IN7BC	EPIO[7].bytes
#define OUT0CS	EPIO[8].cntrl
#define OUT0BC	EPIO[8].bytes
#define OUT1CS	EPIO[9].cntrl
#define OUT1BC	EPIO[9].bytes
#define OUT2CS	EPIO[10].cntrl
#define OUT2BC	EPIO[10].bytes
#define OUT3CS	EPIO[11].cntrl
#define OUT3BC	EPIO[11].bytes
#define OUT4CS	EPIO[12].cntrl
#define OUT4BC	EPIO[12].bytes
#define OUT5CS	EPIO[13].cntrl
#define OUT5BC	EPIO[13].bytes
#define OUT6CS	EPIO[14].cntrl
#define OUT6BC	EPIO[14].bytes
#define OUT7CS	EPIO[15].cntrl
#define OUT7BC	EPIO[15].bytes

#endif				/* EZREGS_H */
