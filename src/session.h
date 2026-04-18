#ifndef SESSION_H
#define SESSION_H

#include <time.h>

#include "config.h"
#include "trakr.h"

typedef struct {
  unsigned int id;
  char task[TRAKR_TASK_LENGTH];
  time_t start;
  int has_ended;
  time_t end;
} session_t;

session_t *session_new(const char *, const time_t, const time_t);

time_t session_new_time(const char *);

int session_strtime(const time_t, char *);

session_t *session_parse(const char *);

int session_str(session_t *, char *);

void session_free(session_t *);

session_t *session_is_currently_active(const config_t *);

#endif // SESSION_H
