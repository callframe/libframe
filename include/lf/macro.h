#pragma once

#define lf_unused(x) ((void)(x))
#define lf_enum(T, name) typedef T name; enum
#define lf_zerout(x, n) memset((x), 0, (n) * sizeof(x))
