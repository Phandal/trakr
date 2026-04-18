#ifndef CONFIG_H
#define CONFIG_H

typedef struct {
  char *directory;
} config_t;

config_t config_new(void);

#endif // CONFIG_H
