/*header.h*/

typedef unsigned int u32;
typedef signed int s32;
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;

//CAN Frame
typedef struct CAN1_MSG{
	u32 id;
	u32 byteA;
	u32 byteB;
	u8 rtr;
	u8 dlc;
}CAN1;


extern void delay_sec(unsigned int);
extern void delay_ms(unsigned int);



extern void uart0_init(unsigned int baud);
extern void uart0_tx(unsigned char data);
extern void uart0_tx_string(u8 *ptr);
extern void uart0_rx_string(u8 *ptr,u8 len);
extern u8 uart0_rx(void);

extern void can1_tx(CAN1 v);
extern void can1_init(void);
extern void can1_rx(CAN1 *ptr);

extern void config_vic_for_eint(void);
extern void config_eint(void);




