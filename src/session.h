#ifndef SESSION_H
#define SESSION_H

#include <time.h>

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

char *session_strtime(const time_t);

void session_free(session_t *);

#endif // SESSION_H
