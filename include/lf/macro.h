#pragma once

#define lf_cast(T, x) ((T)(x))
#define lf_unused(x) lf_cast(void, x)
#define lf_enum(T, name) \
  typedef T name;        \
  enum
// TODO: reject pointer arguments at compile time.
#define lf_countof(x) (sizeof(x) / sizeof((x)[0]))
#define lf_zerout(x, n) memset(&(x), 0, (n) * sizeof(x))
