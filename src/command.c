#include "command.h"

#include <getopt.h>
#include <stdio.h>
#include <string.h>

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

int cmd_clock_in(int argc, char **argv, const trakr_t *app) {
  int ch;
  char task[TRAKR_TASK_LENGTH] = {0};
  time_t start = -1;

  struct option longopts[] = {
      {"task", required_argument, NULL, 't'},
      {"at", required_argument, NULL, 'a'},
      {0, 0, 0, 0},
  };

  optind = 2;
  while ((ch = getopt_long(argc, argv, "+t:a:", longopts, NULL)) != -1) {
    switch (ch) {
    case 't':
      strncpy(task, optarg, TRAKR_TASK_LENGTH - 1);
      task[TRAKR_TASK_LENGTH - 1] = '\0';
      break;
    case 'a':
      if ((start = trakr_session_parse_time(optarg)) == -1) {
        trakr_log("unable to parse time '%s'\n", optarg);
        return 1;
      }
      break;
    default:
      return 1;
    }
  }
  argc -= optind;
  argv += optind;

  if (argc == 1 || task[0] == '\0') {
    trakr_log("clock in requires a task name\n");
    return 1;
  }

  if (trakr_session_active(app)) {
    trakr_log(
        "cannot clock into a new session when a session is already active\n");
    return 1;
  }

  trakr_session_t session;
  if (!trakr_session_new(&session, task, start, -1)) {
    trakr_log("could not create new session\n");
    return 1;
  }

  char startstr[TRAKR_TIME_LENGTH];
  trakr_session_strtime(startstr, TRAKR_TIME_LENGTH, session.start);
  printf("Clocked in at %s\n", startstr);
  printf("  - %d | %s\n", session.id, session.task);

  return 0;
}

int cmd_clock_out(int argc, char **argv, const trakr_t *app) {
  int ch;
  time_t end = -1;

  struct option longopts[] = {
      {"at", required_argument, NULL, 'a'},
      {0, 0, 0, 0},
  };

  optind = 2;
  while ((ch = getopt_long(argc, argv, "+a:", longopts, NULL)) != -1) {
    switch (ch) {
    case 'a':
      if ((end = trakr_session_parse_time(optarg)) == -1) {
        trakr_log("unable to parse time '%s'\n", optarg);
        return 1;
      }
      break;
    default:
      return 1;
    }
  }
  argc -= optind;
  argv += optind;

  if (trakr_session_active(app)) {
    trakr_log("cannot clock out of session when none are active\n");
    return 1;
  }

  // TODO remove this when clocking out actual current task
  if (end == -1) {
    end = time(NULL);
  }

  char endstr[TRAKR_TIME_LENGTH];
  trakr_session_strtime(endstr, TRAKR_TIME_LENGTH, end);
  printf("Clocked out at %s\n", endstr);
  return 0;
}
