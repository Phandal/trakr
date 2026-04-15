#include "command.h"

#include <getopt.h>
#include <stdio.h>
#include <string.h>

#include "trakr.h"

int cmd_is_help(const char *command) {
  if (strcmp(command, "help") == 0) {
    return 1;
  }

  if (strcmp(command, "--help") == 0) {
    return 1;
  }

  if (strcmp(command, "-h") == 0) {
    return 1;
  }

  return 0;
}

int cmd_clock_in(int argc, char **argv) {
  int ch;
  char task[TRAKR_TASK_LENGTH];
  if (argc == 1) {
    fprintf(stderr, "trakr: clock in requires a task name\n");
    return 1;
  }

  struct option longopts[] = {
      {"task", required_argument, NULL, 't'},
      {0, 0, 0, 0},
  };

  while ((ch = getopt_long(argc, argv, "+t:", longopts, NULL)) != -1) {
    switch (ch) {
    case 't':
      strncpy(task, optarg, TRAKR_TASK_LENGTH - 1);
      task[TRAKR_TASK_LENGTH - 1] = '\0';
      break;
    default:
      return 1;
    }
  }

  printf("Clocked in to session\n  - %s\n", task);

  return 1;
}

int cmd_clock_out(int argc, char **argv) { return 1; }
