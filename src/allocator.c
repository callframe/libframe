#include "lf/allocator.h"

#include <stddef.h>

#include "lf/assert.h"

_Thread_local static struct lf_allocator* LF_ALLOCATOR = NULL;

void lf_allocator_use(struct lf_allocator* allocator) {
  LF_ALLOCATOR = allocator;
}

u8* lf_allocate(usize size, usize align) {
  lf_assert(LF_ALLOCATOR != NULL);
  return LF_ALLOCATOR->allocate(LF_ALLOCATOR->self, size, align);
}

void lf_deallocate(u8* p) {
  lf_assert(LF_ALLOCATOR != NULL);
  return LF_ALLOCATOR->deallocate(LF_ALLOCATOR->self, p);
}
