/*uart0_driver.c*/
#include <LPC21xx.H>
#include "header.h"

void uart0_init(u32 baud){
	int a[]={15,60,30,15,15};
	PINSEL0|=0x5;
	unsigned int result=0,pclk;
	pclk=a[VPBDIV]*1000000;
	result=pclk/(16*baud);
	U0LCR=0x83;//8N1, DLAB=1
	U0DLL=result&0xFF;//lower byte res
	U0DLM=(result>>8)&0xFF;//upper byte res
	U0LCR=0x03;//8N1, DLAB=0
}

#define THRE ((U0LSR>>5)&1)
void uart0_tx(u8 data){
	U0THR=data;
	while(THRE==0);
}

#define RDR (U0LSR&1)
u8 uart0_rx(void){
	while(RDR==0);
	return U0RBR;
}

void uart0_tx_string(u8 *ptr){
	while(*ptr!='\0'){
	 U0THR=*ptr;
	 while(THRE==0);
		//delay_ms(10);
   ptr++;		
	}
}

void uart0_rx_string(u8 *ptr,
											u8 len){
	s32 i;
	for(i=0;i<len;i++){
		while(RDR==0);//polling condition
		ptr[i]=U0RBR;
		if(ptr[i]=='\r')//if enter key
			break;
	}
	ptr[i]='\0';//null
}










