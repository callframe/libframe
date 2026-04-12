#pragma once

#ifdef __cplusplus
#define LF_CXX
#endif

#ifdef LF_CXX
#define LF_COMPAT_BEGIN extern "C" {
#define LF_COMPAT_END }

#else
#define LF_COMPAT_BEGIN
#define LF_COMPAT_END

#endif

#if defined(__clang__) || defined(__GNUC__)
#define LF_COMPILER_GNUC

#elif defined(_MSC_VER)
#define LF_COMPILER_MSVC

#else
#error "this compiler is not supported"
#endif

#if defined(LF_COMPILER_GNUC)
#define lf_likely(x) __builtin_expect(!!(x), 1)
#define lf_unlikely(x) __builtin_expect(!!(x), 0)

#elif defined(LF_COMPILER_MSVC)
#define lf_likely(x) (x)
#define lf_unlikely(x) (x)

#endif
