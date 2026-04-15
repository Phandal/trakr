#ifndef COMMAND_H
#define COMMAND_H

int cmd_is_help(const char *);

int cmd_clock_in(int, char **);

int cmd_clock_out(int, char **);

#endif // COMMAND_H
