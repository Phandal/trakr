#include "config.h"
#include "trakr.h"

#include <stdlib.h>

config_t config_new() {
  char *user_defined_dir = NULL;
  config_t config = {.directory = TRAKR_DIR};

  if ((user_defined_dir = getenv("TRAKR_DIR")) != NULL) {
    config.directory = user_defined_dir;
  }

  return config;
}
