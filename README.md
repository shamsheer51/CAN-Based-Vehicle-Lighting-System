 # Vehicle Lighting System on LPC2129

 Lights are important in a vehicle just like how we all need some positive light in life! So here to solve that I implemented a lighting system which is made possible due to the CAN (Controller Area Network)
 present in LPC2129 a ARM7 based microcontroller. Here is a quick walkthrough to my design.

 ## Features
 - The switch controls for the light is implemented internally with external interrupts so achieving a higher response time compared to their polling based condition checks.
 - A full fledged CAN Bus is adhering with CAN 2.0A standard which is simple and efficient for the automotive control works.
 - The Decentralized setup with seperate ECU's is less prone to failure in times of malfunction.
 - Added UART support for effective debugging of frames in the serial terminal.
 - Drivers written from scratch that runs in a bare-metal setup without heavy dependence on external libraries.

## Setup

The entire code-base here is written in Keil Microvision 5 and the startup code is provided by the NXP semiconductors. Replications of this project can be done by cloning the repository and opening the files
in Keil. 

> **NOTE:** This implementation of Embedded-C code is targetted towards LPC2129 microcontroller. To run in the other it requires some slight modifications so refer your microcontroller datasheet accordingly

## Block Diagram
<div align="center">
<img src="Demo.png" alt="Project Architecture" width="1000" />
</div>

Here is the following Data frame details:

**Left Indicator Data Frame:**
- ID:0x203
- LI ON DATA:**0x14**
- LI OFF DATA:**0x15**

**Headlight Data Frame:**
- ID:**0x201**
- HL ON DATA:**0x10**
- HL OFF DATA:**0x11**

**Right Indicator Data Frame:**
- ID:**0x202**
- RI ON DATA:**0x12**
- RI OFF DATA:**0x13**

These are the only frames accepted by the Rx side due to the configuration of the Message Acceptance system in the CAN peripheral. To allow further messages it needs to be modified,

## Directory Structure
### **Rx section**
```text
├── Rx
    ├── can1_driver.c       // CAN1 Driver
    ├── delay.c             // Timer driver for LPC2129
    ├── header.h            // All header files to be added 
    ├── main3.c             // Program Body
    ├── p1.ini              //INI script for Rx side debbugging
    ├── rx
    ├── Rxnode.uvproj       // project file for keil
    ├── Startup.s           //Startup code for LPC2129
    └── uart0_driver.c      //UART0 driver for LPC2129
```
Here is a quick view of the Rx section of the project

The receiver here does the following actions:

- Receive the Data-frames from the ECU and take actions accordingly.
- Send Error-frame back in-event of errors.
- Whenever Data-frame is received the interrupt is triggered to take the action.

### **Tx section**

```text
└── Tx
    ├── can1_driver.c       //CAN1 Driver LPC2129
    ├── delay.c             //Timer Driver LPC2129
    ├── header.h            //Header files
    ├── interrpt.c          //Driver to handle external interrupts
    ├── main2.c             //Main body
    ├── Startup.s           //Startup code on Tx section
    ├── Txnode.uvproj       //Keil Project file
    └── uart0_driver.c      //UART0 driver for LPC2129
```
Here is a quick overview of the Tx side of the project

The transmitter node does the following actions:

- Transmit the data-frame when the corresponding external interrupt is triggered.
- Act as a centralized control-panel for operation.
- Interfacing ECU's to the user.

## Contact & Queries

For any queries regarding this project contact
# CAN-Based-Vehicle-Lighting-System
