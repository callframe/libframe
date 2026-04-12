#include "lf/bit.h"
#include "lf/assert.h"
#include "lf/compat.h"
#include <limits.h>

i32 lf_ctz(usize v) {
  if (v == 0)
    return sizeof(usize) * CHAR_BIT;

// GNUC handling
#if defined(LF_COMPILER_GNUC)
#if defined(LF_64BIT)
  return (i32)__builtin_ctzll((unsigned long long)v);
#elif defined(LF_32BIT)
  return (i32)__builtin_ctz((unsigned long)v);
#else
#error "not supported"
#endif

// MSVC handling
#elif defined(LF_COMPILER_MSVC)
#error "not supported"
#endif
}

i32 lf_clz(usize v) {
  if (v == 0)
    return sizeof(usize) * CHAR_BIT;

// GNUC handling
#if defined(LF_COMPILER_GNUC)
#if defined(LF_64BIT)
  return (i32)__builtin_clzll((unsigned long long)v);
#elif defined(LF_32BIT)
  return (i32)__builtin_clz((unsigned long)v);
#else
#error "not supported"
#endif

// MSVC handling
#elif defined(LF_COMPILER_MSVC)
#error "not supported"
#endif
}

usize lf_log2ceil(usize v) {
  lf_assert(v != 0);
  return sizeof(usize) * CHAR_BIT - (usize)lf_clz(v - 1);
}

usize lf_log2floor(usize v) {
  lf_assert(v != 0);
  return (sizeof(usize) * CHAR_BIT - 1) - (usize)lf_clz(v);
}
