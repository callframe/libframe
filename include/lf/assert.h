#pragma once

#include "lf/bit.h"
#include "lf/compat.h"

LF_COMPAT_BEGIN

_Noreturn void LF_PANIC_SYM(const char* file, u32 line, const char* fmt, ...);

#define lf_panic(...) LF_PANIC_SYM(__FILE__, __LINE__, __VA_ARGS__)

#ifdef NDEBUG
#include "lf/macro.h"
#define lf_assert(cond) lf_unused(cond)

#else
#define lf_assert(cond)                                                \
  do {                                                                 \
    if (lf_unlikely(!(cond))) lf_panic("assertion failed: %s", #cond); \
  } while (0);

#endif

LF_COMPAT_END
