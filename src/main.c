#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "command.h"
#include "config.h"
#include "trakr.h"

void usage() {
  trakr_log("USAGE:\n  trakr <command> [<options>]\n\n");
  trakr_log("COMMANDS\n");
  trakr_log("  %-15sClock in to a session\n", "in");
  trakr_log("  %-15sClock out of the current session\n", "out");
  trakr_log("  %-15sReport time logged\n", "report");
  trakr_log("  %-15sUpdate a session\n", "update");
  trakr_log("  %-15sDelete a session\n", "delete");
}

int main(int argc, char **argv) {
  int res;
  char *command;

  if (argc == 1) {
    usage();
    exit(EXIT_FAILURE);
  }
  command = argv[1];
  argc--;
  argv++;

  config_t *config = config_new();
  if (!config) {
    trakr_log("could not create config\n");
    return 1;
  }
  printf("using config dir: %s\n", config->directory);

  if (cmd_is_help(command)) {
    usage();
    res = 0;
  } else if (strcmp(command, "in") == 0) {
    res = cmd_clock_in(argc, argv, config);
  } else if (strcmp(command, "out") == 0) {
    res = cmd_clock_out(argc, argv, config);
  } else {
    trakr_log("unknown command '%s'\n", command);
    usage();
    res = 1;
  }

  config_free(config);
  return res;
}
