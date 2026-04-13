#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "lf/macro.h"

LF_COMPAT_BEGIN

// int types

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

#if UINTPTR_MAX == UINT64_MAX
#define LF_64BIT
typedef u64 usize;
typedef i64 isize;

#elif UINTPTR_MAX == UINT32_MAX
#define LF_32BIT
typedef u32 usize;
typedef i32 isize;

#else
#error "architecture not supported"
#endif

// float types
typedef float f32;
typedef double f64;

// bit control
bool lf_ispow2(usize v);

bool lf_aligned_to(usize v, usize align);
usize lf_align_up(usize v, usize align);
usize lf_align_down(usize v, usize align);

i32 lf_ctz(usize v);
i32 lf_clz(usize v);

usize lf_log2ceil(usize v);
usize lf_log2floor(usize v);

LF_COMPAT_END
