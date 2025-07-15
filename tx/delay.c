#include<LPC21XX.H>

void delay_ms(unsigned int msec){
T0PC=0;
T0PR=15000-1;
T0TC=0;
T0TCR=1;
while(T0TC<msec);
T0TCR=0;
}

void delay_sec(unsigned int sec){
T0PC=0;
T0PR=15000000-1;
T0TC=0;
T0TCR=1;
while(T0TC<sec);
T0TCR=0;
}


