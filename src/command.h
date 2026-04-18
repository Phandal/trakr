#ifndef COMMAND_H
#define COMMAND_H

#include "config.h"

int cmd_is_help(const char *);

int cmd_clock_in(int, char **, config_t *);

int cmd_clock_out(int, char **, config_t *);

#endif // COMMAND_H
