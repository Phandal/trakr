#include "command.h"

#include <getopt.h>
#include <stdio.h>
#include <string.h>

#include "session.h"
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

int cmd_clock_in(int argc, char **argv, config_t *config) {
  int ch;
  char task[TRAKR_TASK_LENGTH] = {0};
  time_t start = -1;

  struct option longopts[] = {
      {"task", required_argument, NULL, 't'},
      {"at", required_argument, NULL, 'a'},
      {0, 0, 0, 0},
  };

  while ((ch = getopt_long(argc, argv, "+t:a:", longopts, NULL)) != -1) {
    switch (ch) {
    case 't':
      strncpy(task, optarg, TRAKR_TASK_LENGTH - 1);
      task[TRAKR_TASK_LENGTH - 1] = '\0';
      break;
    case 'a':
      if ((start = session_new_time(optarg)) == -1) {
        trakr_log("unable to parse time '%s'\n", optarg);
        return 1;
      }
      break;
    default:
      trakr_log("unknown error\n");
      return 1;
    }
  }
  argc -= optind;
  argv += optind;

  if (argc == 1 || task[0] == '\0') {
    trakr_log("clock in requires a task name\n");
    return 1;
  }

  if (session_is_currently_active(config)) {
    trakr_log("cannot clock into a new session when a session is already active\n");
    return 1;
  }

  session_t *session = session_new(task, start, -1);
  if (session == NULL) {
    trakr_log("could not create new session\n");
    return 1;
  }

  /* printf("Clocked in at %s\n", session_strtime(session->start)); */
  /* printf("  - %d | %s\n", session->id, session->task); */
  char session_buf[TRAKR_SESSION_LENGTH] = {0};
  if (session_str(session, session_buf) == -1) {
    trakr_log("could not print session\n");
  }

  printf("Created new session: %s\n", session_buf);
  
  session_free(session);
  return 0;
}

int cmd_clock_out(int argc, char **argv, config_t *config) {
  int ch;
  time_t end_time = -1;

  struct option longopts[] = {
      {"at", required_argument, NULL, 'a'},
      {0, 0, 0, 0},
  };

  while ((ch = getopt_long(argc, argv, "+a:", longopts, NULL)) != -1) {
    switch (ch) {
    case 'a':
      if ((end_time = session_new_time(optarg)) == -1) {
        trakr_log("unable to parse time '%s'\n", optarg);
        return 1;
      }
      break;
    default:
      trakr_log("unknown error\n");
      return 1;
    }
  }
  argc -= optind;
  argv += optind;

  if (session_is_currently_active(config) == NULL) {
    trakr_log("cannot clock out of session when none are active\n");
    return 1;
  }

  // TODO remove this when clocking out actual current task
  if (end_time == -1) {
    end_time = time(NULL);
  }

  char end[TRAKR_TIME_LENGTH] = {0};
  session_strtime(end_time, end);
  printf("Clocked out at %s\n", end);
  return 0;
}
