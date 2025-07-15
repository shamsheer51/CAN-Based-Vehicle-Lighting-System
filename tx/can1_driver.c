/*can1_driver.c*/
#include <LPC21xx.H>
#include "header.h"

void can1_init(void){
	VPBDIV=1;
	PINSEL1|=0x40000;
	C1MOD=0x1;//reset mode
	AFMR=2;//accept all incoming msgs
	C1BTR=0x001C001D;//125Kbps baudrate
	C1MOD=0;//release reset mode
}

#define TCS ((C1GSR>>3)&1)
void can1_tx(CAN1 v){
	C1TID1=v.id;//set identifier
	C1TFI1=v.dlc<<16;//set DLC=8,RTR=0,FF=0
	if(v.rtr==0){//if data-frame
		C1TDA1=v.byteA;
		C1TDB1=v.byteB;
	}	
	else//if remoteframe
		C1TFI1|=(1<<30);//rtr=1
	C1CMR=1|(1<<5);//Select Txbuf1 & start xmission
	while(TCS==0);
}





