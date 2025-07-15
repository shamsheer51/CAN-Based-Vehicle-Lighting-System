/*main nodeA*/
#include <LPC21xx.H>
#include "header.h"

/*Left Indicator Data Frame
*ID:0x203
*LI ON DATA:0x14
*LI OFF DATA:0x15
*
*Headlight Data Frame
*ID:0x201
*HL ON DATA:0x10
*HL OFF DATA:0x11
*
*Right Indicator Data Frame
*ID:0x202
*RI ON DATA:0x12
*RI OFF DATA:0x13
*/

//data frames
CAN1 LI;
CAN1 Head;
CAN1 RI;

//flags for choosing transmit conditions
u32 flag1;
u32 flag2;
u32 flag3;

int main()
{
	//flags for toggling the conditions
	u32 en1=0;
	u32 en2=0;
	u32 en3=0;
	
	//uart0,can1,vic and ext-intrpts init
	uart0_init(9600);
	can1_init();
	config_eint();
	config_vic_for_eint();
	
	//Headlight data
	Head.id=0x201;
	Head.rtr=0;//data-frame
	Head.dlc=1;
	
	//Right-indicator data;
	RI.id=0x202;
	RI.rtr=0;//data-frame
	RI.dlc=1;
	
	//Left-indicator data;
	LI.id=0x203;
	LI.rtr=0;//data-frame
	LI.dlc=1;
	
	while(1){
		
//Headlight dataframe transmitting		
		if(flag2)
			{
			en1^=1;
			if(en1){
				Head.byteA=0x10;//headlight on
				uart0_tx_string((u8 *)"Headlight on\r\n");
			}
			else{
				Head.byteA=0x11;//headlight off
				uart0_tx_string((u8 *)"Headlight off\r\n");
			}
			can1_tx(Head);//send data-frame
			flag2=0;//resetting flag
	}
		
	
	
//Right-indicator data transmitting	
	if(flag3){
			en2^=1;
			if(en2){
				RI.byteA=0x12;//Right indic on
				uart0_tx_string((u8 *)"RI on\r\n");
			}
			else{
				RI.byteA=0x13;//Right indic off
				uart0_tx_string((u8 *)"RI off\r\n");
			}
			can1_tx(RI);//send data-frame		
			flag3=0;//resetting flag
	}
	
//Left-Indicator data transmitting
if(flag1){
			en3^=1;
			if(en3){
				LI.byteA=0x14;//Left indic on
				uart0_tx_string((u8 *)"LI on\r\n");
			}
			else{
				LI.byteA=0x15;//Right indic off
				uart0_tx_string((u8 *)"LI off\r\n");
			}
			can1_tx(LI);//send data-frame	
			flag1=0;//resetting flag
}
}
}

