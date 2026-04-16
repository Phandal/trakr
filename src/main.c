#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "command.h"

void usage() {
  fprintf(stderr, "USAGE:\n  trakr <command> [<options>]\n\n");
  fprintf(stderr, "COMMANDS\n");
  fprintf(stderr, "  %-15sClock in to a session\n", "in");
  fprintf(stderr, "  %-15sClock out of the current session\n", "out");
  fprintf(stderr, "  %-15sReport time logged\n", "report");
  fprintf(stderr, "  %-15sUpdate a session\n", "update");
  fprintf(stderr, "  %-15sDelete a session\n", "delete");
}

int main(int argc, char **argv) {
  int ch;
  int res;
  char *command;

  if (argc == 1) {
    usage();
    exit(EXIT_FAILURE);
  }
  command = argv[1];
  argc--;
  argv++;

  if (cmd_is_help(command)) {
    usage();
    res = 0;
  } else if (strcmp(command, "in") == 0) {
    res = cmd_clock_in(argc, argv);
  } else if (strcmp(command, "out") == 0) {
    res = cmd_clock_out(argc, argv);
  } else {
    fprintf(stderr, "trakr: unknown command '%s'\n", command);
    usage();
    res = 1;
  }

  return res;
}
