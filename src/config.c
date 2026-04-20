#include "config.h"
#include "trakr.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *_expand_home(const char *path) {
  if (!path) {
    return NULL;
  }

  if (path[0] == '~') {
    char *home = getenv("HOME");
    if (!home) {
      return NULL;
    }

    size_t size = strlen(home) + strlen(path + 1) + 2;
    char *full = malloc(size);
    if (snprintf(full, size, "%s/%s", home, path + 1) < 0) {
      return NULL;
    }

    return full;
  }

  return strdup(path);
}

config_t *config_new(void) {
  config_t *config = malloc(sizeof(config_t));
  if (!config) {
    return NULL;
  }

  const char *path = getenv("TRAKR_FILE");
  if (!path) {
    path = TRAKR_FILE;
  }

  config->data_path = _expand_home(path);
  if (!config->data_path) {
    free(config);
    return NULL;
  }

  return config;
}

void config_free(config_t *config) {
  if (!config) {
    return;
  }

  free(config->data_path);
  free(config);
  config = NULL;
}
