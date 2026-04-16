#include "session.h"
#include "trakr.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

static char time_str[6] = {0};

session_t *session_new(const char *task) {
  session_t *session = (session_t *)malloc(sizeof(session_t));
  if (!session) {
    return NULL;
  }

  strncpy(session->task, task, TRAKR_TASK_LENGTH - 1);
  session->task[TRAKR_TASK_LENGTH - 1] = '\0';

  session->start = time(NULL);
  if (session->start == -1) {
    return NULL;
  }
  return session;
}

char *session_time(time_t *time) {
  struct tm *timeptr = localtime(time);
  if (!timeptr) {
    return NULL;
  }

  strftime(time_str, 6, "%H:%M", timeptr);
  return time_str;
}

void session_free(session_t *session) {
  if (session == NULL) {
    return;
  }

  free(session);
  session = NULL;
}
