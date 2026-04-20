#include "trakr.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void trakr_log(const char *fmt, ...) {
  fprintf(stderr, "[trakr]: ");
  va_list list;

  va_start(list, fmt);
  vfprintf(stderr, fmt, list);
  va_end(list);
}

static size_t trakr_push_session(trakr_t *trakr,
                                 const trakr_session_t *session) {
  if (trakr->count == trakr->cap) {
    size_t new_cap = trakr->cap == 0 ? 10 : trakr->cap * 2;
    trakr_session_t *temp =
        realloc(trakr->sessions, new_cap * sizeof(trakr_session_t));
    if (!temp) {
      trakr_log("error reading sessions");
      exit(1);
    }
    trakr->cap = new_cap;
    trakr->sessions = temp;
  }

  trakr->sessions[trakr->count++] = *session;

  return trakr->count;
}

static time_t trakr_session_parse_time(const char *buf) {
  time_t current = time(NULL);
  struct tm *tm = localtime(&current);
  tm->tm_sec = 0;

  if (strptime(buf, "%Y-%m-%d %H:%M", tm) == NULL) {
    return -1;
  }

  return mktime(tm);
}

static trakr_session_t *trakr_session_parse(const char *line) {
  int offset = 0;
  char buf[TRAKR_SESSION_LENGTH + 1] = {0};
  trakr_session_t *session = malloc(sizeof(trakr_session_t));
  if (!session) {
    return NULL;
  }

  if (strnlen(line, TRAKR_HEADER_LENGTH) < TRAKR_HEADER_LENGTH) {
    return NULL;
  }

  // ID
  memmove(buf, line, TRAKR_ID_LENGTH);
  buf[TRAKR_ID_LENGTH] = '\0';
  session->id = strtol(buf, NULL, 10);
  offset += TRAKR_ID_LENGTH + 1;

  // START
  memmove(buf, line + offset, TRAKR_TIME_LENGTH);
  buf[TRAKR_TIME_LENGTH] = '\0';
  session->start = trakr_session_parse_time(buf);
  if (session->start == -1) {
    return NULL;
  }
  offset += TRAKR_TIME_LENGTH + 1;

  // END
  memmove(buf, line + offset, TRAKR_TIME_LENGTH);
  buf[TRAKR_TIME_LENGTH] = '\0';
  if (strncmp(buf, "                ", TRAKR_TIME_LENGTH) == 0) {
    session->end = -1;
  } else {
    session->end = trakr_session_parse_time(buf);
    if (session->end == -1) {
      return NULL;
    }
  }
  offset += TRAKR_TIME_LENGTH + 1;

  // TASK
  int size = strnlen(line + offset, TRAKR_TASK_LENGTH);
  memmove(session->task, line + offset, size);
  if (session->task[size - 1] == '\n') {
    session->task[size - 1] = '\0';
  }

  return session;
}

trakr_t *trakr_load(config_t *config) {
  FILE *datafile = NULL;
  char line[TRAKR_SESSION_LENGTH] = {0};
  trakr_session_t *session = NULL;
  int line_size = 0;

  trakr_t *trakr = malloc(sizeof(trakr_t));
  if (!trakr) {
    return NULL;
  }

  if ((datafile = fopen(config->data_path, "r+")) == NULL) {
    if ((datafile = fopen(config->data_path, "w+")) == NULL) {
      trakr_log("error opening data file '%s'\n", config->data_path);
      return NULL;
    }
  }

  while (fgets(line, TRAKR_SESSION_LENGTH, datafile) != NULL) {
    session = trakr_session_parse(line);
    if (!session) {
      trakr_log("corrupted data file starting with the line:\n%s", line);
      return NULL;
    }

    trakr_push_session(trakr, session);
  }

  return trakr;
}

void trakr_free(trakr_t *trakr) {
  if (!trakr) {
    return;
  }

  free(trakr->sessions);
  free(trakr);
}
