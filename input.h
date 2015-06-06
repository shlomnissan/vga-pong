#ifndef INPUT_H
#define INPUT_H

#include <dos.h>

#include "types.h"

#define I_KEYBOARD	0x60

#define KEY_UP_D	72
#define KEY_UP_R	200
#define KEY_DOWN_D	80
#define KEY_DOWN_R	208
#define KEY_ESCAPE	1

int readKeyboard(void);

#endif
