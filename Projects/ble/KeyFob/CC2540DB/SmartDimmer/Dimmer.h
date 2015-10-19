#ifndef __DIMMER_H
#define __DIMMER_H

char readIntensity(void);

void increaseIntensity(void);
void decreaseIntensity(void);

typedef struct {
  unsigned char port;
  unsigned char pin;
} PINConfig;
#endif