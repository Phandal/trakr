#ifndef COMMAND_H
#define COMMAND_H

#include "trakr.h"

int cmd_is_help(const char *);

int cmd_clock_in(int, char **, const trakr_t *);

int cmd_clock_out(int, char **, const trakr_t *);

#endif // COMMAND_H
