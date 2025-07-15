/*interrpt.c*/

#include"header.h"
#include<LPC21XX.H>

//flags for controlling the tx
extern int flag1;//left indicator
extern int flag2;//headlight
extern int flag3;//Right indicator



void EINT0_handler() __irq
{
flag1=1;
EXTINT|=(1<<0);
VICVectAddr=0;
}

void EINT1_handler()__irq{
flag2=1;
EXTINT|=(1<<1);
VICVectAddr=0;
}

void EINT2_handler()__irq{
flag3=1;
EXTINT|=(1<<2);
VICVectAddr=0;
}


void config_eint(void){
//u32 temp=(10<<27);
PINSEL0|=(10U<<28);//pinsel for P0.14 and P0.15
PINSEL1|=1;//PINSEL for P0.16
EXTMODE=7;//settings interrupts to edge sensitive
EXTPOLAR=0;//active low
}

void config_vic_for_eint(void){
VICIntSelect=0;
VICVectAddr0=(int)EINT0_handler;
VICVectAddr1=(int)EINT1_handler;
VICVectAddr2=(int)EINT2_handler;
VICVectCntl0=14|(1<<5);
VICVectCntl1=15|(1<<5);
VICVectCntl2=16|(1<<5);
VICIntEnable=(1<<14)|(1<<15)|(1<<16);
}
