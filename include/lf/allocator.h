#pragma once

#include "lf/bit.h"
#include "lf/compat.h"

LF_COMPAT_BEGIN

typedef u8* (*lf_allocate_t)(u8* self, usize size, usize align);
typedef void (*lf_deallocate_t)(u8* self, u8* p);

struct lf_allocator {
  u8* self;
  lf_allocate_t allocate;
  lf_deallocate_t deallocate;
};

_Thread_local extern const struct lf_allocator* LF_ALLOCATOR;

const struct lf_allocator* lf_allocator_default(void);

u8* lf_allocate(usize size, usize align);
void lf_deallocate(u8* p);

LF_COMPAT_END
