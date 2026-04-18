#define _XOPEN_SOURCE

#include "session.h"
#include "trakr.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char *_session_current_file_name(const config_t *config) {
  char *current_filename = "current";
  char day_dir[9] = {0};

  time_t tm = time(NULL);
  struct tm *timeptr = localtime(&tm);

  strftime(day_dir, 9, "%m%d%Y", timeptr);

  size_t size = strlen(config->directory) + strlen(day_dir) +
                strlen(current_filename) + 3;

  char *path = malloc(sizeof(char) * size);
  snprintf(path, size, "%s/%s/%s", config->directory, day_dir,
           current_filename);
  printf("current path: %s\n", path);
  return path;
}

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

  if (end != -1) {
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

int session_strtime(const time_t time, char *buf) {
  int rs;
  struct tm *timeptr = localtime(&time);
  if (!timeptr) {
    return -1;
  }

  if ((rs = strftime(buf, 6, "%H:%M", timeptr)) == 0) {
    return -1;
  }

  return rs;
}

session_t *session_parse(const char *s) {
  char start[TRAKR_TIME_LENGTH];
  char end[TRAKR_TIME_LENGTH];
  char task[TRAKR_TASK_LENGTH];

  if (sscanf(s, "%5s | %5s | %511[^\n]", start, end, task) != 3) {
    return NULL;
  }

  time_t start_time;
  time_t end_time;

  if ((start_time = session_new_time(start)) == -1) {
    return NULL;
  }

  if (strncmp(end, "null", TRAKR_TIME_LENGTH) == 0) {
    end_time = -1;
  } else {
    if ((end_time = session_new_time(end)) == -1) {
      return NULL;
    }
  }

  return session_new(task, start_time, end_time);
}

int session_str(session_t *session, char *buf) {
  char start[TRAKR_TIME_LENGTH] = {0};
  char end[TRAKR_TIME_LENGTH] = {0};

  if (session_strtime(session->start, start) == -1) {
    return -1;
  }

  if (session->has_ended) {
    if (session_strtime(session->end, end) == -1) {
      return -1;
    }
  }
  
  return snprintf(buf, TRAKR_SESSION_LENGTH, "%s | %s | %s", start, end,
                  session->task);
}

void session_free(session_t *session) {
  if (session == NULL) {
    return;
  }

  free(session);
  session = NULL;
}

session_t *session_is_currently_active(const config_t *config) {
  char session_buf[TRAKR_SESSION_LENGTH] = {0};
  char *filepath = _session_current_file_name(config);

  FILE *fd = fopen(filepath, "r");
  if (fd == NULL) {
    perror("fopen");
    return NULL;
  }

  fgets(session_buf, TRAKR_SESSION_LENGTH, fd);
  fclose(fd);
  free(filepath);

  if (session_buf[0] == '\0') {
    return NULL;
  }

  return session_parse(session_buf);
}

