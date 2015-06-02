#ifndef INPUT_H
#define INPUT_H

#include <dos.h>

#include "types.h"

#define I_KEYBOARD	0x60

#define KEY_UP		72
#define KEY_DOWN	80
#define KEY_ESCAPE	1

int readKeyboard(void);

#endif
