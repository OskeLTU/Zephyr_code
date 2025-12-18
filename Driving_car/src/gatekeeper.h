#ifndef GATEKEEPER_H
#define GATEKEEPER_H

#include <stdbool.h>

void bluetouth_signal_recived();
void bluetouth_release();
void timeout_control();

bool bluetouth_in_control();

#endif