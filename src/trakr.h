#ifndef TRAKR_H
#define TRAKR_H

#define _XOPEN_SOURCE 700

#define TRAKR_ID_LENGTH 5

#define TRAKR_TIME_LENGTH 16

#define TRAKR_TASK_LENGTH 512

#define TRAKR_HEADER_LENGTH                                                    \
  (TRAKR_ID_LENGTH + 1 + TRAKR_TIME_LENGTH + 1 + TRAKR_TIME_LENGTH)

#define TRAKR_SESSION_LENGTH (TRAKR_HEADER_LENGTH + 1 + TRAKR_TASK_LENGTH)

#define TRAKR_FILE "~/.trakr"

#include <stdint.h>
#include <time.h>

#include "config.h"

typedef struct {
  uint16_t id;
  time_t start;
  time_t end;
  char task[TRAKR_TASK_LENGTH];
} trakr_session_t;

typedef struct {
  size_t count;
  size_t cap;
  trakr_session_t *sessions;
} trakr_t;

void trakr_log(const char *, ...);

trakr_t *trakr_load(const config_t *);

void trakr_free(trakr_t *);

int trakr_session_new(trakr_session_t *, const char *, time_t, time_t);

time_t trakr_session_parse_date(const char *);

time_t trakr_session_parse_time(const char *);

int trakr_session_strtime(char *, size_t, time_t);

int trakr_session_active(const trakr_t *);

#endif // TRAKR_H
