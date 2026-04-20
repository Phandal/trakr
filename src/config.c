#include "config.h"
#include "trakr.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *_expand_home(const char *dir) {
  if (!dir) {
    return NULL;
  }

  if (dir[0] == '~') {
    char *home = getenv("HOME");
    if (!home) {
      return NULL;
    }

    size_t size = strlen(home) + strlen(dir + 2) + 2;
    char *full = malloc(size);
    if (snprintf(full, size, "%s/%s", home, dir) < 0) {
      return NULL;
    }

    return full;
  }

  return strdup(dir);
}

config_t *config_new(void) {
  config_t *config = malloc(sizeof(config_t));
  if (!config) {
    return NULL;
  }

  const char *dir = getenv("TRAKR_DIR");
  if (!dir) {
    dir = TRAKR_DIR;
  }

  config->directory = _expand_home(dir);
  if (!config->directory) {
    free(config);
    return NULL;
  }

  return config;
}

void config_free(config_t *config) {
  if (!config) {
    return;
  }

  free(config->directory);
  free(config);
  config = NULL;
}
