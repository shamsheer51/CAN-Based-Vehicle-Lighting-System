/*main Rx*/
#include <LPC21xx.H>
#include "header.h"


CAN1 r1;
u32 flag;
u32 leftflag;
u32 rightflag;

int main(){
	can1_init();//this initialization must be first
	config_vic_for_can1();
	uart0_init(9600);
	IODIR0|=LED1|LED2|LED3;
	IOSET0|=LED1|LED2|LED3;
	uart0_tx_string("nodeB\r\n");
	while(1){
		//can1_rx(&r1);//waiting for msg to receive
		if(flag==1){//any frame is received
			flag=0;//for next frame
			if(r1.rtr==0){
				uart0_tx_string("data-frame received\r\n");
//				if(r1.id==0x201)
//					{
//				switch(r1.byteA&0xFF)
//					{
//				case 0x10://turn ON headlight
//									uart0_tx_string("HEAD ON\r\n");IOCLR0=LED1;break;
//				case 0x11://turn OFF headlight	
//									uart0_tx_string("HEAD OFF\r\n");IOSET0=LED1;break;
//					}
//			}
			if(r1.id==0x202)
					{
				switch(r1.byteA&0xFF)
					{
				case 0x12:/*turn ON RI*/
									uart0_tx_string("RI ON\r\n");rightflag=1;right_blink();break;
				case 0x13:/*turn OFF RI*/	
									uart0_tx_string("RI OFF\r\n");break;
					}
			}
			if(r1.id==0x203)
					{
				switch(r1.byteA&0xFF)
					{
				case 0x14:/*turn ON LI*/
									uart0_tx_string("LI ON\r\n");leftflag=1;left_blink();break;
				case 0x15:/*turn OFF LI*/	
									uart0_tx_string("LI OFF\r\n");break;
					}
			}
		}
		else
				uart0_tx_string("remote-frame received\r\n");
		}			
	}
}
