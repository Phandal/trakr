#define _XOPEN_SOURCE

#include "session.h"
#include "trakr.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

static char time_str[6] = {0};

session_t *session_new(const char *task, const time_t start, const time_t end) {
  session_t *session = (session_t *)malloc(sizeof(session_t));
  if (!session) {
    return NULL;
  }

  // TODO make this dynamic
  session->id = 1;

  strncpy(session->task, task, TRAKR_TASK_LENGTH - 1);
  session->task[TRAKR_TASK_LENGTH - 1] = '\0';

  if (start == -1) {
    if ((session->start = time(NULL)) == -1) {
      return NULL;
    }
  } else {
    session->start = start;
  }

  if (end == -1) {
    session->has_ended = 1;
  } else {
    session->end = end;
  }

  return session;
}

time_t session_new_time(const char *timestr) {
  time_t current_time = time(NULL);
  struct tm *parts = localtime(&current_time);
  parts->tm_sec = 0;

  if (strptime(timestr, "%H:%M", parts) == NULL) {
    return -1;
  }

  return mktime(parts);
}

char *session_strtime(const time_t time) {
  struct tm *timeptr = localtime(&time);
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
