#include "lf/bit.h"

#include <limits.h>

#include "lf/assert.h"
#include "lf/compat.h"
#include "lf/macro.h"

i32 lf_ctz(usize v) {
  if (v == 0) return sizeof(usize) * CHAR_BIT;

// GNUC handling
#if defined(LF_COMPILER_GNUC)
#if defined(LF_64BIT)
  return lf_cast(i32, __builtin_ctzll(lf_cast(unsigned long long, v)));
#elif defined(LF_32BIT)
  return lf_cast(i32, __builtin_ctz(lf_cast(unsigned long, v)));
#else
#error "not supported"
#endif

// MSVC handling
#elif defined(LF_COMPILER_MSVC)
#error "not supported"
#endif
}

i32 lf_clz(usize v) {
  if (v == 0) return sizeof(usize) * CHAR_BIT;

// GNUC handling
#if defined(LF_COMPILER_GNUC)
#if defined(LF_64BIT)
  return lf_cast(i32, __builtin_clzll(lf_cast(unsigned long long, v)));
#elif defined(LF_32BIT)
  return lf_cast(i32, __builtin_clz(lf_cast(unsigned long, v)));
#else
#error "not supported"
#endif

// MSVC handling
#elif defined(LF_COMPILER_MSVC)
#error "not supported"
#endif
}

bool lf_ispow2(usize v) { return v && ((v & (v - 1)) == 0); }

bool lf_aligned_to(usize v, usize align) {
  lf_assert(lf_ispow2(align));
  return (v & (align - 1)) == 0;
}

usize lf_align_up(usize v, usize align) {
  lf_assert(lf_ispow2(align));
  return (v + align - 1) & ~(align - 1);
}

usize lf_align_down(usize v, usize align) {
  lf_assert(lf_ispow2(align));
  return v & ~(align - 1);
}

usize lf_log2ceil(usize v) {
  lf_assert(v != 0);
  return sizeof(usize) * CHAR_BIT - lf_cast(usize, lf_clz(v - 1));
}

usize lf_log2floor(usize v) {
  lf_assert(v != 0);
  return (sizeof(usize) * CHAR_BIT - 1) - lf_cast(usize, lf_clz(v));
}
