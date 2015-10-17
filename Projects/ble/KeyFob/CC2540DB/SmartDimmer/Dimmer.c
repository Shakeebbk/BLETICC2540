/*
Author: Shakeeb
Date: 15 Oct 2015
 */
#include "Dimmer.h"
#include "bcomdef.h"
#include "OSAL.h"
#include "OSAL_PwrMgr.h"

#include "OnBoard.h"
#include "hal_adc.h"
#include "hal_led.h"
#include "hal_key.h"
#include "gatt.h"

#include "hci.h"
   
static void setIntensity(char value);
/*
clear bit - position starts from 0
 */

static int debugCount = 0;
char clearBit(char val, int position) {
	val &= ~(1<<position);
	return val;
}

/*
setBit - position starts form 0
 */
char setBit(char val, int position) {
	val |= (1<<position);
        return val;
}

/*
readBit - position starts form 0
 */
bool readBit(char val, int position) {
        return((val>>position) & 0x01);
}
static void setIntensity(char value) {
	if((value < 16) && (value >=0)) {
		if(value & 0x01) {
			P1 = setBit(P1, 2);
		}
		else {
			P1 = clearBit(P1, 2);
		}
		
		if((value>>1) & 0x01) {
			P1 = setBit(P1, 4);
		}
		else {
			P1 = clearBit(P1, 4);
		}
		
		if((value>>2) & 0x01) {
			P1 = setBit(P1, 7);
		}
		else {
			P1 = clearBit(P1, 7);	
		}
		
		if((value>>3) & 0x01) {
			P0 = setBit(P1, 6);
		}
		else {
			P0 = clearBit(P1, 6);
		}
	}
        //Debug
        //debugCount = value;  
}

char readIntensity(void) {
        char val = 0;
        if(readBit(P1, 2)) {
                val = setBit(val, 0);
        }
        if(readBit(P1, 4)) {
                val = setBit(val, 1);
        }
        if(readBit(P1, 7)) {
                val = setBit(val, 2);
        }
        if(readBit(P0, 6)) {
                val = setBit(val, 3);
        }
        return val;
        //return debugCount;
}

void increaseIntensity(void) {
  int level = readIntensity();
  level++;
  setIntensity(level);
}
void decreaseIntensity(void) {
  int level = readIntensity();
  level--;
  setIntensity(level);
}