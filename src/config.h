#ifndef CONFIG_H
#define CONFIG_H

typedef struct {
  char *directory;
} config_t;

config_t *config_new(void);

void config_free(config_t *);

#endif // CONFIG_H
