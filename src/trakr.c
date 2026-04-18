#include "trakr.h"
#include <stdarg.h>
#include <stdio.h>

void trakr_log(const char *fmt, ...) {
  va_list list;

  va_start(list, fmt);
  vfprintf(stderr, fmt, list);
  va_end(list);
}
