/*can1_driver.c
  Rxnode
*/
#include <LPC21xx.H>
#include "header.h"
extern CAN1 r1;
extern u32 flag;
extern u32 leftflag;
extern u32 rightflag;

unsigned int *ptr=(unsigned int*)0xE0038000;
void can1_init(void){
	PINSEL1|=0x40000;//P0.25-->RD1
	VPBDIV=1;//PCLK==60MHz
	C1MOD=0x1;//Select reset mode
	C1BTR=0x001C001D;//125Kbps baudrate
	
	//AF setting for INI testing
	ptr[0]=0x22012202;//ID 0x201 & 0x202
	ptr[1]=0x22032204;//ID 0x203 & 0x204
	

	/*AF setting for embC testing
	ptr[0]=0x02010202;//ID 0x201 & 0x202
	ptr[1]=0x02030204;//ID 0x203 & 0x204*/

	SFF_sa=0;
	SFF_GRP_sa=0xC;
	EFF_sa=0xC;
	EFF_GRP_sa=0xC;
	ENDofTable=0x0C;
	AFMR=0x0;//Enable AF sertings
	C1MOD=0x0;//Release reset mode
}


void CAN1_Rx_Handler(void) __irq{
	r1.id=C1RID;
	r1.dlc=(C1RFS>>16)&0xF;//extract dlc
	r1.rtr=(C1RFS>>30)&1;//extract rtr
	if(r1.rtr==0){//if data-frame
		r1.byteA=C1RDA;
		r1.byteB=C1RDB;
	}
	C1CMR=(1<<2);//*release rxbuf
	flag=1;
	if(r1.id==0x201)
					{
				switch(r1.byteA&0xFF)
					{
				case 0x10://turn ON headlight
									uart0_tx_string("HEAD ON\r\n");IOCLR0=LED1;break;
				case 0x11://turn OFF headlight	
									uart0_tx_string("HEAD OFF\r\n");IOSET0=LED1;break;
					}
				}
	if(((r1.byteA&0xFF)==0x15)||((r1.byteA&0xFF)==0x12))
		{
		leftflag=0;
		}
	if(((r1.byteA&0xFF)==0x13)||((r1.byteA&0xFF)==0x14))
		{
		rightflag=0;
		}
  VICVectAddr=0;
}

void config_vic_for_can1(void){
	VICVectAddr5=(u32)CAN1_Rx_Handler;
	VICVectCntl5=26|(1<<5);//Assign CAN1 Rx intr to slot5
	VICIntEnable=(1<<26);//En CAN1 Rx Intr in VIC peripheral
	C1IER=1;//En CAN1 Rx intr in CAN1 Peri	
}

//#define RBS (C1GSR&1)
//void can1_rx(CAN1 *ptr){
//	while(RBS==0);//waiting for DF /RF to receive
//	ptr->id=C1RID;
//	ptr->dlc=(C1RFS>>16)&0xF;//extract dlc
//	ptr->rtr=(C1RFS>>30)&1;//extract rtr
//	if(ptr->rtr==0){//if data-frame
//		ptr->byteA=C1RDA;
//		ptr->byteB=C1RDB;
//	}
//	C1CMR=(1<<2);//*release rxbuf	
//}

//#define TCS ((C1GSR>>3)&1)
//void can1_tx(CAN1 v){
//	C1TID1=v.id;//set identifier
//	C1TFI1=v.dlc<<16;//set DLC=8,RTR=0,FF=0
//	if(v.rtr==0){//if data-frame
//		C1TDA1=v.byteA;
//		C1TDB1=v.byteB;
//	}	
//	else//if remoteframe
//		C1TFI1|=(1<<30);//rtr=1
//	C1CMR=1|(1<<5);//Select Txbuf1 & start xmission
//	while(TCS==0);
//}

void left_blink(void){
	while(leftflag==1){
		uart0_tx_string((u8*)"function entered\r\n");
		IOCLR0=LED3;
		delay_ms(1000);
		IOSET0=LED3;
}
}

void right_blink(void){
	while(rightflag==1){
		uart0_tx_string((u8*)"right function entered\r\n");
		IOCLR0=LED2;
		delay_ms(1000);
		IOSET0=LED2;
}
}



