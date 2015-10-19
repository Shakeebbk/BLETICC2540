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

#ifdef CC2540_BRICK_BOARD
#define DATA_PORT_0 P0
#define DATA_PIN_0 5
#define DATA_PORT_1 P0
#define DATA_PIN_1 4
#define DATA_PORT_2 P0
#define DATA_PIN_2 3
#define DATA_PORT_3 P0
#define DATA_PIN_3 2
#else
#define DATA_PORT_0 P1
#define DATA_PIN_0 2
#define DATA_PORT_1 P1
#define DATA_PIN_1 4
#define DATA_PORT_2 P1
#define DATA_PIN_2 7
#define DATA_PORT_3 P0
#define DATA_PIN_3 6
#endif
   
static void setIntensity(char value);
/*
clear bit - position starts from 0
 */
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
			DATA_PORT_0 = setBit(DATA_PORT_0, DATA_PIN_0);
		}
		else {
			DATA_PORT_0 = clearBit(DATA_PORT_0, DATA_PIN_0);
		}
		
		if((value>>1) & 0x01) {
			DATA_PORT_1 = setBit(DATA_PORT_1, DATA_PIN_1);
		}
		else {
			DATA_PORT_1 = clearBit(DATA_PORT_1, DATA_PIN_1);
		}
		
		if((value>>2) & 0x01) {
			DATA_PORT_2 = setBit(DATA_PORT_2, DATA_PIN_2);
		}
		else {
			DATA_PORT_2 = clearBit(DATA_PORT_2, DATA_PIN_2);
		}
		
		if((value>>3) & 0x01) {
			DATA_PORT_3 = setBit(DATA_PORT_3, DATA_PIN_3);
		}
		else {
			DATA_PORT_3 = clearBit(DATA_PORT_3, DATA_PIN_3);
		}
	}
}

char readIntensity(void) {
        char val = 0;
        if(readBit(DATA_PORT_0, DATA_PIN_0)) {
                val = setBit(val, 0);
        }
        if(readBit(DATA_PORT_1, DATA_PIN_1)) {
                val = setBit(val, 1);
        }
        if(readBit(DATA_PORT_2, DATA_PIN_2)) {
                val = setBit(val, 2);
        }
        if(readBit(DATA_PORT_3, DATA_PIN_3)) {
                val = setBit(val, 3);
        }
        return val;
}

void increaseIntensity(void) {
  unsigned int level = readIntensity();
  level++;
  setIntensity(level);
}
void decreaseIntensity(void) {
  unsigned int level = readIntensity();
  level--;
  setIntensity(level);
}