#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <stdbool.h>

extern volatile bool manual_overide_flag;

int bluetooth_begin(void);

#endif