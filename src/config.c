#include "config.h"
#include "trakr.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

config_t *config_new() {
  char *user_defined_dir = NULL;
  config_t *config = (config_t *)malloc(sizeof(config_t));
  if (!config) {
    return NULL;
  }
  config->directory = strdup(TRAKR_DIR);

  if ((user_defined_dir = getenv("TRAKR_DIR")) != NULL) {
    config->directory = user_defined_dir;
  }

  if (config->directory[0] == '~' && config->directory[1] == '/') {
    config->directory += 2;
    char *home = getenv("HOME");
    if (home == NULL) {
      return NULL;
    }

    size_t size = strlen(config->directory) + strlen(home) + 2;
    char *fullpath = malloc(sizeof(char) * size);
    snprintf(fullpath, size, "%s/%s", home, config->directory);
    config->directory = fullpath;
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
