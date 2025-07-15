/*main nodeA*/
#include <LPC21xx.H>
#include "header.h"
#define SW1 ((IOPIN0>>14)&1)	//P0.14
#define SW2 ((IOPIN0>>15)&1)	//P0.15
#define SW3 ((IOPIN0>>16)&1)	//P0.16

CAN1 LI;
CAN1 Head;
CAN1 RI;
int main(){
	u32 flag1=0;
	u32 flag2=0;
	u32 flag3=0;
	can1_init();
	
	//Head data
	Head.id=0x201;
	Head.rtr=0;//data-frame
	Head.dlc=1;
	
	//Right indicator data;
	RI.id=0x202;
	RI.rtr=0;//data-frame
	RI.dlc=1;
	
	//Left indicator data;
	LI.id=0x203;
	LI.rtr=0;//data-frame
	LI.dlc=1;
	
	while(1){
		if(SW1==0){
			while(SW1==0);
			delay_ms(50);//to avoid key debouncing
			flag1^=1;
			if(flag1)
				Head.byteA=0x10;//headlight on
			else
				Head.byteA=0x11;//headlight off
			can1_tx(Head);//send data-frame		
	}
		
	if(SW2==0){
			while(SW2==0);
			delay_ms(50);//to avoid key debouncing
			flag2^=1;
			if(flag2)
				RI.byteA=0x12;//Right indic on
			else
				RI.byteA=0x13;//Right indic off
			can1_tx(RI);//send data-frame		
	}
	
		if(SW3==0){
			while(SW3==0);
			delay_ms(50);//to avoid key debouncing
			flag3^=1;
			if(flag3)
				LI.byteA=0x14;//Right indic on
			else
				LI.byteA=0x15;//Right indic off
			can1_tx(LI);//send data-frame		
	
}
}
}

