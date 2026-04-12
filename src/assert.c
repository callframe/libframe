#include "lf/assert.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

_Noreturn void LF_PANIC_SYM(const char *file, u32 line, const char *fmt,
                              ...) {
  fprintf(stderr, "PANIC at %s:%d: ", file, line);

  va_list args;
  va_start(args, fmt);
  vfprintf(stderr, fmt, args);
  va_end(args);

  fputs("\n", stderr);
  fflush(stderr);
  abort();
}
