#ifndef _KEY_H_					   /*if not define*/
#define _KEY_H_
#include <STC8.H>
#include "display.h"
unsigned char button_scan(void);
void password_scan();
void Delay(unsigned char x);
void Key_Mode(void);
sbit key1=P2^4;
sbit key2=P2^5;
sbit key3=P2^6;
sbit key4=P2^7;
sbit p2_0=P2^0;
sbit p21=P2^1;

#endif     
